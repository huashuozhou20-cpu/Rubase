/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "transaction_manager.h"
#include "record/rm_file_handle.h"
#include "system/sm_manager.h"

std::unordered_map<txn_id_t, Transaction *> TransactionManager::txn_map = {};

/**
 * @description: 事务的开始方法
 * @return {Transaction*} 开始事务的指针
 * @param {Transaction*} txn 事务指针，空指针代表需要创建新事务，否则开始已有事务
 * @param {LogManager*} log_manager 日志管理器指针
 */
Transaction * TransactionManager::begin(Transaction* txn, LogManager* log_manager) {
    if (txn == nullptr) {
        txn_id_t txn_id = next_txn_id_++;
        txn = new Transaction(txn_id);
    }
    txn->set_state(TransactionState::GROWING);

    if (concurrency_mode_ == ConcurrencyMode::MVCC) {
        txn->set_read_ts(next_timestamp_++);
        txn->set_start_ts(txn->get_read_ts());
        running_txns_.AddTxn(txn->get_read_ts());

        // Build ReadView under latch_ (txn_map iteration must be protected)
        ReadView rv;
        rv.low_limit_id_ = next_txn_id_.load();
        rv.up_limit_id_ = rv.low_limit_id_;
        {
            std::scoped_lock lock(latch_);
            for (auto& [tid, t] : TransactionManager::txn_map) {
                auto state = t->get_state();
                if (state == TransactionState::GROWING || state == TransactionState::SHRINKING) {
                    rv.active_txn_ids_.push_back(tid);
                    if (tid < rv.up_limit_id_) rv.up_limit_id_ = tid;
                }
            }
        }
        txn->set_read_view(rv);
    }

    std::scoped_lock lock(latch_);
    TransactionManager::txn_map[txn->get_transaction_id()] = txn;

    auto* begin_log = new BeginLogRecord(txn->get_transaction_id());
    lsn_t lsn = log_manager->add_log_to_buffer(begin_log);
    txn->set_prev_lsn(lsn);

    return txn;
}

/**
 * @description: 事务的提交方法
 * @param {Transaction*} txn 需要提交的事务
 * @param {LogManager*} log_manager 日志管理器指针
 */
void TransactionManager::commit(Transaction* txn, LogManager* log_manager) {
    txn->set_state(TransactionState::SHRINKING);

    auto* commit_log = new CommitLogRecord(txn->get_transaction_id());
    log_manager->add_log_to_buffer(commit_log);
    log_manager->flush_log_to_disk();

    // Release all locks
    for (auto& lock_data_id : *txn->get_lock_set()) {
        lock_manager_->unlock(txn, lock_data_id);
    }
    txn->get_lock_set()->clear();
    txn->get_write_set()->clear();

    txn->set_state(TransactionState::COMMITTED);
    txn->set_commit_ts(next_timestamp_++);

    if (concurrency_mode_ == ConcurrencyMode::MVCC) {
        running_txns_.RemoveTxn(txn->get_read_ts());
        running_txns_.UpdateCommitTs(txn->get_commit_ts());
        // Periodic GC: clean up committed/aborted txns below the watermark
        static std::atomic<int> gc_counter{0};
        if (++gc_counter % 64 == 0) {
            GarbageCollection();
        }
    } else {
        std::scoped_lock lock(latch_);
        TransactionManager::txn_map.erase(txn->get_transaction_id());
    }
}

/**
 * @description: 事务的终止（回滚）方法
 * @param {Transaction *} txn 需要回滚的事务
 * @param {LogManager} *log_manager 日志管理器指针
 */
void TransactionManager::abort(Transaction * txn, LogManager *log_manager) {
    txn->set_state(TransactionState::SHRINKING);

    // Rollback writes in reverse order
    auto& write_set = *txn->get_write_set();
    while (!write_set.empty()) {
        WriteRecord* wr = write_set.back();
        write_set.pop_back();
        RmFileHandle* fh = sm_manager_->fhs_[wr->GetTableName()].get();
        switch (wr->GetWriteType()) {
            case WType::INSERT_TUPLE:
                fh->delete_record(wr->GetRid(), nullptr);
                break;
            case WType::DELETE_TUPLE:
                fh->insert_record(wr->GetRid(), wr->GetRecord().data);
                break;
            case WType::UPDATE_TUPLE:
                fh->update_record(wr->GetRid(), wr->GetRecord().data, nullptr);
                break;
        }
        delete wr;
    }

    auto* abort_log = new AbortLogRecord(txn->get_transaction_id());
    log_manager->add_log_to_buffer(abort_log);
    log_manager->flush_log_to_disk();

    // Release all locks
    for (auto& lock_data_id : *txn->get_lock_set()) {
        lock_manager_->unlock(txn, lock_data_id);
    }
    txn->get_lock_set()->clear();

    txn->set_state(TransactionState::ABORTED);
    txn->set_commit_ts(next_timestamp_++);

    if (concurrency_mode_ == ConcurrencyMode::MVCC) {
        running_txns_.RemoveTxn(txn->get_read_ts());
        running_txns_.UpdateCommitTs(txn->get_commit_ts());
    } else {
        std::scoped_lock lock(latch_);
        TransactionManager::txn_map.erase(txn->get_transaction_id());
    }
}

