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

class InsertExecutor : public AbstractExecutor {
   private:
    TabMeta tab_;                   // 表的元数据
    std::vector<std::vector<Value>> values_list_;  // 多行插入数据
    std::vector<std::string> col_names_;  // 可选的列名列表
    RmFileHandle *fh_;              // 表的数据文件句柄
    std::string tab_name_;          // 表名称
    Rid rid_;
    SmManager *sm_manager_;
    size_t current_row_ = 0;

    // Build a mapping from column name to index in the table
    std::map<std::string, int> col_name_to_idx_;

   public:
    InsertExecutor(SmManager *sm_manager, const std::string &tab_name,
                   std::vector<std::vector<Value>> values_list,
                   std::vector<std::string> col_names, Context *context) {
        sm_manager_ = sm_manager;
        tab_ = sm_manager_->db_.get_table(tab_name);
        values_list_ = std::move(values_list);
        col_names_ = std::move(col_names);
        tab_name_ = tab_name;

        // Build column name → index map
        for (size_t i = 0; i < tab_.cols.size(); i++) {
            col_name_to_idx_[tab_.cols[i].name] = (int)i;
        }

        // Validate row sizes
        size_t expected = col_names_.empty() ? tab_.cols.size() : col_names_.size();
        for (auto &row : values_list_) {
            if (row.size() != expected) {
                throw InvalidValueCountError();
            }
        }
        fh_ = sm_manager_->fhs_.at(tab_name).get();
        context_ = context;
    };

    std::unique_ptr<RmRecord> Next() override {
        while (current_row_ < values_list_.size()) {
            auto &row_vals = values_list_[current_row_++];
            // Make record buffer (initially all zeros = NULL)
            RmRecord rec(fh_->get_file_hdr().record_size);
            memset(rec.data, 0, fh_->get_file_hdr().record_size);

            // Map values to table columns
            for (size_t vi = 0; vi < row_vals.size(); vi++) {
                auto &val = row_vals[vi];
                ColMeta *col;
                if (col_names_.empty()) {
                    // Default: values are in table column order
                    col = &tab_.cols[vi];
                } else {
                    // Column list provided: look up column by name
                    auto it = col_name_to_idx_.find(col_names_[vi]);
                    if (it == col_name_to_idx_.end()) {
                        throw RMDBError("Column '" + col_names_[vi] + "' not found in table '" + tab_name_ + "'");
                    }
                    col = &tab_.cols[it->second];
                }
                if (col->type != val.type) {
                    throw IncompatibleTypeError(coltype2str(col->type), coltype2str(val.type));
                }
                if (col->not_null && val.is_null_) {
                    throw RMDBError("Column '" + col->name + "' cannot be NULL");
                }
                val.init_raw(col->len);
                memcpy(rec.data + col->offset, val.raw->data, col->len);
            }
            // Insert into record file
            rid_ = fh_->insert_record(rec.data, context_);

            // Insert into index
            for (size_t i = 0; i < tab_.indexes.size(); ++i) {
                auto &index = tab_.indexes[i];
                auto ih = sm_manager_->ihs_.at(sm_manager_->get_ix_manager()->get_index_name(tab_name_, index.cols)).get();
                char *key = new char[index.col_tot_len];
                int offset = 0;
                for (size_t j = 0; j < static_cast<size_t>(index.col_num); ++j) {
                    memcpy(key + offset, rec.data + index.cols[j].offset, index.cols[j].len);
                    offset += index.cols[j].len;
                }
                ih->insert_entry(key, rid_, context_->txn_);
                delete[] key;
            }
        }
        return nullptr;
    }
    Rid &rid() override { return rid_; }
};