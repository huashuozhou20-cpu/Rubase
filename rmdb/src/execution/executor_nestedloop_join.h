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

class NestedLoopJoinExecutor : public AbstractExecutor {
   private:
    std::unique_ptr<AbstractExecutor> left_;    // 左儿子节点（需要join的表）
    std::unique_ptr<AbstractExecutor> right_;   // 右儿子节点（需要join的表）
    size_t len_;                                // join后获得的每条记录的长度
    std::vector<ColMeta> cols_;                 // join后获得的记录的字段

    std::vector<Condition> fed_conds_;          // join条件
    bool is_end_;
    std::unique_ptr<RmRecord> left_record_;
    std::unique_ptr<RmRecord> right_record_;

    bool eval_cond(const Condition &cond, const RmRecord &left_rec, const RmRecord &right_rec) {
        // 找到左右两侧列在各自记录中的偏移和类型
        const auto &lhs_col_meta = get_col_meta(cond.lhs_col);
        const auto &rhs_col_meta = get_col_meta(cond.rhs_col);

        char *lhs_data = (lhs_col_meta.tab_name == left_->cols()[0].tab_name)
                             ? left_rec.data + lhs_col_meta.offset
                             : right_rec.data + lhs_col_meta.offset;

        char *rhs_data = (rhs_col_meta.tab_name == left_->cols()[0].tab_name)
                             ? left_rec.data + rhs_col_meta.offset
                             : right_rec.data + rhs_col_meta.offset;

        if (lhs_col_meta.type != rhs_col_meta.type) return false;

        int cmp = 0;
        switch (lhs_col_meta.type) {
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
                cmp = memcmp(lhs_data, rhs_data, lhs_col_meta.len);
                break;
        }

        switch (cond.op) {
            case OP_EQ: return cmp == 0;
            case OP_NE: return cmp != 0;
            case OP_LT: return cmp < 0;
            case OP_GT: return cmp > 0;
            case OP_LE: return cmp <= 0;
            case OP_GE: return cmp >= 0;
        }
        return false;
    }

    ColMeta get_col_meta(const TabCol &target) {
        for (auto &col : cols_) {
            if (col.tab_name == target.tab_name && col.name == target.col_name) return col;
        }
        for (auto &col : left_->cols()) {
            if (col.tab_name == target.tab_name && col.name == target.col_name) return col;
        }
        for (auto &col : right_->cols()) {
            if (col.tab_name == target.tab_name && col.name == target.col_name) return col;
        }
        return ColMeta{};
    }

    bool check_all_conds() {
        if (fed_conds_.empty()) return true;
        for (auto &cond : fed_conds_) {
            if (!eval_cond(cond, *left_record_, *right_record_)) return false;
        }
        return true;
    }

    bool find_next_match() {
        while (true) {
            // 尝试推进右表
            right_->nextTuple();
            if (!right_->is_end()) {
                right_record_ = right_->Next();
                if (check_all_conds()) return true;
                continue;
            }
            // 右表遍历完，推进左表，重置右表
            left_->nextTuple();
            if (left_->is_end()) return false;
            left_record_ = left_->Next();

            right_->beginTuple();
            if (!right_->is_end()) {
                right_record_ = right_->Next();
                if (check_all_conds()) return true;
            }
        }
    }

   public:
    NestedLoopJoinExecutor(std::unique_ptr<AbstractExecutor> left, std::unique_ptr<AbstractExecutor> right,
                            std::vector<Condition> conds) {
        left_ = std::move(left);
        right_ = std::move(right);
        len_ = left_->tupleLen() + right_->tupleLen();
        cols_ = left_->cols();
        auto right_cols = right_->cols();
        for (auto &col : right_cols) {
            col.offset += left_->tupleLen();
        }

        cols_.insert(cols_.end(), right_cols.begin(), right_cols.end());
        is_end_ = true;
        fed_conds_ = std::move(conds);
    }

    void beginTuple() override {
        left_->beginTuple();
        if (left_->is_end()) {
            is_end_ = true;
            return;
        }
        left_record_ = left_->Next();

        right_->beginTuple();
        if (!right_->is_end()) {
            right_record_ = right_->Next();
            if (check_all_conds()) {
                is_end_ = false;
                return;
            }
        }
        // 寻找第一个满足条件的配对
        if (find_next_match()) {
            is_end_ = false;
        } else {
            is_end_ = true;
        }
    }

    void nextTuple() override {
        if (!find_next_match()) {
            is_end_ = true;
        }
    }

    bool is_end() const override { return is_end_; }

    size_t tupleLen() const override { return len_; }

    const std::vector<ColMeta> &cols() const override { return cols_; }

    std::unique_ptr<RmRecord> Next() override {
        if (is_end_) return nullptr;
        auto rec = std::make_unique<RmRecord>(len_);
        memcpy(rec->data, left_record_->data, left_->tupleLen());
        memcpy(rec->data + left_->tupleLen(), right_record_->data, right_->tupleLen());
        return rec;
    }

    Rid &rid() override { return _abstract_rid; }
};