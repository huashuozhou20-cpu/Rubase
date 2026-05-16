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
        };

        for (auto &cond : conds_) {
            if (cond.lhs_col.tab_name != tab_name_) {
                // lhs is on other table, now rhs must be on this table
                assert(!cond.is_rhs_val && cond.rhs_col.tab_name == tab_name_);
                // swap lhs and rhs
                std::swap(cond.lhs_col, cond.rhs_col);
                cond.op = swap_op.at(cond.op);
            }
        }
        fed_conds_ = conds_;
        is_end_ = true;
    }

    void beginTuple() override {
        auto ih = sm_manager_->ihs_
                      .at(sm_manager_->get_ix_manager()->get_index_name(tab_name_, index_meta_.cols))
                      .get();

        // 从等值条件中提取key，构造查找范围
        char *key = new char[index_meta_.col_tot_len];
        memset(key, 0, index_meta_.col_tot_len);
        int offset = 0;
        for (size_t i = 0; i < index_meta_.col_num; i++) {
            // 查找匹配当前索引列的等值条件
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
        scan_->next();
        if (scan_->is_end()) {
            is_end_ = true;
            return;
        }
        rid_ = scan_->rid();
    }

    bool is_end() const override { return is_end_; }

    size_t tupleLen() const override { return len_; }

    const std::vector<ColMeta> &cols() const override { return cols_; }

    std::unique_ptr<RmRecord> Next() override {
        if (is_end_) return nullptr;
        return fh_->get_record(rid_, context_);
    }

    Rid &rid() override { return rid_; }
};