/* ===== MVCC Methods ===== */

bool TransactionManager::UpdateUndoLink(Rid rid, std::optional<UndoLink> prev_link,
                                        std::function<bool(std::optional<UndoLink>)> &&check) {
    std::optional<VersionUndoLink> prev_version = VersionUndoLink::FromOptionalUndoLink(prev_link);
    auto version_check = [&](std::optional<VersionUndoLink> cur) -> bool {
        if (!check) return true;
        if (!cur.has_value()) return check(std::nullopt);
        return check(cur->prev_);
    };
    return UpdateVersionLink(rid, prev_version, version_check);
}

bool TransactionManager::UpdateVersionLink(
    Rid rid, std::optional<VersionUndoLink> prev_version,
    std::function<bool(std::optional<VersionUndoLink>)> &&check) {

    std::unique_lock<std::shared_mutex> map_lock(version_info_mutex_);

    auto it = version_info_.find(rid.page_no);
    std::shared_ptr<PageVersionInfo> page_info;
    if (it == version_info_.end()) {
        page_info = std::make_shared<PageVersionInfo>();
        version_info_[rid.page_no] = page_info;
    } else {
        page_info = it->second;
    }
    map_lock.unlock();

    std::unique_lock<std::shared_mutex> page_lock(page_info->mutex_);

    auto slot_it = page_info->prev_version_.find(rid.slot_no);
    std::optional<VersionUndoLink> current;
    if (slot_it != page_info->prev_version_.end()) {
        current = slot_it->second;
    }

    if (check && !check(current)) {
        return false;
    }

    if (prev_version.has_value()) {
        page_info->prev_version_[rid.slot_no] = *prev_version;
    } else {
        page_info->prev_version_.erase(rid.slot_no);
    }
    return true;
}

std::optional<UndoLink> TransactionManager::GetUndoLink(Rid rid) {
    auto version_link = GetVersionLink(rid);
    if (version_link.has_value()) {
        return version_link->prev_;
    }
    return std::nullopt;
}

std::optional<VersionUndoLink> TransactionManager::GetVersionLink(Rid rid) {
    std::shared_lock<std::shared_mutex> map_lock(version_info_mutex_);

    auto it = version_info_.find(rid.page_no);
    if (it == version_info_.end()) {
        return std::nullopt;
    }
    auto page_info = it->second;
    map_lock.unlock();

    std::shared_lock<std::shared_mutex> page_lock(page_info->mutex_);
    auto slot_it = page_info->prev_version_.find(rid.slot_no);
    if (slot_it != page_info->prev_version_.end()) {
        return slot_it->second;
    }
    return std::nullopt;
}

std::optional<UndoLog> TransactionManager::GetUndoLogOptional(UndoLink link) {
    if (!link.IsValid()) {
        return std::nullopt;
    }
    std::scoped_lock lock(latch_);
    auto it = TransactionManager::txn_map.find(link.prev_txn_);
    if (it == TransactionManager::txn_map.end()) {
        return std::nullopt;
    }
    return it->second->GetUndoLog(link.prev_log_idx_);
}

UndoLog TransactionManager::GetUndoLog(UndoLink link) {
    auto result = GetUndoLogOptional(link);
    if (!result.has_value()) {
        throw InternalError("GetUndoLog: transaction " + std::to_string(link.prev_txn_) +
                            " not found for undo log index " + std::to_string(link.prev_log_idx_));
    }
    return *result;
}

timestamp_t TransactionManager::GetWatermark() {
    return running_txns_.GetWatermark();
}

void TransactionManager::GarbageCollection() {
    timestamp_t watermark = GetWatermark();
    // watermark_ starts at 0 (constructor default). Skip GC until at least
    // one commit has advanced it past the initial value.
    if (watermark <= 0) return;

    std::scoped_lock lock(latch_);

    std::vector<std::pair<txn_id_t, Transaction*>> to_erase;
    for (auto& [txn_id, txn] : TransactionManager::txn_map) {
        auto state = txn->get_state();
        if (state == TransactionState::COMMITTED || state == TransactionState::ABORTED) {
            if (txn->get_commit_ts() < watermark) {
                to_erase.emplace_back(txn_id, txn);
            }
        }
    }

    for (auto& [txn_id, txn] : to_erase) {
        TransactionManager::txn_map.erase(txn_id);
        delete txn;  // free the Transaction object allocated in begin()
    }
}