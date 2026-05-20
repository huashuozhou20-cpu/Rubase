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

class IndexScanExecutor : public AbstractExecutor {
   private:
    std::string tab_name_;                      // 表名称
    TabMeta tab_;                               // 表的元数据
    std::vector<Condition> conds_;              // 扫描条件
    RmFileHandle *fh_;                          // 表的数据文件句柄
    std::vector<ColMeta> cols_;                 // 需要读取的字段
    size_t len_;                                // 选取出来的一条记录的长度
    std::vector<Condition> fed_conds_;          // 扫描条件，和conds_字段相同

    std::vector<std::string> index_col_names_;  // index scan涉及到的索引包含的字段
    IndexMeta index_meta_;                      // index scan涉及到的索引元数据

    Rid rid_;
    std::unique_ptr<RecScan> scan_;
    bool is_end_;

    SmManager *sm_manager_;

    const ColMeta *get_col_meta(const TabCol &target) {
        for (auto &col : tab_.cols) {
            if (col.name == target.col_name) return &col;
        }
        return nullptr;
    }

    bool eval_cond(const Condition &cond, const RmRecord &rec) {
        if (cond.op == OP_OR) {
            for (auto &child : cond.children) {
                if (eval_cond(child, rec)) return true;
            }
            return cond.children.empty();
        }
        if (cond.op == OP_NOT) {
            for (auto &child : cond.children) {
                if (eval_cond(child, rec)) return false;
            }
            return true;
        }

        const ColMeta *lhs_meta = get_col_meta(cond.lhs_col);
        if (!lhs_meta) return true;
        char *lhs_data = rec.data + lhs_meta->offset;

        if (cond.op == OP_IS_NULL)
            return check_is_null(lhs_data, lhs_meta->type, lhs_meta->len);
        if (cond.op == OP_IS_NOT_NULL)
            return !check_is_null(lhs_data, lhs_meta->type, lhs_meta->len);

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
                default: return false;
            }
            bool in_range = (cmp_low >= 0 && cmp_high <= 0);
            return (cond.op == OP_BETWEEN) ? in_range : !in_range;
        }

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
                    default: break;
                }
                if (cmp == 0) { found = true; break; }
            }
            return (cond.op == OP_IN) ? found : !found;
        }

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
                default: return false;
            }
            switch (cond.op) {
                case OP_EQ: return cmp == 0;
                case OP_NE: return cmp != 0;
                case OP_LT: return cmp < 0;
                case OP_GT: return cmp > 0;
                case OP_LE: return cmp <= 0;
                case OP_GE: return cmp >= 0;
                case OP_LIKE: {
                    std::string lhs_str(lhs_data, lhs_meta->len);
                    return like_match(lhs_str, cond.rhs_val.str_val);
                }
                case OP_NOT_LIKE: {
                    std::string lhs_str(lhs_data, lhs_meta->len);
                    return !like_match(lhs_str, cond.rhs_val.str_val);
                }
                default: return true;
            }
        } else {
            const ColMeta *rhs_meta = get_col_meta(cond.rhs_col);
            if (!rhs_meta) return true;
            char *rhs_data = rec.data + rhs_meta->offset;
            if (lhs_meta->type != rhs_meta->type) return false;
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
                default: return false;
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

    bool check_all_conds(const RmRecord &rec) {
        if (fed_conds_.empty()) return true;
        for (auto &cond : fed_conds_) {
            if (!eval_cond(cond, rec)) return false;
        }
        return true;
    }

   public:
    IndexScanExecutor(SmManager *sm_manager, std::string tab_name, std::vector<Condition> conds,
                      std::vector<std::string> index_col_names, Context *context) {
        sm_manager_ = sm_manager;
        context_ = context;
        tab_name_ = std::move(tab_name);
        tab_ = sm_manager_->db_.get_table(tab_name_);
        conds_ = std::move(conds);
        index_col_names_ = index_col_names;
        index_meta_ = *(tab_.get_index_meta(index_col_names_));
        fh_ = sm_manager_->fhs_.at(tab_name_).get();
        cols_ = tab_.cols;
        len_ = cols_.back().offset + cols_.back().len;
        std::map<CompOp, CompOp> swap_op = {
            {OP_EQ, OP_EQ}, {OP_NE, OP_NE}, {OP_LT, OP_GT}, {OP_GT, OP_LT}, {OP_LE, OP_GE}, {OP_GE, OP_LE},
            {OP_IS_NULL, OP_IS_NULL}, {OP_IS_NOT_NULL, OP_IS_NOT_NULL},
            {OP_LIKE, OP_LIKE}, {OP_NOT_LIKE, OP_NOT_LIKE},
        };

        for (auto &cond : conds_) {
            if (cond.lhs_col.tab_name != tab_name_) {
                assert(!cond.is_rhs_val && cond.rhs_col.tab_name == tab_name_);
                std::swap(cond.lhs_col, cond.rhs_col);
                auto it = swap_op.find(cond.op);
                if (it != swap_op.end()) {
                    cond.op = it->second;
                }
            }
        }
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

            int old_size = undo.tuple_test_->size;
            txn_id_t old_trx_id;
            memcpy(&old_trx_id,
                   undo.tuple_test_->data + trx_id_offset(old_size),
                   sizeof(txn_id_t));

            if (context_->txn_->is_visible(old_trx_id)) {
                auto result = std::make_unique<RmRecord>();
                result->size = old_size;
                result->data = undo.tuple_test_->data;
                result->allocated_ = false;
                return result;
            }

            roll_ptr = undo.prev_version_;
        }

        return nullptr;
    }

    bool use_mvcc_read() const {
        return context_->txn_mgr_ != nullptr
            && context_->txn_ != nullptr
            && context_->txn_->has_read_view()
            && context_->txn_->is_read_only();
    }

    void beginTuple() override {
        auto ih = sm_manager_->ihs_
                      .at(sm_manager_->get_ix_manager()->get_index_name(tab_name_, index_meta_.cols))
                      .get();

        char *key = new char[index_meta_.col_tot_len];
        memset(key, 0, index_meta_.col_tot_len);
        int offset = 0;
        for (size_t i = 0; i < static_cast<size_t>(index_meta_.col_num); i++) {
            for (auto &cond : fed_conds_) {
                if (cond.is_rhs_val && cond.op == OP_EQ &&
                    cond.lhs_col.col_name == index_meta_.cols[i].name &&
                    cond.lhs_col.tab_name == tab_name_) {
                    cond.rhs_val.init_raw(index_meta_.cols[i].len);
                    memcpy(key + offset, cond.rhs_val.raw->data, index_meta_.cols[i].len);
                    break;
                }
            }
            offset += index_meta_.cols[i].len;
        }

        Iid lower = ih->lower_bound(key);
        Iid upper = ih->upper_bound(key);
        scan_ = std::make_unique<IxScan>(ih, lower, upper, sm_manager_->get_bpm());
        delete[] key;
        is_end_ = false;
        nextTuple();
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

    std::unique_ptr<RmRecord> Next() override {
        if (is_end_) return nullptr;
        if (use_mvcc_read()) {
            return get_visible_record(rid_);
        }
        return fh_->get_record(rid_, context_);
    }

    Rid &rid() override { return rid_; }
};