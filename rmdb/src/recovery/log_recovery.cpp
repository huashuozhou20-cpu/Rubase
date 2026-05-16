/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "log_recovery.h"

#include <unordered_set>

#include "record/rm_file_handle.h"

void RecoveryManager::read_log_file() {
    log_size_ = disk_manager_->get_file_size(LOG_FILE_NAME);
    if (log_size_ <= 0) {
        log_data_ = nullptr;
        return;
    }
    log_data_ = new char[log_size_];
    disk_manager_->read_log(log_data_, log_size_, 0);
}

const char* RecoveryManager::get_record_by_lsn(lsn_t lsn) const {
    auto it = lsn_to_offset_.find(lsn);
    if (it == lsn_to_offset_.end()) {
        return nullptr;
    }
    return log_data_ + it->second;
}

void RecoveryManager::undo_txn(txn_id_t txn_id, lsn_t start_lsn) {
    lsn_t lsn = start_lsn;
    while (lsn != INVALID_LSN) {
        const char* rec = get_record_by_lsn(lsn);
        if (rec == nullptr) break;

        LogType log_type = *reinterpret_cast<const LogType*>(rec + OFFSET_LOG_TYPE);
        if (log_type == LogType::begin) break;

        if (log_type == LogType::INSERT) {
            InsertLogRecord log_rec;
            log_rec.deserialize(rec);
            auto it = sm_manager_->fhs_.find(std::string(log_rec.table_name_, log_rec.table_name_size_));
            if (it != sm_manager_->fhs_.end()) {
                it->second->delete_record(log_rec.rid_, nullptr);
            }
        } else if (log_type == LogType::DELETE) {
            DeleteLogRecord log_rec;
            log_rec.deserialize(rec);
            auto it = sm_manager_->fhs_.find(std::string(log_rec.table_name_, log_rec.table_name_size_));
            if (it != sm_manager_->fhs_.end()) {
                it->second->insert_record(log_rec.rid_, log_rec.delete_value_.data);
            }
        } else if (log_type == LogType::UPDATE) {
            UpdateLogRecord log_rec;
            log_rec.deserialize(rec);
            auto it = sm_manager_->fhs_.find(std::string(log_rec.table_name_, log_rec.table_name_size_));
            if (it != sm_manager_->fhs_.end()) {
                it->second->update_record(log_rec.rid_, log_rec.old_value_.data, nullptr);
            }
        }

        lsn = *reinterpret_cast<const lsn_t*>(rec + OFFSET_PREV_LSN);
    }
}

/**
 * @description: analyze阶段，需要获得脏页表（DPT）和未完成的事务列表（ATT）
 */
void RecoveryManager::analyze() {
    read_log_file();
    if (log_data_ == nullptr) return;

    att_.clear();
    txn_last_lsn_.clear();
    lsn_to_offset_.clear();
    dpt_.clear();

    int offset = 0;
    while (offset < log_size_) {
        const char* rec = log_data_ + offset;
        LogType log_type = *reinterpret_cast<const LogType*>(rec + OFFSET_LOG_TYPE);
        lsn_t lsn = *reinterpret_cast<const lsn_t*>(rec + OFFSET_LSN);
        uint32_t log_tot_len = *reinterpret_cast<const uint32_t*>(rec + OFFSET_LOG_TOT_LEN);
        txn_id_t log_tid = *reinterpret_cast<const txn_id_t*>(rec + OFFSET_LOG_TID);

        lsn_to_offset_[lsn] = offset;
        txn_last_lsn_[log_tid] = lsn;

        switch (log_type) {
            case LogType::begin:
                att_.insert(log_tid);
                break;
            case LogType::commit:
            case LogType::ABORT:
                att_.erase(log_tid);
                break;
            case LogType::INSERT:
            case LogType::DELETE:
            case LogType::UPDATE: {
                // Extract page_no from the record's rid
                int record_size = *reinterpret_cast<const int*>(rec + OFFSET_LOG_DATA);
                int rid_offset = OFFSET_LOG_DATA + sizeof(int) + record_size;
                if (log_type == LogType::UPDATE) {
                    // UPDATE has two records: old_value and new_value
                    int new_record_size = *reinterpret_cast<const int*>(rec + rid_offset);
                    rid_offset += sizeof(int) + new_record_size;
                }
                const Rid* rid = reinterpret_cast<const Rid*>(rec + rid_offset);
                dpt_[rid->page_no].push_back(lsn);
                break;
            }
        }

        offset += log_tot_len;
    }
}

