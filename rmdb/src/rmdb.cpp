/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <atomic>
#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "errors.h"
#include "optimizer/optimizer.h"
#include "recovery/log_recovery.h"
#include "optimizer/plan.h"
#include "optimizer/planner.h"
#include "portal.h"
#include "analyze/analyze.h"
#include "execution/executor_abstract.h"
#ifdef ENABLE_PROFILING
#include "common/sampler.h"
#endif
#include "network/epoll_server.h"

#define DEFAULT_PORT 8765

// 构建全局所需的管理器对象
auto disk_manager = std::make_unique<DiskManager>();
auto buffer_pool_manager = std::make_unique<BufferPoolManager>(BUFFER_POOL_SIZE, disk_manager.get());
auto rm_manager = std::make_unique<RmManager>(disk_manager.get(), buffer_pool_manager.get());
auto ix_manager = std::make_unique<IxManager>(disk_manager.get(), buffer_pool_manager.get());
auto sm_manager = std::make_unique<SmManager>(disk_manager.get(), buffer_pool_manager.get(), rm_manager.get(), ix_manager.get());
auto lock_manager = std::make_unique<LockManager>();
auto txn_manager = std::make_unique<TransactionManager>(lock_manager.get(), sm_manager.get(),
                                                         ConcurrencyMode::MVCC);
auto planner = std::make_unique<Planner>(sm_manager.get());
auto optimizer = std::make_unique<Optimizer>(sm_manager.get(), planner.get());
auto ql_manager = std::make_unique<QlManager>(sm_manager.get(), txn_manager.get(), planner.get());
auto log_manager = std::make_unique<LogManager>(disk_manager.get());
auto recovery = std::make_unique<RecoveryManager>(disk_manager.get(), buffer_pool_manager.get(), sm_manager.get());
auto portal = std::make_unique<Portal>(sm_manager.get());
auto analyze = std::make_unique<Analyze>(sm_manager.get());

// View definitions: name → SelectStmt AST
std::map<std::string, std::shared_ptr<ast::TreeNode>> view_defs;
std::mutex view_mutex;
static pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;

// Epoll server pointer for signal handler
static EpollServer *g_server = nullptr;

static void sigint_handler(int /*signo*/) {
#ifdef ENABLE_PROFILING
    Sampler::stop();
#endif
    log_manager->flush_log_to_disk();
    std::cout << "The Server received Ctrl+C, will be closed\n";
    if (g_server) g_server->stop();
}

// Start a fresh auto-commit transaction on the calling worker thread.
// In the epoll model, different queries from the same connection may be
// processed by different workers, so we cannot reuse a transaction object
// across threads.  Explicit multi-statement transactions (BEGIN / COMMIT)
// are not yet supported in the epoll model.
static int64_t begin_autocommit_txn() {
    auto *txn = txn_manager->begin(nullptr, log_manager.get());
    txn->set_txn_mode(false);
    return txn->get_transaction_id();
}

