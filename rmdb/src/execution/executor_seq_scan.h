/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include "index/ix.h"
#include "system/sm.h"

class SeqScanExecutor : public AbstractExecutor {
   private:
    std::string tab_name_;              // 表的名称
    std::vector<Condition> conds_;      // scan的条件
    RmFileHandle *fh_;                  // 表的数据文件句柄
    std::vector<ColMeta> cols_;         // scan后生成的记录的字段
    size_t len_;                        // scan后生成的每条记录的长度
    std::vector<Condition> fed_conds_;  // 同conds_，两个字段相同

    Rid rid_;
    std::unique_ptr<RecScan> scan_;     // table_iterator
    bool is_end_;

    SmManager *sm_manager_;

    // 评估单条条件是否满足（支持递归 OR/NOT）
    bool eval_cond(const Condition &cond, const RmRecord &rec) {
        // Internal node: OR
        if (cond.op == OP_OR) {
            for (auto &child : cond.children) {
                if (eval_cond(child, rec)) return true;
            }
            return cond.children.empty();
        }
        // Internal node: NOT
        if (cond.op == OP_NOT) {
            for (auto &child : cond.children) {
                if (eval_cond(child, rec)) return false;
            }
            return true;
        }

        // Leaf: find lhs column
        const ColMeta *lhs_meta = nullptr;
        for (auto &col : cols_) {
            if (col.tab_name == cond.lhs_col.tab_name && col.name == cond.lhs_col.col_name) {
                lhs_meta = &col;
                break;
            }
        }
        if (!lhs_meta) return true;

        char *lhs_data = rec.data + lhs_meta->offset;

        // IS NULL / IS NOT NULL
        if (cond.op == OP_IS_NULL) {
            return check_is_null(lhs_data, lhs_meta->type, lhs_meta->len);
        }
        if (cond.op == OP_IS_NOT_NULL) {
            return !check_is_null(lhs_data, lhs_meta->type, lhs_meta->len);
        }

        // LIKE / NOT LIKE
        if (cond.op == OP_LIKE || cond.op == OP_NOT_LIKE) {
            std::string col_str(lhs_data, lhs_meta->len);
            col_str = col_str.c_str();  // trim null padding
            bool matched = like_match(col_str, cond.rhs_val.str_val);
            return (cond.op == OP_LIKE) ? matched : !matched;
        }

        // BETWEEN / NOT BETWEEN
        if (cond.op == OP_BETWEEN || cond.op == OP_NOT_BETWEEN) {
            int cmp_low = 0, cmp_high = 0;
            switch (lhs_meta->type) {
                case TYPE_INT: {
                    int a = *(int *)lhs_data;
                    cmp_low = (a < cond.rhs_val.int_val) ? -1 : ((a > cond.rhs_val.int_val) ? 1 : 0);
                    cmp_high = (a < cond.rhs_val2.int_val) ? -1 : ((a > cond.rhs_val2.int_val) ? 1 : 0);
                    break;
                }
                case TYPE_FLOAT: {
                    float a = *(float *)lhs_data;
                    cmp_low = (a < cond.rhs_val.float_val) ? -1 : ((a > cond.rhs_val.float_val) ? 1 : 0);
                    cmp_high = (a < cond.rhs_val2.float_val) ? -1 : ((a > cond.rhs_val2.float_val) ? 1 : 0);
                    break;
                }
                case TYPE_STRING:
                    cmp_low = memcmp(lhs_data, cond.rhs_val.raw->data, lhs_meta->len);
                    cmp_high = memcmp(lhs_data, cond.rhs_val2.raw->data, lhs_meta->len);
                    break;
            }
            bool in_range = (cmp_low >= 0 && cmp_high <= 0);
            return (cond.op == OP_BETWEEN) ? in_range : !in_range;
        }

        // IN / NOT IN
        if (cond.op == OP_IN || cond.op == OP_NOT_IN) {
            bool found = false;
            for (auto &v : cond.in_values) {
                int cmp = 0;
                switch (lhs_meta->type) {
                    case TYPE_INT: {
                        int a = *(int *)lhs_data;
                        cmp = (a < v.int_val) ? -1 : ((a > v.int_val) ? 1 : 0);
                        break;
                    }
                    case TYPE_FLOAT: {
                        float a = *(float *)lhs_data;
                        cmp = (a < v.float_val) ? -1 : ((a > v.float_val) ? 1 : 0);
                        break;
                    }
                    case TYPE_STRING:
                        cmp = memcmp(lhs_data, v.raw->data, lhs_meta->len);
                        break;
                }
                if (cmp == 0) { found = true; break; }
            }
            return (cond.op == OP_IN) ? found : !found;
        }

        // Regular comparison (col op value)
        if (cond.is_rhs_val) {
            int cmp = 0;
            switch (lhs_meta->type) {
                case TYPE_INT: {
                    int a = *(int *)lhs_data, b = cond.rhs_val.int_val;
                    cmp = (a < b) ? -1 : ((a > b) ? 1 : 0);
                    break;
                }
                case TYPE_FLOAT: {
                    float a = *(float *)lhs_data, b = cond.rhs_val.float_val;
                    cmp = (a < b) ? -1 : ((a > b) ? 1 : 0);
                    break;
                }
                case TYPE_STRING:
                    cmp = memcmp(lhs_data, cond.rhs_val.raw->data, lhs_meta->len);
                    break;
            }
            switch (cond.op) {
                case OP_EQ: return cmp == 0;
                case OP_NE: return cmp != 0;
                case OP_LT: return cmp < 0;
                case OP_GT: return cmp > 0;
                case OP_LE: return cmp <= 0;
                case OP_GE: return cmp >= 0;
                default: return true;
            }
        } else {
            // col1 op col2
            const ColMeta *rhs_meta = nullptr;
            for (auto &col : cols_) {
                if (col.tab_name == cond.rhs_col.tab_name && col.name == cond.rhs_col.col_name) {
                    rhs_meta = &col;
                    break;
                }
            }
            if (!rhs_meta) return true;

            char *rhs_data = rec.data + rhs_meta->offset;
            int cmp = 0;
            switch (lhs_meta->type) {
                case TYPE_INT: {
                    int a = *(int *)lhs_data, b = *(int *)rhs_data;
                    cmp = (a < b) ? -1 : ((a > b) ? 1 : 0);
                    break;
                }
                case TYPE_FLOAT: {
                    float a = *(float *)lhs_data, b = *(float *)rhs_data;
                    cmp = (a < b) ? -1 : ((a > b) ? 1 : 0);
                    break;
                }
                case TYPE_STRING:
                    cmp = memcmp(lhs_data, rhs_data, lhs_meta->len);
                    break;
            }
            switch (cond.op) {
                case OP_EQ: return cmp == 0;
                case OP_NE: return cmp != 0;
                case OP_LT: return cmp < 0;
                case OP_GT: return cmp > 0;
                case OP_LE: return cmp <= 0;
                case OP_GE: return cmp >= 0;
                default: return true;
            }
        }
    }


