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
#include <readline/history.h>
#include <readline/readline.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <atomic>

#include "errors.h"
#include "optimizer/optimizer.h"
#include "recovery/log_recovery.h"
#include "optimizer/plan.h"
#include "optimizer/planner.h"
#include "portal.h"
#include "analyze/analyze.h"
#include "execution/executor_abstract.h"

#define DEFAULT_PORT 8765
#define MAX_CONN_LIMIT 128

static bool should_exit = false;
static std::atomic<int> active_connections{0};

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
pthread_mutex_t *buffer_mutex;
pthread_mutex_t *sockfd_mutex;

static jmp_buf jmpbuf;
void sigint_handler(int signo) {
    should_exit = true;
    log_manager->flush_log_to_disk();
    std::cout << "The Server receive Crtl+C, will been closed\n";
    longjmp(jmpbuf, 1);
}

// 判断当前正在执行的是显式事务还是单条SQL语句的事务，并更新事务ID
void SetTransaction(txn_id_t *txn_id, Context *context) {
    context->txn_ = txn_manager->get_transaction(*txn_id);
    if(context->txn_ == nullptr || context->txn_->get_state() == TransactionState::COMMITTED ||
        context->txn_->get_state() == TransactionState::ABORTED) {
        context->txn_ = txn_manager->begin(nullptr, context->log_mgr_);
        *txn_id = context->txn_->get_transaction_id();
        context->txn_->set_txn_mode(false);
    }
}