// Resolve scalar subqueries in AST condition tree by executing them
// and replacing SubqueryExpr with literal values.
void resolve_subqueries(std::shared_ptr<ast::TreeNode> node) {
    if (!node) return;
    // Process condition expressions recursively
    if (auto binary = std::dynamic_pointer_cast<ast::BinaryExpr>(node)) {
        resolve_subqueries(binary->lhs);
        if (auto sub = std::dynamic_pointer_cast<ast::SubqueryExpr>(binary->rhs)) {
            // Execute scalar subquery and replace with result value
            try {
                Analyze sub_analyze(sm_manager.get());
                auto sub_query = sub_analyze.do_analyze(sub->subquery);
                char sub_buf[BUFFER_LENGTH];
                int sub_offset = 0;
                auto sub_txn = txn_manager->begin(nullptr, log_manager.get());
                Context sub_ctx(lock_manager.get(), log_manager.get(), sub_txn, sub_buf, &sub_offset);
                sub_ctx.txn_mgr_ = txn_manager.get();
                auto sub_plan = planner->do_planner(sub_query, &sub_ctx);
                // Unwrap DMLPlan wrapper
                if (auto dml = std::dynamic_pointer_cast<DMLPlan>(sub_plan))
                    sub_plan = dml->subplan_;
                auto root_exec = portal->convert_plan_executor(sub_plan, &sub_ctx);
                if (!root_exec) {
                    txn_manager->abort(sub_txn, log_manager.get()); return;
                }
                root_exec->beginTuple();
                if (!root_exec->is_end()) {
                    auto rec = root_exec->Next();
                    if (!rec) { txn_manager->abort(sub_txn, log_manager.get()); return; }
                    auto &cols = root_exec->cols();
                    if (!cols.empty()) {
                        auto &col = cols[0];
                        if (col.type == TYPE_INT)
                            binary->rhs = std::make_shared<ast::IntLit>(*(int *)(rec->data + col.offset));
                        else if (col.type == TYPE_FLOAT)
                            binary->rhs = std::make_shared<ast::FloatLit>(*(float *)(rec->data + col.offset));
                        else
                            binary->rhs = std::make_shared<ast::FloatLit>(0);
                    }
                } else {
                    // Empty set: replace with NULL so the outer comparison
                    // evaluates to NULL (false in WHERE context → 0 rows).
                    binary->rhs = std::make_shared<ast::NullLit>();
                }
                txn_manager->commit(sub_txn, log_manager.get());
            } catch (RMDBError &e) {
#ifndef NDEBUG
                std::cerr << "Subquery failed: " << e.what() << std::endl;
#endif
            }
        } else {
            resolve_subqueries(binary->rhs);
        }
    } else if (auto logic = std::dynamic_pointer_cast<ast::LogicExpr>(node)) {
        for (auto &arg : logic->args) resolve_subqueries(arg);
    } else if (auto in_expr = std::dynamic_pointer_cast<ast::InExpr>(node)) {
        // Resolve IN subquery: execute and collect all values
        if (in_expr->subquery) {
            try {
                Analyze sub_analyze(sm_manager.get());
                auto sub_query = sub_analyze.do_analyze(in_expr->subquery);
                char sub_buf[BUFFER_LENGTH]; int sub_offset = 0;
                auto sub_txn = txn_manager->begin(nullptr, log_manager.get());
                Context sub_ctx(lock_manager.get(), log_manager.get(), sub_txn, sub_buf, &sub_offset);
                sub_ctx.txn_mgr_ = txn_manager.get();
                auto sub_plan = planner->do_planner(sub_query, &sub_ctx);
                if (auto dml = std::dynamic_pointer_cast<DMLPlan>(sub_plan))
                    sub_plan = dml->subplan_;
                auto root_exec = portal->convert_plan_executor(sub_plan, &sub_ctx);
                if (root_exec) {
                    root_exec->beginTuple();
                    auto &cols = root_exec->cols();
                    while (!root_exec->is_end()) {
                        auto rec = root_exec->Next();
                        if (rec && !cols.empty()) {
                            auto &col = cols[0];
                            if (col.type == TYPE_INT)
                                in_expr->values.push_back(std::make_shared<ast::IntLit>(*(int*)(rec->data+col.offset)));
                            else if (col.type == TYPE_FLOAT)
                                in_expr->values.push_back(std::make_shared<ast::FloatLit>(*(float*)(rec->data+col.offset)));
                            else if (col.type == TYPE_STRING) {
                                std::string s(rec->data+col.offset, col.len);
                                s = s.c_str();
                                in_expr->values.push_back(std::make_shared<ast::StringLit>(s));
                            }
                        }
                        root_exec->nextTuple();
                    }
                }
                txn_manager->commit(sub_txn, log_manager.get());
            } catch (RMDBError &e) {}
            in_expr->subquery = nullptr;  // Mark as resolved
        }
    }
}

