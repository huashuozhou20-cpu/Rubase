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

#include <algorithm>
#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include "execution_sort.h"
#include "index/ix.h"
#include "system/sm.h"

class SortMergeJoinExecutor : public AbstractExecutor {
   private:
    std::unique_ptr<AbstractExecutor> left_;
    std::unique_ptr<AbstractExecutor> right_;
    size_t len_;
    std::vector<ColMeta> cols_;

    std::vector<Condition> conds_;
    std::vector<Condition> equi_conds_;
    bool is_end_;
    std::unique_ptr<RmRecord> left_record_;
    std::unique_ptr<RmRecord> right_record_;
    std::vector<RmRecord> right_matches_;  // buffered matches for current left key
    size_t right_match_pos_;

    ColMeta get_col_meta(const TabCol &target) {
        for (auto &col : cols_) {
            if (col.tab_name == target.tab_name && col.name == target.col_name)
                return col;
        }
        for (auto &col : left_->cols()) {
            if (col.tab_name == target.tab_name && col.name == target.col_name)
                return col;
        }
        for (auto &col : right_->cols()) {
            if (col.tab_name == target.tab_name && col.name == target.col_name)
                return col;
        }
        return ColMeta{};
    }

    // Compare join keys from left and right records
    int compare_keys(const RmRecord &left_rec, const RmRecord &right_rec) {
        for (auto &cond : equi_conds_) {
            ColMeta lhs_meta = get_col_meta(cond.lhs_col);
            ColMeta rhs_meta = get_col_meta(cond.rhs_col);

            char *lhs_data = (lhs_meta.tab_name == left_->cols()[0].tab_name)
                                 ? left_rec.data + lhs_meta.offset
                                 : right_rec.data + lhs_meta.offset;
            char *rhs_data = (rhs_meta.tab_name == left_->cols()[0].tab_name)
                                 ? left_rec.data + rhs_meta.offset
                                 : right_rec.data + rhs_meta.offset;

            int cmp = 0;
            switch (lhs_meta.type) {
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
                    cmp = memcmp(lhs_data, rhs_data, lhs_meta.len);
                    break;
            }
            if (cmp != 0) return cmp;
        }
        return 0;
    }

    bool eval_cond(const Condition &cond, const RmRecord &left_rec,
                   const RmRecord &right_rec) {
        if (cond.op == OP_OR) {
            for (auto &child : cond.children) {
                if (eval_cond(child, left_rec, right_rec)) return true;
            }
            return cond.children.empty();
        }
        if (cond.op == OP_NOT) {
            for (auto &child : cond.children) {
                if (eval_cond(child, left_rec, right_rec)) return false;
            }
            return true;
        }

        ColMeta lhs_meta = get_col_meta(cond.lhs_col);
        char *lhs_data = nullptr;
        if (!lhs_meta.tab_name.empty()) {
            lhs_data = (lhs_meta.tab_name == left_->cols()[0].tab_name)
                           ? left_rec.data + lhs_meta.offset
                           : right_rec.data + lhs_meta.offset;
        }

        if (cond.op == OP_IS_NULL)
            return check_is_null(lhs_data, lhs_meta.type, lhs_meta.len);
        if (cond.op == OP_IS_NOT_NULL)
            return !check_is_null(lhs_data, lhs_meta.type, lhs_meta.len);

        ColMeta rhs_meta = get_col_meta(cond.rhs_col);
        char *rhs_data = nullptr;
        if (!rhs_meta.tab_name.empty()) {
            rhs_data = (rhs_meta.tab_name == left_->cols()[0].tab_name)
                           ? left_rec.data + rhs_meta.offset
                           : right_rec.data + rhs_meta.offset;
        }

        if (lhs_meta.type != rhs_meta.type) return false;

        int cmp = 0;
        switch (lhs_meta.type) {
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
                cmp = memcmp(lhs_data, rhs_data, lhs_meta.len);
                break;
        }

        switch (cond.op) {
            case OP_EQ: return cmp == 0;
            case OP_NE: return cmp != 0;
            case OP_LT: return cmp < 0;
            case OP_GT: return cmp > 0;
            case OP_LE: return cmp <= 0;
            case OP_GE: return cmp >= 0;
            default: return false;
        }
    }

    bool check_all_conds() {
        if (conds_.empty()) return true;
        for (auto &cond : conds_) {
            if (!eval_cond(cond, *left_record_, *right_record_)) return false;
        }
        return true;
    }

