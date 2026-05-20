#!/usr/bin/env python3
"""
RMDB 事务隔离性线性化与数据一致性强校验
=========================================
模拟极端并发转账与条件约束对抗，检验 MVCC 快照读与写锁在极限状态下
是否会产生写偏斜（Write Skew）或破坏隔离级别。

测试模型（经典 Checking-Account 写偏斜场景）：
  - 账户表 accounts(id, balance)，初始 (1, 100), (2, 100)
  - 业务约束：balance[1] + balance[2] >= 0 在任何时刻必须成立
  - 事务 A：若 sum > 150，从账户 1 扣除 150（变 -50）
  - 事务 B：若 sum > 150，从账户 2 扣除 150（变 -50）
  - 若两事务同时基于相同快照判定 sum=200>150 并分别扣款成功，
    则 sum 变为 -100 → 写偏斜漏洞！

用法:
  python3 tools/isolation_consistency_test.py [--rounds N] [--verbose]
"""

import socket
import sys
import os
import time
import threading
import argparse
from typing import Optional, Tuple, List
from dataclasses import dataclass

SOCK_TIMEOUT = 15.0

PROJECT_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILD_DIR = os.path.join(PROJECT_DIR, "build")

# ============================================================
# Client helpers
# ============================================================

def execute(sock: socket.socket, sql: str) -> Tuple[bool, str]:
    """Send SQL, return (success, response_text)."""
    if not sql.endswith(";"):
        sql += ";"
    try:
        sock.sendall(sql.encode() + b"\0")
        resp = sock.recv(65536)
        text = resp.decode(errors="replace")
        has_error = "error" in text.lower() or "failure" in text.lower()
        return (not has_error), text
    except (socket.timeout, ConnectionError, OSError) as e:
        return False, str(e)


def drain_socket(sock: socket.socket) -> None:
    """Read and discard any pending data."""
    try:
        sock.settimeout(0.1)
        while True:
            data = sock.recv(65536)
            if not data:
                break
    except Exception:
        pass
    finally:
        sock.settimeout(SOCK_TIMEOUT)


def get_balance(sock: socket.socket, account_id: int) -> Optional[int]:
    """SELECT balance FROM accounts WHERE id=<id> and parse result."""
    ok, resp = execute(sock, f"SELECT balance FROM accounts WHERE id={account_id}")
    if not ok:
        return None
    for line in resp.split("\n"):
        if line.startswith("|") and "---" not in line:
            parts = [p.strip() for p in line.split("|") if p.strip()]
            if parts and parts[0].lstrip("-").isdigit():
                return int(parts[0])
    return None


# ============================================================
# Test state
# ============================================================

@dataclass
class RoundResult:
    round_num: int
    outcome: str    # "write_skew", "both_aborted", "one_succeeded", "both_ok", "error"
    bal1: int
    bal2: int
    detail: str = ""