// ============================================================================
// Fast-path SQL dispatch: bypass yyparse() for known sysbench OLTP patterns.
// The parser is a serialization point (buffer_mutex) and a CPU hotspot —
// constructing the AST directly skips both costs for the hot workload.
// Returns nullptr if the statement does not match a recognised pattern.
// ============================================================================
static std::shared_ptr<ast::TreeNode> try_fast_path(const std::string &stmt_str) {
    const char *s = stmt_str.c_str();
    while (*s == ' ' || *s == '\t' || *s == '\n') ++s;

    char tab[64];
    int v1 = 0, v2 = 0, pos = 0;

    // ---- UPDATE <table> SET val=<int> WHERE id=<int> ----
    if (sscanf(s, "UPDATE %63s SET val = %d WHERE id = %d %n", tab, &v1, &v2, &pos) >= 3 && pos > 0) {
        // Verify remaining is only trailing ';' and whitespace
        for (const char *p = s + pos; *p; ++p)
            if (*p != ' ' && *p != ';' && *p != '\t' && *p != '\n') goto not_update;
        std::vector<std::shared_ptr<ast::SetClause>> set_clauses;
        set_clauses.push_back(std::make_shared<ast::SetClause>("val", std::make_shared<ast::IntLit>(v1)));
        auto lhs = std::make_shared<ast::Col>("", "id");
        auto rhs = std::make_shared<ast::IntLit>(v2);
        auto cond = std::make_shared<ast::BinaryExpr>(lhs, ast::SV_OP_EQ, rhs);
        return std::make_shared<ast::UpdateStmt>(std::string(tab), std::move(set_clauses), cond);
    }
    not_update:

    // ---- DELETE FROM <table> WHERE id=<int> ----
    pos = 0;
    if (sscanf(s, "DELETE FROM %63s WHERE id = %d %n", tab, &v1, &pos) >= 2 && pos > 0) {
        for (const char *p = s + pos; *p; ++p)
            if (*p != ' ' && *p != ';' && *p != '\t' && *p != '\n') goto not_delete;
        auto lhs = std::make_shared<ast::Col>("", "id");
        auto rhs = std::make_shared<ast::IntLit>(v1);
        auto cond = std::make_shared<ast::BinaryExpr>(lhs, ast::SV_OP_EQ, rhs);
        return std::make_shared<ast::DeleteStmt>(std::string(tab), cond);
    }
    not_delete:

    // ---- SELECT * FROM <table> WHERE id BETWEEN <int> AND <int> AND val + 1 > 0 ----
    pos = 0;
    if (sscanf(s, "SELECT * FROM %63s WHERE id BETWEEN %d AND %d AND val + 1 > 0 %n",
               tab, &v1, &v2, &pos) >= 3 && pos > 0) {
        for (const char *p = s + pos; *p; ++p)
            if (*p != ' ' && *p != ';' && *p != '\t' && *p != '\n') goto not_select;
        auto between = std::make_shared<ast::BetweenExpr>(
            std::make_shared<ast::Col>("", "id"), false,
            std::make_shared<ast::IntLit>(v1), std::make_shared<ast::IntLit>(v2));
        auto val_plus_1 = std::make_shared<ast::ArithExpr>(
            std::make_shared<ast::Col>("", "val"), ast::ARITH_ADD,
            std::make_shared<ast::IntLit>(1));
        auto gt_zero = std::make_shared<ast::BinaryExpr>(
            val_plus_1, ast::SV_OP_GT, std::make_shared<ast::IntLit>(0));
        std::vector<std::shared_ptr<ast::CondExpr>> args;
        args.push_back(between);
        args.push_back(gt_zero);
        auto cond = std::make_shared<ast::LogicExpr>(ast::LOGIC_AND, std::move(args));
        auto sel = std::make_shared<ast::SelectStmt>();
        sel->tabs.push_back(std::string(tab));
        sel->cond = cond;
        return sel;
    }
    not_select:

    // ---- INSERT INTO <table> VALUES(<int>, <int>, '<str>') ----
    pos = 0;
    char padding[256];
    if (sscanf(s, "INSERT INTO %63s VALUES ( %d , %d , '%255[^']' ) %n",
               tab, &v1, &v2, padding, &pos) >= 4 && pos > 0) {
        for (const char *p = s + pos; *p; ++p)
            if (*p != ' ' && *p != ';' && *p != '\t' && *p != '\n') goto not_insert;
        std::vector<std::shared_ptr<ast::Value>> row;
        row.push_back(std::make_shared<ast::IntLit>(v1));
        row.push_back(std::make_shared<ast::IntLit>(v2));
        row.push_back(std::make_shared<ast::StringLit>(std::string(padding)));
        std::vector<std::vector<std::shared_ptr<ast::Value>>> vals;
        vals.push_back(std::move(row));
        return std::make_shared<ast::InsertStmt>(std::string(tab),
            std::vector<std::string>{}, std::move(vals));
    }
    not_insert:

    return nullptr;
}