// 将格式化的结果发送给客户端
static int send_result_to_client(int fd, const char *data, int len) {
    if (len <= 0) return 0;
    int total = 0;
    while (total < len) {
        int sent = write(fd, data + total, len - total);
        if (sent <= 0) return -1;
        total += sent;
    }
    return total;
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
                std::cerr << "Subquery failed: " << e.what() << std::endl;
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

void *client_handler(void *sock_fd) {
    int fd = *((int *)sock_fd);
    delete (int *)sock_fd;  // heap-allocated by accept loop
    pthread_mutex_unlock(sockfd_mutex);

    active_connections.fetch_add(1);

    int i_recvBytes;
    // 接收客户端发送的请求
    char data_recv[BUFFER_LENGTH];
    // 需要返回给客户端的结果
    char *data_send = new char[BUFFER_LENGTH];
    // 需要返回给客户端的结果的长度
    int offset = 0;
    // 记录客户端当前正在执行的事务ID
    txn_id_t txn_id = INVALID_TXN_ID;

    std::string output = "establish client connection, sockfd: " + std::to_string(fd) + "\n";
    std::cout << output;

    // Accumulation buffer for multi-line statements
    std::string accum_buf;
    accum_buf.reserve(BUFFER_LENGTH * 4);

    while (true) {
        std::cout << "Waiting for request..." << std::endl;
        memset(data_recv, 0, BUFFER_LENGTH);

        i_recvBytes = read(fd, data_recv, BUFFER_LENGTH - 1);

        if (i_recvBytes == 0) {
            std::cout << "Maybe the client has closed" << std::endl;
            break;
        }
        if (i_recvBytes == -1) {
            std::cout << "Client read error!" << std::endl;
            break;
        }
        data_recv[i_recvBytes] = '\0';

        printf("i_recvBytes: %d \n ", i_recvBytes);

        if (strcmp(data_recv, "exit") == 0) {
            std::cout << "Client exit." << std::endl;
            break;
        }
        if (strcmp(data_recv, "crash") == 0) {
            std::cout << "Server crash" << std::endl;
            exit(1);
        }

        std::cout << "Read from client " << fd << ": " << data_recv << std::endl;

        // Append to accumulation buffer for multi-line support (strip \r)
        for (char *p = data_recv; *p; p++)
            if (*p != '\r') accum_buf += *p;

        // Check if we have a complete statement (ends with ';')
        // Trim trailing whitespace for the check
        std::string trimmed = accum_buf;
        while (!trimmed.empty() && (trimmed.back() == ' ' || trimmed.back() == '\t' ||
               trimmed.back() == '\n' || trimmed.back() == '\r')) {
            trimmed.pop_back();
        }
        if (trimmed.empty() || trimmed.back() != ';') {
            // Incomplete statement, wait for more input
            continue;
        }

        // Process all ;-separated statements
        const char *remaining = accum_buf.c_str();
        bool send_error = false;
        while (*remaining) {
            // Skip whitespace between statements
            while (*remaining == ' ' || *remaining == '\t' ||
                   *remaining == '\n' || *remaining == '\r')
                remaining++;
            if (!*remaining) break;

            // Find end of this statement (next ';')
            const char *semi = strchr(remaining, ';');
            if (!semi) break;

            // Extract this statement including the ';'
            std::string stmt(remaining, semi - remaining + 1);

            // Skip empty or whitespace-only statements
            bool has_content = false;
            for (char c : stmt) {
                if (c != ';' && c != ' ' && c != '\t' && c != '\n' && c != '\r') {
                    has_content = true;
                    break;
                }
            }
            if (!has_content) {
                remaining = semi + 1;
                continue;
            }

            memset(data_send, '\0', BUFFER_LENGTH);
            offset = 0;

            // 开启事务，初始化系统所需的上下文信息
            Context *context = new Context(lock_manager.get(), log_manager.get(), nullptr, data_send, &offset);
            context->txn_mgr_ = txn_manager.get();
            SetTransaction(&txn_id, context);

            // 用于判断是否已经调用了yy_delete_buffer来删除buf
            bool finish_analyze = false;
            pthread_mutex_lock(buffer_mutex);
            YY_BUFFER_STATE buf = yy_scan_string(stmt.c_str());
            if (yyparse() == 0) {
                if (ast::parse_tree != nullptr) {
                    try {
                        // Handle CREATE VIEW / DROP VIEW
                        if (auto cv = std::dynamic_pointer_cast<ast::CreateView>(ast::parse_tree)) {
                            view_defs[cv->view_name] = cv->select_stmt;
                            sm_manager->create_view(cv->view_name, "");
                            Result r{Result::SUCCESS, ""};
                            memcpy(data_send, r.msg.c_str(), r.msg.length());
                            offset = r.msg.length();
                            yy_delete_buffer(buf);
                            finish_analyze = true;
                            pthread_mutex_unlock(buffer_mutex);
                            goto send_response;
                        }
                        if (auto dv = std::dynamic_pointer_cast<ast::DropView>(ast::parse_tree)) {
                            view_defs.erase(dv->view_name);
                            sm_manager->drop_view(dv->view_name);
                            Result r{Result::SUCCESS, ""};
                            memcpy(data_send, r.msg.c_str(), r.msg.length());
                            offset = r.msg.length();
                            yy_delete_buffer(buf);
                            finish_analyze = true;
                            pthread_mutex_unlock(buffer_mutex);
                            goto send_response;
                        }
                        // Resolve subqueries in WHERE/HAVING conditions before analysis
                        if (auto stmt = std::dynamic_pointer_cast<ast::SelectStmt>(ast::parse_tree)) {
                            resolve_subqueries(stmt->cond);
                        }
                        // analyze and rewrite
                        std::shared_ptr<Query> query = analyze->do_analyze(ast::parse_tree);
                        yy_delete_buffer(buf);
                        finish_analyze = true;
                        pthread_mutex_unlock(buffer_mutex);
                        // 优化器
                        std::shared_ptr<Plan> plan = optimizer->plan_query(query, context);

                        // FOR UPDATE: mark txn read-write + flag context for X-lock routing
                        if (auto dml = std::dynamic_pointer_cast<DMLPlan>(plan)) {
                            if (dml->is_for_update_ && context->txn_) {
                                context->txn_->set_read_only(false);
                                context->is_for_update_ = true;
                            }
                        }

                        // portal
                        std::shared_ptr<PortalStmt> portalStmt = portal->start(plan, context);
                        portal->run(portalStmt, ql_manager.get(), &txn_id, context);
                        portal->drop();
                    } catch (TransactionAbortException &e) {
                        // 事务需要回滚，格式化abort结果返回给客户端
                        Result result{Result::ABORT, "abort\n"};
                        memcpy(data_send, result.msg.c_str(), result.msg.length());
                        offset = result.msg.length();

                        // 回滚事务
                        txn_manager->abort(context->txn_, log_manager.get());
                        std::cout << e.GetInfo() << std::endl;

                        std::fstream outfile;
                        outfile.open("output.txt", std::ios::out | std::ios::app);
                        outfile << result.msg;
                        outfile.close();
                    } catch (RMDBError &e) {
                        // 格式化错误结果返回给客户端
                        std::cerr << e.what() << std::endl;
                        Result result{Result::FAILURE, std::string(e.what()) + "\n"};
                        memcpy(data_send, result.msg.c_str(), result.msg.length());
                        offset = result.msg.length();

                        // 将报错信息写入output.txt
                        std::fstream outfile;
                        outfile.open("output.txt", std::ios::out | std::ios::app);
                        outfile << "failure\n";
                        outfile.close();
                    }
                }
            } else {
                // Parser error: send failure to client
                yy_delete_buffer(buf);
                finish_analyze = true;
                pthread_mutex_unlock(buffer_mutex);
                std::string err = "Parser Error: syntax error\n";
                memcpy(data_send, err.c_str(), err.length());
                offset = err.length();
                // Write to output.txt
                std::fstream outfile;
                outfile.open("output.txt", std::ios::out | std::ios::app);
                outfile << "parser error\n";
                outfile.close();
            }
            if(finish_analyze == false) {
                yy_delete_buffer(buf);
                pthread_mutex_unlock(buffer_mutex);
            }
            // 将格式化结果发送给客户端（空结果时发送确认符，使客户端可区分成功）
            send_response:
            if (offset == 0) {
                data_send[0] = '\n';
                offset = 1;
            }
            if (send_result_to_client(fd, data_send, offset) < 0) {
                send_error = true;
                delete context;
                break;
            }
            // 如果是单条语句，需要按照一个完整的事务来执行，所以执行完当前语句后，自动提交事务
            if(context->txn_->get_txn_mode() == false)
            {
                txn_manager->commit(context->txn_, context->log_mgr_);
            }
            delete context;

            // Move to next statement
            remaining = semi + 1;
        }

        // Clear accumulation buffer after processing all statements
        accum_buf.clear();
        if (send_error) break;
    }

    // Clear
    std::cout << "Terminating current client_connection..." << std::endl;
    close(fd);           // close a file descriptor.
    active_connections.fetch_sub(1);
    pthread_exit(NULL);  // terminate calling thread!
}

void start_server(int port) {
    // init mutex
    buffer_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    sockfd_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(buffer_mutex, nullptr);
    pthread_mutex_init(sockfd_mutex, nullptr);

    int sockfd_server;
    int fd_temp;
    struct sockaddr_in s_addr_in {};

    // 初始化连接
    sockfd_server = socket(AF_INET, SOCK_STREAM, 0);  // ipv4,TCP
    assert(sockfd_server != -1);
    int val = 1;
    if (setsockopt(sockfd_server, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0) {
        std::cerr << "setsockopt(SO_REUSEADDR) failed: " << strerror(errno) << std::endl;
        exit(1);
    }
#ifdef SO_REUSEPORT
    if (setsockopt(sockfd_server, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val)) < 0) {
        std::cerr << "setsockopt(SO_REUSEPORT) failed: " << strerror(errno) << std::endl;
        exit(1);
    }
#endif

    // before bind(), set the attr of structure sockaddr.
    memset(&s_addr_in, 0, sizeof(s_addr_in));
    s_addr_in.sin_family = AF_INET;
    s_addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr_in.sin_port = htons(port);
    fd_temp = bind(sockfd_server, (struct sockaddr *)(&s_addr_in), sizeof(s_addr_in));
    if (fd_temp == -1) {
        std::cout << "Bind error!" << std::endl;
        exit(1);
    }

    fd_temp = listen(sockfd_server, MAX_CONN_LIMIT);
    if (fd_temp == -1) {
        std::cout << "Listen error!" << std::endl;
        exit(1);
    }

    while (!should_exit) {
        std::cout << "Waiting for new connection..." << std::endl;
        pthread_t thread_id;
        struct sockaddr_in s_addr_client {};
        int client_length = sizeof(s_addr_client);

        if (setjmp(jmpbuf)) {
            std::cout << "Break from Server Listen Loop\n";
            break;
        }

        // Block here. Until server accepts a new connection.
        pthread_mutex_lock(sockfd_mutex);
        int sockfd = accept(sockfd_server, (struct sockaddr *)(&s_addr_client), (socklen_t *)(&client_length));
        if (sockfd == -1) {
            std::cout << "Accept error!" << std::endl;
            pthread_mutex_unlock(sockfd_mutex);
            continue;  // ignore current socket ,continue while loop.
        }

        // Reject gracefully when at connection limit — send error to client
        // before closing, so clients see a clear failure instead of a hard drop.
        if (active_connections.load() >= MAX_CONN_LIMIT) {
            std::cout << "Connection limit reached (" << MAX_CONN_LIMIT
                      << "), rejecting new connection." << std::endl;
            const char *msg = "Error: Too many connections, server limit reached.\n";
            send_result_to_client(sockfd, msg, strlen(msg));
            close(sockfd);
            pthread_mutex_unlock(sockfd_mutex);  // release before continuing loop
            continue;
        }

        // Heap-allocate to prevent stack-use-after-scope: the worker thread
        // reads *sockfd_ptr then deletes it.
        int *sockfd_ptr = new int(sockfd);
        if (pthread_create(&thread_id, nullptr, &client_handler, (void *)sockfd_ptr) != 0) {
            std::cout << "Create thread fail!" << std::endl;
            delete sockfd_ptr;
            close(sockfd);
            pthread_mutex_unlock(sockfd_mutex);
            break;  // break while loop
        }

    }

    // Clear
    std::cout << " Try to close all client-connection.\n";
    int ret = shutdown(sockfd_server, SHUT_WR);  // shut down the all or part of a full-duplex connection.
    if(ret == -1) { printf("%s\n", strerror(errno)); }
//    assert(ret != -1);
    sm_manager->close_db();
    std::cout << " DB has been closed.\n";
    std::cout << "Server shuts down." << std::endl;
}

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
                     "Welcome to RMDB!\n"
                     "Type 'help;' for help.\n"
                     "\n";
        // Database name is passed by args
        std::string db_name = argv[1];
        if (!sm_manager->is_dir(db_name)) {
            // Database not found, create a new one
            sm_manager->create_db(db_name);
        }
        // Open database
        sm_manager->open_db(db_name);

        // recovery database
        recovery->analyze();
        recovery->redo();
        recovery->undo();

        // 开启服务端，开始接受客户端连接
        start_server(port);
    } catch (RMDBError &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    return 0;
}