    bool advance_to_next_match() {
        while (true) {
            if (right_match_pos_ < right_matches_.size()) {
                // Still have buffered matches for current left key
                right_record_ = std::make_unique<RmRecord>(right_matches_[right_match_pos_++]);
                return true;
            }
            right_matches_.clear();
            right_match_pos_ = 0;

            // Advance left
            left_->nextTuple();
            if (left_->is_end()) {
                return false;
            }
            left_record_ = left_->Next();

            // Collect all right matches for this left key
            while (!right_->is_end()) {
                auto rec = right_->Next();
                int cmp = compare_keys(*left_record_, *rec);
                if (cmp < 0) {
                    // Right key > left key, need to advance left
                    break;
                }
                right_matches_.push_back(*rec);
                right_->nextTuple();
            }
            // Remove non-matching entries from the start
            size_t i = 0;
            while (i < right_matches_.size()) {
                int cmp = compare_keys(*left_record_, right_matches_[i]);
                if (cmp == 0) break;
                i++;
            }
            right_matches_.erase(right_matches_.begin(), right_matches_.begin() + i);

            if (!right_matches_.empty()) {
                right_record_ = std::make_unique<RmRecord>(right_matches_[0]);
                right_match_pos_ = 1;
                return true;
            }
            // Right exhausted, rewind for next left tuple
            right_->beginTuple();
            if (right_->is_end()) return false;
        }
    }

   public:
    SortMergeJoinExecutor(std::unique_ptr<AbstractExecutor> left,
                          std::unique_ptr<AbstractExecutor> right,
                          std::vector<Condition> conds,
                          std::vector<Condition> equi_conds)
        : conds_(std::move(conds)), equi_conds_(std::move(equi_conds)) {

        // Use SortExecutor wrappers for sorted input
        if (!equi_conds_.empty()) {
            auto left_sort_col = equi_conds_[0].lhs_col;
            auto right_sort_col = equi_conds_[0].rhs_col;
            if (left_sort_col.tab_name != left->cols()[0].tab_name)
                std::swap(left_sort_col, right_sort_col);

            left_ = std::make_unique<SortExecutor>(std::move(left), left_sort_col, false);
            right_ = std::make_unique<SortExecutor>(std::move(right), right_sort_col, false);
        } else {
            left_ = std::move(left);
            right_ = std::move(right);
        }

        len_ = left_->tupleLen() + right_->tupleLen();
        cols_ = left_->cols();
        auto right_cols = right_->cols();
        for (auto &col : right_cols) {
            col.offset += left_->tupleLen();
        }
        cols_.insert(cols_.end(), right_cols.begin(), right_cols.end());
        is_end_ = true;
        right_match_pos_ = 0;
    }

    void beginTuple() override {
        left_->beginTuple();
        if (left_->is_end()) {
            is_end_ = true;
            return;
        }
        left_record_ = left_->Next();

        right_->beginTuple();
        right_matches_.clear();
        right_match_pos_ = 0;

        // Scan right for first match, then check remaining conditions
        while (!right_->is_end()) {
            auto rec = right_->Next();
            int cmp = compare_keys(*left_record_, *rec);
            if (cmp < 0) {
                // left key < right key, advance left
                left_->nextTuple();
                if (left_->is_end()) { is_end_ = true; return; }
                left_record_ = left_->Next();
                continue;
            }
            if (cmp > 0) {
                // left key > right key, advance right
                right_->nextTuple();
                continue;
            }
            // Keys match, buffer all matching right tuples
            while (!right_->is_end()) {
                auto r2 = right_->Next();
                if (compare_keys(*left_record_, *r2) != 0) break;
                right_matches_.push_back(*r2);
                right_->nextTuple();
            }
            right_matches_.push_back(*rec);
            break;
        }

        if (right_matches_.empty()) {
            is_end_ = true;
            return;
        }

        // Find first match that satisfies all conditions
        for (size_t i = 0; i < right_matches_.size(); i++) {
            right_record_ = std::make_unique<RmRecord>(right_matches_[i]);
            if (check_all_conds()) {
                right_match_pos_ = i + 1;
                is_end_ = false;
                return;
            }
        }

        // Try next left tuples
        if (!advance_to_next_match()) {
            is_end_ = true;
            return;
        }

        // Verify the match satisfies all conditions
        if (!check_all_conds()) {
            if (!advance_to_next_match()) {
                is_end_ = true;
                return;
            }
        }
        is_end_ = false;
    }

    void nextTuple() override {
        // First check remaining buffered matches for current left key
        while (right_match_pos_ < right_matches_.size()) {
            right_record_ = std::make_unique<RmRecord>(right_matches_[right_match_pos_++]);
            if (check_all_conds()) return;
        }

        if (!advance_to_next_match()) {
            is_end_ = true;
            return;
        }
        // Verify remaining conditions
        if (!check_all_conds()) {
            if (!advance_to_next_match()) {
                is_end_ = true;
            }
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