// ============================================================================
// Per-query processing function — called by worker pool threads.
// Each call handles exactly one SQL statement on one connection.
// Results are written back via g_server->enqueue_response().
// ============================================================================
static void process_query(int conn_fd, const std::string &stmt_str) {
    // Per-query output buffer
    char data_send[BUFFER_LENGTH];
    memset(data_send, 0, BUFFER_LENGTH);
    int offset = 0;

    // Register this worker thread's active read timestamp for GC watermark.
    // Thread-local slot persists across queries on the same worker.
    static thread_local int gc_slot = txn_manager->RegisterThread();

    // Fresh auto-commit transaction for every query (epoll workers are pooled)
    int64_t txn_id = begin_autocommit_txn();
    Context *context = new Context(lock_manager.get(), log_manager.get(), nullptr,
                                   data_send, &offset);
    context->txn_mgr_ = txn_manager.get();
    context->txn_ = txn_manager->get_transaction(txn_id);

    // Publish current read timestamp so GC knows this thread is active
    if (gc_slot >= 0 && context->txn_) {
        txn_manager->SetThreadActiveTs(gc_slot, context->txn_->get_read_ts());
    }
    context->txn_mgr_ = txn_manager.get();
    context->txn_ = txn_manager->get_transaction(txn_id);

    // ---- Phase 1: build AST (fast-path or full parser) ----
    // The fast path constructs the AST directly from a string-prefix match,
    // skipping the yyparse() CPU overhead.  do_analyze() still runs under
    // buffer_mutex because it may touch shared catalog / metadata state that
    // was originally serialised by the parser mutex.
    std::shared_ptr<ast::TreeNode> local_ast = try_fast_path(stmt_str);

    YY_BUFFER_STATE parser_buf = nullptr;
    bool parser_mutex_held = false;

    if (!local_ast) {
        pthread_mutex_lock(&buffer_mutex);
        parser_mutex_held = true;
        parser_buf = yy_scan_string(stmt_str.c_str());
        if (yyparse() != 0 || ast::parse_tree == nullptr) {
            yy_delete_buffer(parser_buf);
            pthread_mutex_unlock(&buffer_mutex);
            parser_mutex_held = false;
            std::string err = "Parser Error: syntax error\n";
            memcpy(data_send, err.c_str(), err.length());
            offset = err.length();
            goto send_response;
        }
        local_ast = ast::parse_tree;
    } else {
        // Fast-path succeeded: acquire mutex for analysis phase.
        // We still serialise do_analyze() to match the original contract.
        pthread_mutex_lock(&buffer_mutex);
        parser_mutex_held = true;
    }

    // ---- Phase 2: analyse + execute AST (common for both paths) ----
    if (local_ast != nullptr) {
        try {
            // CREATE VIEW / DROP VIEW (parser path only — not in fast-path patterns)
            if (auto cv = std::dynamic_pointer_cast<ast::CreateView>(local_ast)) {
                {
                    std::lock_guard<std::mutex> lock(view_mutex);
                    view_defs[cv->view_name] = cv->select_stmt;
                }
                sm_manager->create_view(cv->view_name, "");
                Result r{Result::SUCCESS, ""};
                memcpy(data_send, r.msg.c_str(), r.msg.length());
                offset = r.msg.length();
                goto cleanup_parser;
            }
            if (auto dv = std::dynamic_pointer_cast<ast::DropView>(local_ast)) {
                {
                    std::lock_guard<std::mutex> lock(view_mutex);
                    view_defs.erase(dv->view_name);
                }
                sm_manager->drop_view(dv->view_name);
                Result r{Result::SUCCESS, ""};
                memcpy(data_send, r.msg.c_str(), r.msg.length());
                offset = r.msg.length();
                goto cleanup_parser;
            }
            if (auto stmt = std::dynamic_pointer_cast<ast::SelectStmt>(local_ast)) {
                resolve_subqueries(stmt->cond);
            }
            std::shared_ptr<Query> query = analyze->do_analyze(local_ast);

            // Release parser resources now that analysis consumed the AST
            if (parser_mutex_held) {
                if (parser_buf) yy_delete_buffer(parser_buf);
                pthread_mutex_unlock(&buffer_mutex);
                parser_mutex_held = false;
            }

            std::shared_ptr<Plan> plan = optimizer->plan_query(query, context);
            if (auto dml = std::dynamic_pointer_cast<DMLPlan>(plan)) {
                if (dml->is_for_update_ && context->txn_) {
                    context->txn_->set_read_only(false);
                    context->is_for_update_ = true;
                }
            }
            std::shared_ptr<PortalStmt> portalStmt = portal->start(plan, context);
            portal->run(portalStmt, ql_manager.get(), &txn_id, context);
            portal->drop();
        } catch (TransactionAbortException &e) {
            Result result{Result::ABORT, "abort\n"};
            memcpy(data_send, result.msg.c_str(), result.msg.length());
            offset = result.msg.length();
            txn_manager->abort(context->txn_, log_manager.get());
        } catch (RMDBError &e) {
            Result result{Result::FAILURE, std::string(e.what()) + "\n"};
            memcpy(data_send, result.msg.c_str(), result.msg.length());
            offset = result.msg.length();
        }
    }

cleanup_parser:
    if (parser_mutex_held) {
        if (parser_buf) yy_delete_buffer(parser_buf);
        pthread_mutex_unlock(&buffer_mutex);
    }

send_response:
    // Send result via epoll server
    if (offset == 0) {
        data_send[0] = '\n';
        offset = 1;
    }
    if (g_server) {
        g_server->enqueue_response(conn_fd, data_send, static_cast<size_t>(offset));
    }

    // Autocommit single-statement transactions
    if (context->txn_ && !context->txn_->get_txn_mode()) {
        txn_manager->commit(context->txn_, log_manager.get());
    }
    // Mark this thread as idle for GC watermark
    if (gc_slot >= 0) {
        txn_manager->SetThreadActiveTs(gc_slot, INT64_MAX);
    }
    delete context;
}