class IsolationTest:
    """Write-skew detection test harness with persistent connections."""

    def __init__(self, rounds: int = 10000, verbose: bool = False,
                 host: str = "127.0.0.1", port: int = 8765):
        self.rounds = rounds
        self.verbose = verbose
        self.host = host
        self.port = port
        self.results: List[RoundResult] = []
        self.write_skews = 0
        self.both_aborted = 0
        self.one_succeeded = 0
        self.both_ok = 0
        self.errors = 0
        self.lock = threading.Lock()

    def _new_connection(self) -> Optional[socket.socket]:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(SOCK_TIMEOUT)
        try:
            s.connect((self.host, self.port))
            return s
        except Exception:
            return None

    def _setup_table(self, admin_sock: socket.socket) -> bool:
        """Create accounts table with initial rows."""
        execute(admin_sock, "DROP TABLE accounts")
        ok, resp = execute(
            admin_sock, "CREATE TABLE accounts (id INT PRIMARY KEY, balance INT)"
        )
        if not ok:
            print(f"  CREATE TABLE failed: {resp[:200]}")
            return False
        execute(admin_sock, "INSERT INTO accounts VALUES(1, 100)")
        execute(admin_sock, "INSERT INTO accounts VALUES(2, 100)")
        ok, _ = execute(admin_sock, "SELECT * FROM accounts")
        return ok

    def _reset_accounts(self, admin_sock: socket.socket) -> None:
        execute(admin_sock, "UPDATE accounts SET balance = 100 WHERE id = 1")
        execute(admin_sock, "UPDATE accounts SET balance = 100 WHERE id = 2")

    def _check_balances(self, admin_sock: socket.socket) -> Tuple[Optional[int], Optional[int]]:
        b1 = get_balance(admin_sock, 1)
        b2 = get_balance(admin_sock, 2)
        return b1, b2

    def _txn_worker(self, account_to_deduct: int, barrier: threading.Barrier,
                    ready_event: threading.Event, result_holder: List[bool],
                    sock: socket.socket):
        """Execute one side of the write-skew race using a persistent connection."""
        committed = False
        try:
            # Start explicit transaction
            ok, _ = execute(sock, "begin")
            if not ok:
                result_holder.append(False)
                return

            # Signal readiness and wait for both threads
            ready_event.set()
            barrier.wait(timeout=10)

            # Read both balances inside the transaction
            b1 = get_balance(sock, 1)
            b2 = get_balance(sock, 2)
            if b1 is None or b2 is None:
                execute(sock, "abort")
                result_holder.append(False)
                return

            if b1 + b2 > 150:
                sql = f"UPDATE accounts SET balance = balance - 150 WHERE id = {account_to_deduct}"
                ok, resp = execute(sock, sql)
                if ok:
                    ok, resp = execute(sock, "commit")
                    committed = ok
                    if not ok:
                        execute(sock, "abort")
                else:
                    execute(sock, "abort")
            else:
                execute(sock, "abort")
        except Exception:
            pass

        result_holder.append(committed)

    def _run_single_round(self, round_num: int, admin_sock: socket.socket,
                          sock_a: socket.socket, sock_b: socket.socket) -> RoundResult:
        barrier = threading.Barrier(2, timeout=10)
        ready_a = threading.Event()
        ready_b = threading.Event()
        results_a: List[bool] = []
        results_b: List[bool] = []

        t_a = threading.Thread(
            target=self._txn_worker,
            args=(1, barrier, ready_a, results_a, sock_a),
            name=f"TxnA-{round_num}"
        )
        t_b = threading.Thread(
            target=self._txn_worker,
            args=(2, barrier, ready_b, results_b, sock_b),
            name=f"TxnB-{round_num}"
        )

        t_a.start()
        t_b.start()

        # Wait for both threads to be ready (begin executed) before proceeding
        ready_a.wait(timeout=5)
        ready_b.wait(timeout=5)

        t_a.join(timeout=15)
        t_b.join(timeout=15)

        # Hang detection: if threads are still alive, they're likely deadlocked
        if t_a.is_alive() or t_b.is_alive():
            # Drain connections and return error
            drain_socket(sock_a)
            drain_socket(sock_b)
            return RoundResult(round_num, "error", 0, 0, "Thread hang detected")

        a_ok = results_a[0] if results_a else False
        b_ok = results_b[0] if results_b else False

        # Read final balances
        bal1, bal2 = self._check_balances(admin_sock)
        if bal1 is None or bal2 is None:
            return RoundResult(round_num, "error", 0, 0, "Cannot read balances")

        total = bal1 + bal2

        if a_ok and b_ok:
            if total < 0:
                return RoundResult(round_num, "write_skew", bal1, bal2,
                    f"BOTH committed, sum={total} < 0 — WRITE SKEW DETECTED")
            else:
                return RoundResult(round_num, "both_ok", bal1, bal2,
                    f"Both committed, sum={total} >= 0")
        elif a_ok or b_ok:
            return RoundResult(round_num, "one_succeeded", bal1, bal2,
                f"One committed (sum={total})")
        else:
            if total == 200:
                return RoundResult(round_num, "both_aborted", bal1, bal2,
                    "Both aborted (lock conflict)")
            else:
                return RoundResult(round_num, "error", bal1, bal2,
                    f"Both aborted but balances changed: sum={total}")

    def run(self) -> bool:
        print("=" * 70)
        print("  RMDB 事务隔离性线性化校验 — Write Skew 检测")
        print("=" * 70)
        print(f"\n  测试轮次: {self.rounds}")
        print(f"  目标: {self.host}:{self.port}")

        # Open persistent connections
        print("\n[Setup] 建立持久连接...")
        admin_sock = self._new_connection()
        sock_a = self._new_connection()
        sock_b = self._new_connection()
        if not admin_sock or not sock_a or not sock_b:
            print("[FATAL] 无法连接到 RMDB 服务端")
            return False
        print("  连接就绪: admin + 2 workers")

        print("[Setup] 初始化 accounts 表...")
        if not self._setup_table(admin_sock):
            print("[FATAL] 表初始化失败")
            return False
        print("  accounts 表就绪: (1, 100), (2, 100)")

        print(f"\n[Run] 启动 {self.rounds} 轮并发对抗测试...\n")
        start_time = time.time()
        last_report = start_time

        for rnd in range(1, self.rounds + 1):
            # Reset accounts for this round
            self._reset_accounts(admin_sock)

            result = self._run_single_round(rnd, admin_sock, sock_a, sock_b)

            if result.outcome == "write_skew":
                self.write_skews += 1
            elif result.outcome == "both_aborted":
                self.both_aborted += 1
            elif result.outcome == "one_succeeded":
                self.one_succeeded += 1
            elif result.outcome == "both_ok":
                self.both_ok += 1
            else:
                self.errors += 1

            # Periodic progress
            now = time.time()
            if now - last_report >= 5 or rnd == self.rounds:
                elapsed = now - start_time
                rate = rnd / elapsed if elapsed > 0 else 0
                print(
                    f"  [{rnd:5d}/{self.rounds}] "
                    f"write_skew={self.write_skews:4d}  "
                    f"one_ok={self.one_succeeded:6d}  "
                    f"both_abort={self.both_aborted:5d}  "
                    f"both_ok={self.both_ok:4d}  "
                    f"errors={self.errors:2d}  "
                    f"({rate:.0f} rds/s)"
                )
                last_report = now

            if self.verbose and result.outcome in ("write_skew", "both_ok"):
                print(f"    Round {rnd}: {result.detail}")

            # Stop early if write skew detected (for quick CI feedback)
            if self.write_skews > 0:
                print(f"\n  [!] 第 {rnd} 轮检测到写偏斜，提前终止测试")
                break

        elapsed = time.time() - start_time
        completed = self.write_skews + self.both_aborted + self.one_succeeded + self.both_ok + self.errors

        # Cleanup connections
        for s in (admin_sock, sock_a, sock_b):
            try:
                s.close()
            except Exception:
                pass

        # Report
        print(f"\n{'=' * 70}")
        print("  测试报告")
        print(f"{'=' * 70}")
        print(f"  总轮次:        {completed:6d}")
        print(f"  写偏斜 (FAIL):  {self.write_skews:6d}  ← 两事务均提交且 sum < 0")
        print(f"  单提交 (OK):    {self.one_succeeded:6d}  ← 仅一个事务提交")
        print(f"  双中止 (OK):    {self.both_aborted:6d}  ← 锁冲突导致双方回滚")
        print(f"  双提交安全:     {self.both_ok:6d}  ← 两事务提交但条件重检通过")
        print(f"  错误:           {self.errors:6d}")
        print(f"  耗时:           {elapsed:.1f}s")
        print()

        if self.write_skews == 0:
            print("  结论: PASS — 未检测到写偏斜，隔离级别有效防止了 Checking-Account 异常")
            return True
        else:
            skew_rate = self.write_skews / completed * 100
            print(f"  结论: FAIL — 检测到 {self.write_skews} 次写偏斜 ({skew_rate:.2f}%)")
            print(f"  隔离级别不足以防止 Write Skew（MVCC 快照隔离的已知局限）")
            return False


# ============================================================
# Main
# ============================================================

def main():
    parser = argparse.ArgumentParser(
        description="RMDB 事务隔离性线性化校验 — Write Skew 检测"
    )
    parser.add_argument("--rounds", type=int, default=10000,
                        help="测试轮次 (default: 10000)")
    parser.add_argument("--verbose", action="store_true",
                        help="打印每个异常轮次的详情")
    parser.add_argument("--host", default="127.0.0.1",
                        help="RMDB host (default: 127.0.0.1)")
    parser.add_argument("--port", type=int, default=8765,
                        help="RMDB port (default: 8765)")
    args = parser.parse_args()

    # Quick connectivity check
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(3)
        s.connect((args.host, args.port))
        s.close()
    except Exception as e:
        print(f"[FATAL] 无法连接到 RMDB 服务端 {args.host}:{args.port}: {e}")
        print("请确保服务端已启动: cd build && ./bin/rmdb mydb")
        sys.exit(1)

    test = IsolationTest(rounds=args.rounds, verbose=args.verbose,
                         host=args.host, port=args.port)
    success = test.run()
    sys.exit(0 if success else 1)


if __name__ == "__main__":
    main()
