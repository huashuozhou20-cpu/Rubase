/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "analyze.h"
#include <functional>

/**
 * @description: 分析器，进行语义分析和查询重写，需要检查不符合语义规定的部分
 * @param {shared_ptr<ast::TreeNode>} parse parser生成的结果集
 * @return {shared_ptr<Query>} Query 
 */
std::shared_ptr<Query> Analyze::do_analyze(std::shared_ptr<ast::TreeNode> parse)
{
    std::shared_ptr<Query> query = std::make_shared<Query>();
    if (auto x = std::dynamic_pointer_cast<ast::SelectStmt>(parse))
    {
        // 处理表名
        query->tables = std::move(x->tabs);
        // 检查表是否存在
        for (auto &tab_name : query->tables) {
            sm_manager_->db_.get_table(tab_name);  // throws TableNotFoundError
        }

        // 处理 SELECT 投影列
        for (auto &sv_sel_col : x->cols) {
            TabCol sel_col = {.tab_name = sv_sel_col->tab_name, .col_name = sv_sel_col->col_name};
            query->cols.push_back(sel_col);
        }

        // 标记聚合和 DISTINCT
        query->has_agg = x->is_agg;
        query->has_distinct = x->has_distinct;

        std::vector<ColMeta> all_cols;
        get_all_cols(query->tables, all_cols);
        if (query->cols.empty()) {
            // select * : expand to all columns
            for (auto &col : all_cols) {
                TabCol sel_col = {.tab_name = col.tab_name, .col_name = col.name};
                query->cols.push_back(sel_col);
            }
        } else {
            // infer table name from column name
            for (auto &sel_col : query->cols) {
                sel_col = check_column(all_cols, sel_col);  // 列元数据校验
            }
        }

        // 处理 WHERE 条件
        get_clause(x->cond, query->conds);
        check_clause(query->tables, query->conds);

        // 处理 JOIN ON 条件
        for (auto &join : x->joins) {
            if (join->cond) {
                std::vector<Condition> join_conds;
                get_clause(join->cond, join_conds);
                check_clause(query->tables, join_conds);
                query->conds.insert(query->conds.end(), join_conds.begin(), join_conds.end());
            }
        }

        // 处理 GROUP BY
        if (x->group_by) {
            for (auto &gb_col : x->group_by->cols) {
                TabCol gb = {.tab_name = gb_col->tab_name, .col_name = gb_col->col_name};
                gb = check_column(all_cols, gb);
                // 确保 GROUP BY 列出现在 SELECT 列表中
                bool in_select = false;
                for (auto &sel_col : query->cols) {
                    if (sel_col.tab_name == gb.tab_name && sel_col.col_name == gb.col_name) {
                        in_select = true;
                        break;
                    }
                }
                if (!in_select) {
                    throw InternalError("GROUP BY column '" + gb.col_name + "' must appear in SELECT list");
                }
            }
        }

        // 处理 HAVING 条件
        if (x->having) {
            std::vector<Condition> having_conds;
            get_clause(x->having, having_conds);
            check_clause(query->tables, having_conds);
            // HAVING conditions are stored separately in the AST for the executor to use
        }

        // 校验 LIMIT 值
        if (x->limit) {
            if (x->limit->limit <= 0) {
                throw InternalError("LIMIT must be greater than 0");
            }
        }
    } else if (auto x = std::dynamic_pointer_cast<ast::UpdateStmt>(parse)) {
        // 检查表是否存在
        sm_manager_->db_.get_table(x->tab_name);
        query->tables.push_back(x->tab_name);

        // 处理 SET 子句
        for (auto &sv_set : x->set_clauses) {
            std::vector<ColMeta> all_cols;
            get_all_cols({x->tab_name}, all_cols);
            TabCol target = {.tab_name = "", .col_name = sv_set->col_name};
            target = check_column(all_cols, target);
            SetClause set_clause;
            set_clause.lhs = target;
            set_clause.rhs = convert_sv_value(sv_set->val);
            query->set_clauses.push_back(set_clause);
        }

        // 处理 WHERE 条件
        get_clause(x->cond, query->conds);
        check_clause({x->tab_name}, query->conds);
    } else if (auto x = std::dynamic_pointer_cast<ast::DeleteStmt>(parse)) {
        // 检查表是否存在
        sm_manager_->db_.get_table(x->tab_name);
        //处理where条件
        get_clause(x->cond, query->conds);
        check_clause({x->tab_name}, query->conds);        
    } else if (auto x = std::dynamic_pointer_cast<ast::InsertStmt>(parse)) {
        // 处理insert 的values值
        for (auto &sv_val : x->vals) {
            query->values.push_back(convert_sv_value(sv_val));
        }
    } else {
        // do nothing
    }
    query->parse = std::move(parse);
    return query;
}


TabCol Analyze::check_column(const std::vector<ColMeta> &all_cols, TabCol target) {
    if (target.tab_name.empty()) {
        // Table name not specified, infer table name from column name
        std::string tab_name;
        for (auto &col : all_cols) {
            if (col.name == target.col_name) {
                if (!tab_name.empty()) {
                    throw AmbiguousColumnError(target.col_name);
                }
                tab_name = col.tab_name;
            }
        }
        if (tab_name.empty()) {
            throw ColumnNotFoundError(target.col_name);
        }
        target.tab_name = tab_name;
    } else {
        // 校验指定表中的列是否存在
        TabMeta &tab = sm_manager_->db_.get_table(target.tab_name);
        tab.get_col(target.col_name);  // throws ColumnNotFoundError if not found
    }
    return target;
}