// ---- Epoll-based server main -------------------------------------------------


// ============================================================================
// Epoll-based server main — single I/O thread + worker pool
// ============================================================================
int main(int argc, char **argv) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <database> [port]" << std::endl;
        exit(1);
    }

    int port = DEFAULT_PORT;
    if (argc >= 3) {
        port = std::stoi(argv[2]);
    }

    signal(SIGINT, sigint_handler);
    try {
        std::cout << "\n"
                     "  _____  __  __ _____  ____  \n"
                     " |  __ \\|  \\/  |  __ \\|  _ \\ \n"
                     " | |__) | \\  / | |  | | |_) |\n"
                     " |  _  /| |\\/| | |  | |  _ < \n"
                     " | | \\ \\| |  | | |__| | |_) |\n"
                     " |_|  \\_\\_|  |_|_____/|____/ \n"
                     "\n"
                     "Welcome to RMDB!  (epoll + worker pool)\n"
                     "Type 'help;' for help.\n"
                     "\n";

        std::string db_name = argv[1];
        if (!sm_manager->is_dir(db_name)) {
            sm_manager->create_db(db_name);
        }
        sm_manager->open_db(db_name);

        // ARIES recovery
        recovery->analyze();
        recovery->redo();
        recovery->undo();
        recovery->rebuild_indexes();

        if (recovery->max_lsn() != INVALID_LSN) {
            log_manager->set_global_lsn(recovery->max_lsn() + 1);
        }

        // Launch epoll-based server with worker pool
        int num_workers = static_cast<int>(std::thread::hardware_concurrency());
        if (num_workers < 4) num_workers = 4;
        std::cout << "[server] epoll Reactor + " << num_workers
                  << " worker threads on port " << port << "\n";

        EpollServer server(port, process_query, num_workers);
        g_server = &server;

#ifdef ENABLE_PROFILING
        // Start CPU profiler after all initialization is complete
        Sampler::start("/tmp/rmdb_samples.bin");
#endif

        server.run();
        g_server = nullptr;

    } catch (RMDBError &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    sm_manager->close_db();
    std::cout << " DB has been closed.\nServer shuts down." << std::endl;
    return 0;
}