/**
 * @description: 重做所有未落盘的操作（仅重做DPT中脏页上的操作）
 */
void RecoveryManager::redo() {
    if (log_data_ == nullptr) return;

    // 构建脏页集合，用于快速判断是否需要redo
    std::unordered_set<page_id_t> dirty_pages;
    lsn_t min_dirty_lsn = INVALID_LSN;
    for (auto &entry : dpt_) {
        dirty_pages.insert(entry.first);
        for (auto &lsn : entry.second) {
            if (min_dirty_lsn == INVALID_LSN || lsn < min_dirty_lsn) {
                min_dirty_lsn = lsn;
            }
        }
    }
    // 无脏页则无需重做
    if (dirty_pages.empty()) return;

    // 从最小脏页LSN开始扫描，跳过已落盘的日志记录
    int start_offset = 0;
    if (min_dirty_lsn != INVALID_LSN) {
        auto it = lsn_to_offset_.find(min_dirty_lsn);
        if (it != lsn_to_offset_.end()) start_offset = it->second;
    }

    int offset = start_offset;
    while (offset < log_size_) {
        const char* rec = log_data_ + offset;
        LogType log_type = *reinterpret_cast<const LogType*>(rec + OFFSET_LOG_TYPE);
        uint32_t log_tot_len = *reinterpret_cast<const uint32_t*>(rec + OFFSET_LOG_TOT_LEN);

        bool should_redo = true;
        // 对数据操作类日志，检查其所在页是否在DPT中
        if (log_type == LogType::INSERT || log_type == LogType::DELETE || log_type == LogType::UPDATE) {
            // 从序列化的日志记录中提取RID
            int rec_size = *reinterpret_cast<const int*>(rec + OFFSET_LOG_DATA);
            int rid_offset = OFFSET_LOG_DATA + sizeof(int) + rec_size;
            if (log_type == LogType::UPDATE) {
                int new_rec_size = *reinterpret_cast<const int*>(rec + rid_offset);
                rid_offset += sizeof(int) + new_rec_size;
            }
            const Rid* rid = reinterpret_cast<const Rid*>(rec + rid_offset);
            should_redo = dirty_pages.count(rid->page_no) > 0;
        }

        if (should_redo) {
            if (log_type == LogType::INSERT) {
                InsertLogRecord log_rec;
                log_rec.deserialize(rec);
                std::string table_name(log_rec.table_name_, log_rec.table_name_size_);
                auto it = sm_manager_->fhs_.find(table_name);
                if (it != sm_manager_->fhs_.end()) {
                    it->second->insert_record(log_rec.rid_, log_rec.insert_value_.data);
                }
            } else if (log_type == LogType::DELETE) {
                DeleteLogRecord log_rec;
                log_rec.deserialize(rec);
                std::string table_name(log_rec.table_name_, log_rec.table_name_size_);
                auto it = sm_manager_->fhs_.find(table_name);
                if (it != sm_manager_->fhs_.end()) {
                    it->second->delete_record(log_rec.rid_, nullptr);
                }
            } else if (log_type == LogType::UPDATE) {
                UpdateLogRecord log_rec;
                log_rec.deserialize(rec);
                std::string table_name(log_rec.table_name_, log_rec.table_name_size_);
                auto it = sm_manager_->fhs_.find(table_name);
                if (it != sm_manager_->fhs_.end()) {
                    it->second->update_record(log_rec.rid_, log_rec.new_value_.data, nullptr);
                }
            }
        }

        offset += log_tot_len;
    }
}

/**
 * @description: 回滚未完成的事务
 */
void RecoveryManager::undo() {
    if (log_data_ == nullptr) return;

    // Undo each active transaction (process in any order for now)
    for (txn_id_t txn_id : att_) {
        lsn_t last_lsn = txn_last_lsn_[txn_id];
        undo_txn(txn_id, last_lsn);
    }

    att_.clear();
    txn_last_lsn_.clear();
    lsn_to_offset_.clear();
    dpt_.clear();

    if (log_data_ != nullptr) {
        delete[] log_data_;
        log_data_ = nullptr;
    }
    log_size_ = 0;
}
