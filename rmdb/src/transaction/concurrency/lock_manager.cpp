/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "lock_manager.h"

#include <functional>
#include <unordered_set>

LockManager::GroupLockMode LockManager::lock_mode_to_group_mode(LockMode mode) {
    switch (mode) {
        case LockMode::SHARED:              return GroupLockMode::S;
        case LockMode::EXLUCSIVE:           return GroupLockMode::X;
        case LockMode::INTENTION_SHARED:    return GroupLockMode::IS;
        case LockMode::INTENTION_EXCLUSIVE: return GroupLockMode::IX;
        case LockMode::S_IX:                return GroupLockMode::SIX;
        default:                            return GroupLockMode::NON_LOCK;
    }
}

bool LockManager::is_compatible(LockMode request_mode, GroupLockMode group_mode) {
    // Compatibility matrix: can request_mode be granted when group_mode is held?
    // LockMode order:          SHARED=0, EXLUCSIVE=1, INTENTION_SHARED=2, INTENTION_EXCLUSIVE=3, S_IX=4
    // GroupLockMode order:     NON_LOCK=0, IS=1, IX=2, S=3, X=4, SIX=5
    static const bool compat[5][6] = {
        //         NL  IS  IX   S   X  SIX
        /* SHARED (S)          */ { 1,  1,  0,  1,  0,  0 },
        /* EXCLUSIVE (X)       */ { 1,  0,  0,  0,  0,  0 },
        /* INTENTION_SHARED (IS)*/{ 1,  1,  1,  1,  0,  1 },
        /* INTENTION_EXCL (IX) */ { 1,  1,  1,  0,  0,  0 },
        /* S_IX                */ { 1,  1,  0,  0,  0,  0 },
    };
    int row = static_cast<int>(request_mode);
    int col = static_cast<int>(group_mode);
    return compat[row][col];
}

void LockManager::update_group_lock_mode(LockRequestQueue& queue) {
    bool has_S = false, has_IX = false, has_IS = false, has_X = false, has_SIX = false;
    for (auto& req : queue.request_queue_) {
        if (!req.granted_) continue;
        switch (req.lock_mode_) {
            case LockMode::SHARED:              has_S = true; break;
            case LockMode::EXLUCSIVE:           has_X = true; break;
            case LockMode::INTENTION_SHARED:    has_IS = true; break;
            case LockMode::INTENTION_EXCLUSIVE: has_IX = true; break;
            case LockMode::S_IX:                has_SIX = true; break;
        }
    }
    if (has_X)               queue.group_lock_mode_ = GroupLockMode::X;
    else if (has_SIX)        queue.group_lock_mode_ = GroupLockMode::SIX;
    else if (has_S && has_IX) queue.group_lock_mode_ = GroupLockMode::SIX;
    else if (has_S)          queue.group_lock_mode_ = GroupLockMode::S;
    else if (has_IX)         queue.group_lock_mode_ = GroupLockMode::IX;
    else if (has_IS)         queue.group_lock_mode_ = GroupLockMode::IS;
    else                     queue.group_lock_mode_ = GroupLockMode::NON_LOCK;
}

