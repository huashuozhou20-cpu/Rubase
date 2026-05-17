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

class ProjectionExecutor : public AbstractExecutor {
   private:
    std::unique_ptr<AbstractExecutor> prev_;        // 投影节点的儿子节点
    std::vector<ColMeta> cols_;                     // 需要投影的字段
    size_t len_;                                    // 字段总长度
    std::vector<size_t> sel_idxs_;

   public:
    ProjectionExecutor(std::unique_ptr<AbstractExecutor> prev, const std::vector<TabCol> &sel_cols) {
        prev_ = std::move(prev);

        size_t curr_offset = 0;
        auto &prev_cols = prev_->cols();
        std::vector<bool> used(prev_cols.size(), false);
        for (auto &sel_col : sel_cols) {
            // Find first matching column that hasn't been used yet
            size_t idx = 0;
            for (; idx < prev_cols.size(); idx++) {
                if (!used[idx] && prev_cols[idx].tab_name == sel_col.tab_name &&
                    prev_cols[idx].name == sel_col.col_name) {
                    used[idx] = true;
                    break;
                }
            }
            if (idx == prev_cols.size()) {
                throw ColumnNotFoundError(sel_col.tab_name + '.' + sel_col.col_name);
            }
            sel_idxs_.push_back(idx);
            auto col = prev_cols[idx];
            col.offset = curr_offset;
            curr_offset += col.len;
            cols_.push_back(col);
        }
        len_ = curr_offset;
    }

    void beginTuple() override { prev_->beginTuple(); }

    void nextTuple() override { prev_->nextTuple(); }

    bool is_end() const override { return prev_->is_end(); }

    size_t tupleLen() const override { return len_; }

    const std::vector<ColMeta> &cols() const override { return cols_; }

    std::unique_ptr<RmRecord> Next() override {
        auto prev_rec = prev_->Next();
        if (!prev_rec) return nullptr;
        auto proj_rec = std::make_unique<RmRecord>(len_);
        for (size_t i = 0; i < sel_idxs_.size(); i++) {
            auto &col = cols_[i];
            memcpy(proj_rec->data + col.offset, prev_rec->data + prev_->cols()[sel_idxs_[i]].offset, col.len);
        }
        return proj_rec;
    }

    ColMeta get_col_offset(const TabCol &target) override {
        for (auto &col : cols_) {
            if (col.name == target.col_name &&
                (target.tab_name.empty() || col.tab_name == target.tab_name))
                return col;
        }
        return ColMeta{};
    }

    Rid &rid() override { return _abstract_rid; }
};