void Analyze::get_all_cols(const std::vector<std::string> &tab_names, std::vector<ColMeta> &all_cols) {
    for (auto &sel_tab_name : tab_names) {
        // 这里db_不能写成get_db(), 注意要传指针
        const auto &sel_tab_cols = sm_manager_->db_.get_table(sel_tab_name).cols;
        all_cols.insert(all_cols.end(), sel_tab_cols.begin(), sel_tab_cols.end());
    }
}

void Analyze::get_clause(const std::shared_ptr<ast::CondExpr> &cond, std::vector<Condition> &conds) {
    conds.clear();
    if (!cond) return;

    std::function<void(const std::shared_ptr<ast::CondExpr>&)> traverse;
    traverse = [&](const std::shared_ptr<ast::CondExpr> &node) {
        if (!node) return;

        if (auto logic = std::dynamic_pointer_cast<ast::LogicExpr>(node)) {
            if (logic->op == ast::LOGIC_AND) {
                for (auto &arg : logic->args) {
                    traverse(arg);
                }
            } else if (logic->op == ast::LOGIC_OR) {
                throw InternalError("OR is not yet supported in execution layer");
            } else if (logic->op == ast::LOGIC_NOT) {
                throw InternalError("NOT is not yet supported in execution layer");
            }
        } else if (auto binary = std::dynamic_pointer_cast<ast::BinaryExpr>(node)) {
            Condition c;
            c.lhs_col = {.tab_name = binary->lhs->tab_name, .col_name = binary->lhs->col_name};
            c.op = convert_sv_comp_op(binary->op);
            if (auto rhs_val = std::dynamic_pointer_cast<ast::Value>(binary->rhs)) {
                c.is_rhs_val = true;
                c.rhs_val = convert_sv_value(rhs_val);
            } else if (auto rhs_col = std::dynamic_pointer_cast<ast::Col>(binary->rhs)) {
                c.is_rhs_val = false;
                c.rhs_col = {.tab_name = rhs_col->tab_name, .col_name = rhs_col->col_name};
            }
            conds.push_back(c);
        } else if (auto unary = std::dynamic_pointer_cast<ast::UnaryCondExpr>(node)) {
            throw InternalError("IS NULL / IS NOT NULL is not yet supported in execution layer");
        } else if (auto like = std::dynamic_pointer_cast<ast::LikeExpr>(node)) {
            throw InternalError("LIKE is not yet supported in execution layer");
        } else if (auto between = std::dynamic_pointer_cast<ast::BetweenExpr>(node)) {
            throw InternalError("BETWEEN is not yet supported in execution layer");
        } else if (auto in_expr = std::dynamic_pointer_cast<ast::InExpr>(node)) {
            throw InternalError("IN is not yet supported in execution layer");
        }
    };

    traverse(cond);
}

void Analyze::check_clause(const std::vector<std::string> &tab_names, std::vector<Condition> &conds) {
    // auto all_cols = get_all_cols(tab_names);
    std::vector<ColMeta> all_cols;
    get_all_cols(tab_names, all_cols);
    // Get raw values in where clause
    for (auto &cond : conds) {
        // Infer table name from column name
        cond.lhs_col = check_column(all_cols, cond.lhs_col);
        if (!cond.is_rhs_val) {
            cond.rhs_col = check_column(all_cols, cond.rhs_col);
        }
        TabMeta &lhs_tab = sm_manager_->db_.get_table(cond.lhs_col.tab_name);
        auto lhs_col = lhs_tab.get_col(cond.lhs_col.col_name);
        ColType lhs_type = lhs_col->type;
        ColType rhs_type;
        if (cond.is_rhs_val) {
            cond.rhs_val.init_raw(lhs_col->len);
            rhs_type = cond.rhs_val.type;
        } else {
            TabMeta &rhs_tab = sm_manager_->db_.get_table(cond.rhs_col.tab_name);
            auto rhs_col = rhs_tab.get_col(cond.rhs_col.col_name);
            rhs_type = rhs_col->type;
        }
        if (lhs_type != rhs_type) {
            throw IncompatibleTypeError(coltype2str(lhs_type), coltype2str(rhs_type));
        }
    }
}


Value Analyze::convert_sv_value(const std::shared_ptr<ast::Value> &sv_val) {
    Value val;
    if (auto int_lit = std::dynamic_pointer_cast<ast::IntLit>(sv_val)) {
        val.set_int(int_lit->val);
    } else if (auto float_lit = std::dynamic_pointer_cast<ast::FloatLit>(sv_val)) {
        val.set_float(float_lit->val);
    } else if (auto str_lit = std::dynamic_pointer_cast<ast::StringLit>(sv_val)) {
        val.set_str(str_lit->val);
    } else if (auto bool_lit = std::dynamic_pointer_cast<ast::BoolLit>(sv_val)) {
        // store bool as int: 1 for true, 0 for false
        val.set_int(bool_lit->val ? 1 : 0);
    } else if (auto null_lit = std::dynamic_pointer_cast<ast::NullLit>(sv_val)) {
        throw InternalError("NULL literal not yet supported in execution layer");
    } else {
        throw InternalError("Unexpected sv value type");
    }
    return val;
}

CompOp Analyze::convert_sv_comp_op(ast::SvCompOp op) {
    std::map<ast::SvCompOp, CompOp> m = {
        {ast::SV_OP_EQ, OP_EQ}, {ast::SV_OP_NE, OP_NE}, {ast::SV_OP_LT, OP_LT},
        {ast::SV_OP_GT, OP_GT}, {ast::SV_OP_LE, OP_LE}, {ast::SV_OP_GE, OP_GE},
    };
    return m.at(op);
}