    // 检查当前记录是否满足所有条件（AND 语义）
    bool check_all_conds(const RmRecord &rec) {
        for (auto &cond : fed_conds_) {
            if (!eval_cond(cond, rec)) return false;
        }
        return true;
    }

   public:
    SeqScanExecutor(SmManager *sm_manager, std::string tab_name, std::vector<Condition> conds, Context *context) {
        sm_manager_ = sm_manager;
        tab_name_ = std::move(tab_name);
        conds_ = std::move(conds);
        TabMeta &tab = sm_manager_->db_.get_table(tab_name_);
        fh_ = sm_manager_->fhs_.at(tab_name_).get();
        cols_ = tab.cols;
        len_ = cols_.back().offset + cols_.back().len;

        context_ = context;
        fed_conds_ = conds_;
        is_end_ = true;
    }

    // Returns a visible version of the record at the given rid, following the
    // MVCC version chain through undo logs if the current version is not visible.
    std::unique_ptr<RmRecord> get_visible_record(const Rid& rid) {
        auto rec = fh_->get_record_snapshot(rid);
        if (!rec) return nullptr;

        txn_id_t trx_id;
        memcpy(&trx_id, rec->data + trx_id_offset(rec->size), sizeof(txn_id_t));

        if (context_->txn_->is_visible(trx_id)) {
            return rec;
        }

        // Follow version chain through undo logs
        UndoLink roll_ptr;
        memcpy(&roll_ptr, rec->data + roll_ptr_offset(rec->size), sizeof(UndoLink));

        while (roll_ptr.IsValid()) {
            auto undo_opt = context_->txn_mgr_->GetUndoLogOptional(roll_ptr);
            if (!undo_opt.has_value()) return nullptr;

            auto& undo = *undo_opt;
            if (undo.is_deleted_) return nullptr;
            if (!undo.tuple_test_) return nullptr;

            // Read trx_id from the old version's hidden fields
            int old_size = undo.tuple_test_->size;
            txn_id_t old_trx_id;
            memcpy(&old_trx_id,
                   undo.tuple_test_->data + trx_id_offset(old_size),
                   sizeof(txn_id_t));

            if (context_->txn_->is_visible(old_trx_id)) {
                // Return a (shallow, non-owning) copy of the old record data.
                auto result = std::make_unique<RmRecord>();
                result->size = old_size;
                result->data = undo.tuple_test_->data;
                result->allocated_ = false;
                return result;
            }

            roll_ptr = undo.prev_version_;
        }

        return nullptr;  // no visible version in chain
    }