bool LockManager::lock_common(Transaction* txn, const LockDataId& lock_data_id, LockMode lock_mode) {
    std::unique_lock<std::mutex> lock(latch_);

    auto& queue = lock_table_[lock_data_id];

    // Check if this transaction already holds a lock on this item
    for (auto& req : queue.request_queue_) {
        if (req.txn_id_ == txn->get_transaction_id() && req.granted_) {
            // Same lock type
            if (req.lock_mode_ == lock_mode) {
                return true;
            }
            // Lock upgrade S to X
            if (req.lock_mode_ == LockMode::SHARED && lock_mode == LockMode::EXLUCSIVE) {
                bool can_upgrade = true;
                for (auto& other : queue.request_queue_) {
                    if (other.txn_id_ != txn->get_transaction_id() && other.granted_) {
                        can_upgrade = false;
                        break;
                    }
                }
                if (can_upgrade) {
                    req.lock_mode_ = LockMode::EXLUCSIVE;
                    update_group_lock_mode(queue);
                    return true;
                }
            }
            // Already holds a lock that covers the requested lock mode
            // X covers everything; SIX covers S and IX; IX covers IS
            if (req.lock_mode_ == LockMode::EXLUCSIVE) return true;       // X covers all
            if (req.lock_mode_ == LockMode::S_IX) {
                if (lock_mode == LockMode::SHARED || lock_mode == LockMode::INTENTION_EXCLUSIVE
                    || lock_mode == LockMode::INTENTION_SHARED) return true;  // SIX covers S, IX, IS
            }
            if (req.lock_mode_ == LockMode::INTENTION_EXCLUSIVE
                && lock_mode == LockMode::INTENTION_SHARED) return true;  // IX covers IS
        }
    }

    // Wait until the lock request is compatible with the current group lock mode
    while (!is_compatible(lock_mode, queue.group_lock_mode_)) {
        // Check for deadlock
        txn_id_t victim = find_deadlock_victim(txn->get_transaction_id(), queue);
        if (victim != INVALID_TXN_ID) {
            throw TransactionAbortException(victim, AbortReason::DEADLOCK_PREVENTION);
        }
        // Add an ungranted request so deadlock detection can see us
        LockRequest wait_req(txn->get_transaction_id(), lock_mode);
        wait_req.granted_ = false;
        queue.request_queue_.push_back(wait_req);
        // Block until something changes in this lock queue
        queue.cv_.wait(lock);
        // Remove our ungranted request
        for (auto it = queue.request_queue_.begin(); it != queue.request_queue_.end(); ++it) {
            if (it->txn_id_ == txn->get_transaction_id() && !it->granted_) {
                queue.request_queue_.erase(it);
                break;
            }
        }
    }

    // Grant the lock
    LockRequest new_req(txn->get_transaction_id(), lock_mode);
    new_req.granted_ = true;
    queue.request_queue_.push_back(new_req);
    update_group_lock_mode(queue);
    txn->get_lock_set()->insert(lock_data_id);

    return true;
}

/**
 * @description: 申请行级共享锁
 */
bool LockManager::lock_shared_on_record(Transaction* txn, const Rid& rid, int tab_fd) {
    LockDataId lock_data_id(tab_fd, rid, LockDataType::RECORD);
    return lock_common(txn, lock_data_id, LockMode::SHARED);
}

/**
 * @description: 申请行级排他锁
 */
bool LockManager::lock_exclusive_on_record(Transaction* txn, const Rid& rid, int tab_fd) {
    LockDataId lock_data_id(tab_fd, rid, LockDataType::RECORD);
    return lock_common(txn, lock_data_id, LockMode::EXLUCSIVE);
}

/**
 * @description: 申请表级读锁
 */
bool LockManager::lock_shared_on_table(Transaction* txn, int tab_fd) {
    LockDataId lock_data_id(tab_fd, LockDataType::TABLE);
    return lock_common(txn, lock_data_id, LockMode::SHARED);
}

/**
 * @description: 申请表级写锁
 */
bool LockManager::lock_exclusive_on_table(Transaction* txn, int tab_fd) {
    LockDataId lock_data_id(tab_fd, LockDataType::TABLE);
    return lock_common(txn, lock_data_id, LockMode::EXLUCSIVE);
}

/**
 * @description: 申请表级意向读锁
 */
bool LockManager::lock_IS_on_table(Transaction* txn, int tab_fd) {
    LockDataId lock_data_id(tab_fd, LockDataType::TABLE);
    return lock_common(txn, lock_data_id, LockMode::INTENTION_SHARED);
}

/**
 * @description: 申请表级意向写锁
 */
bool LockManager::lock_IX_on_table(Transaction* txn, int tab_fd) {
    LockDataId lock_data_id(tab_fd, LockDataType::TABLE);
    return lock_common(txn, lock_data_id, LockMode::INTENTION_EXCLUSIVE);
}

/**
 * @description: 释放锁
 */
txn_id_t LockManager::find_deadlock_victim(txn_id_t requestor, const LockRequestQueue& queue) {
    // Collect all txn_ids that hold locks on this item (blocking the requestor)
    std::unordered_set<txn_id_t> blockers;
    for (auto& req : queue.request_queue_) {
        if (req.granted_ && req.txn_id_ != requestor) {
            blockers.insert(req.txn_id_);
        }
    }
    if (blockers.empty()) return INVALID_TXN_ID;

    // Build wait-for graph from all lock queues. Edge: waiter -> holder.
    std::unordered_map<txn_id_t, std::unordered_set<txn_id_t>> wait_for;
    for (auto& [id, q] : lock_table_) {
        std::unordered_set<txn_id_t> held_by;
        for (auto& req : q.request_queue_) {
            if (req.granted_) held_by.insert(req.txn_id_);
        }
        for (auto& req : q.request_queue_) {
            if (!req.granted_) {
                for (auto holder : held_by) {
                    if (holder != req.txn_id_) {
                        wait_for[req.txn_id_].insert(holder);
                    }
                }
            }
        }
    }
    // Add temporary edges: if requestor were waiting, it would point to each blocker
    for (auto blocker : blockers) {
        wait_for[requestor].insert(blocker);
    }

    // DFS cycle detection. Collect all transactions in the cycle.
    std::unordered_set<txn_id_t> visited, rec_stack;
    std::vector<txn_id_t> cycle_members;

    std::function<bool(txn_id_t)> dfs = [&](txn_id_t u) -> bool {
        visited.insert(u);
        rec_stack.insert(u);
        for (auto v : wait_for[u]) {
            if (rec_stack.count(v)) {
                // Cycle found: v is already in the recursion stack.
                // Collect all transactions currently in the rec_stack (on the path from v to u).
                cycle_members.push_back(v);
                for (auto txn : rec_stack) {
                    if (txn != v) cycle_members.push_back(txn);
                }
                return true;
            }
            if (!visited.count(v) && dfs(v)) return true;
        }
        rec_stack.erase(u);
        return false;
    };

    bool has_cycle = dfs(requestor);
    // Remove temporary edges
    wait_for[requestor].clear();

    if (!has_cycle) return INVALID_TXN_ID;

    // Victim selection: choose the youngest transaction (highest txn_id) in the cycle.
    // Younger transactions have done less work, so aborting them is cheaper.
    txn_id_t victim = INVALID_TXN_ID;
    for (auto txn : cycle_members) {
        if (txn > victim) victim = txn;
    }
    return victim;
}

bool LockManager::unlock(Transaction* txn, LockDataId lock_data_id) {
    std::unique_lock<std::mutex> lock(latch_);

    auto it = lock_table_.find(lock_data_id);
    if (it == lock_table_.end()) {
        return false;
    }

    auto& queue = it->second;
    auto& requests = queue.request_queue_;
    txn_id_t txn_id = txn->get_transaction_id();

    for (auto req_it = requests.begin(); req_it != requests.end(); ++req_it) {
        if (req_it->txn_id_ == txn_id && req_it->granted_) {
            requests.erase(req_it);
            update_group_lock_mode(queue);

            // Remove from transaction's lock set
            txn->get_lock_set()->erase(lock_data_id);

            // Clean up empty queues
            if (requests.empty()) {
                lock_table_.erase(it);
                // Wake up anyone who might be waiting for this lock (edge case)
                queue.cv_.notify_all();
            } else {
                // Wake up waiters on this queue since group lock mode changed
                queue.cv_.notify_all();
            }

            return true;
        }
    }

    return false;
}