    // Check whether we should use MVCC lock-free snapshot reads.
    bool use_mvcc_read() const {
        return context_->txn_mgr_ != nullptr
            && context_->txn_ != nullptr
            && context_->txn_->has_read_view()
            && context_->txn_->is_read_only();
    }

    void beginTuple() override {
        scan_ = std::make_unique<RmScan>(fh_);
        if (scan_->is_end()) {
            is_end_ = true;
            return;
        }
        is_end_ = false;
        rid_ = scan_->rid();
        if (use_mvcc_read()) {
            auto rec = get_visible_record(rid_);
            if (!rec || !check_all_conds(*rec)) {
                nextTuple();
            }
        } else {
            auto rec = fh_->get_record(rid_, context_);
            if (!check_all_conds(*rec)) {
                nextTuple();
            }
        }
    }

    void nextTuple() override {
        bool mvcc = use_mvcc_read();
        while (true) {
            scan_->next();
            if (scan_->is_end()) {
                is_end_ = true;
                return;
            }
            rid_ = scan_->rid();
            if (mvcc) {
                auto rec = get_visible_record(rid_);
                if (rec && check_all_conds(*rec)) return;
            } else {
                auto rec = fh_->get_record(rid_, context_);
                if (check_all_conds(*rec)) return;
            }
        }
    }

    bool is_end() const override { return is_end_; }

    size_t tupleLen() const override { return len_; }

    const std::vector<ColMeta> &cols() const override { return cols_; }

    ColMeta get_col_offset(const TabCol &target) override {
        for (auto &col : cols_) {
            if (col.name == target.col_name &&
                (target.tab_name.empty() || col.tab_name == target.tab_name))
                return col;
        }
        return ColMeta{};
    }

    std::unique_ptr<RmRecord> Next() override {
        if (is_end_) return nullptr;
        if (use_mvcc_read()) {
            return get_visible_record(rid_);
        }
        return fh_->get_record(rid_, context_);
    }

    Rid &rid() override { return rid_; }
};