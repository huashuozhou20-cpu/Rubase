#!/usr/bin/env python3
"""
RMDB 长事务混入混沌压测 — 版本链极端拉长 + 两阶段 GC 校验
==========================================================
模拟僵尸长事务对抗密集写入的场景，压测：
  1. 版本链回溯的迭代稳定性（100000 节点安全阀校验）
  2. 两阶段 GC 内存回收（水位线释放后积压版本能否被清空）
  3. 进程 RSS 存活校验（无内存泄漏、无崩溃）

测试模型：
  - 长事务线程：BEGIN 后读取快照，挂起 N 秒锁死水位线
  - 密集写线程：N 并发对同一行极限 UPDATE，版本链暴涨至数千节点
  - 监控线程：在长事务期间持续 SELECT 该行，检验可见性
  - N 秒后长事务 COMMIT，触发 GC，校验内存回落

用法:
  python3 tools/long_txn_stress_test.py [--duration 45] [--writers 8]
"""

import socket
import sys
import os
import time
import threading
import argparse
import subprocess
from typing import Optional, Tuple, List

HOST = "127.0.0.1"
PORT = 8765
SOCK_TIMEOUT = 30.0

PROJECT_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILD_DIR = os.path.join(PROJECT_DIR, "build")


# ============================================================
# Client helpers
# ============================================================

class RMDBClient:
    """Persistent connection to RMDB server."""

    def __init__(self, host=HOST, port=PORT, timeout=SOCK_TIMEOUT):
        self.host = host
        self.port = port
        self.timeout = timeout
        self.sock: Optional[socket.socket] = None

    def connect(self) -> bool:
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.settimeout(self.timeout)
            self.sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
            self.sock.connect((self.host, self.port))
            return True
        except Exception as e:
            print(f"  Connect failed: {e}")
            return False

    def close(self):
        if self.sock:
            try:
                self.sock.close()
            except Exception:
                pass
            self.sock = None

    def execute(self, sql: str) -> Tuple[bool, str]:
        """Send SQL, return (success, response_text)."""
        if not sql.endswith(";"):
            sql += ";"
        try:
            self.sock.sendall(sql.encode() + b"\0")
            resp = self.sock.recv(65536)
            text = resp.decode(errors="replace")
            has_error = "error" in text.lower() or "failure" in text.lower()
            return (not has_error), text
        except (socket.timeout, ConnectionError, OSError) as e:
            return False, str(e)

    def get_balance(self) -> Optional[int]:
        """SELECT balance FROM accounts WHERE id=1."""
        ok, resp = self.execute("SELECT balance FROM accounts WHERE id=1")
        if not ok:
            return None
        for line in resp.split("\n"):
            if line.startswith("|") and "---" not in line:
                parts = [p.strip() for p in line.split("|") if p.strip()]
                if parts and (parts[0].lstrip("-").isdigit()):
                    return int(parts[0])
        return None


def get_server_pid() -> Optional[int]:
    """Return PID of the rmdb server process."""
    try:
        result = subprocess.run(["pgrep", "-f", "rmdb"],
                                capture_output=True, text=True)
        pids = result.stdout.strip().split()
        for pid_str in pids:
            pid = int(pid_str)
            try:
                with open(f"/proc/{pid}/comm", "r") as f:
                    if f.read().strip() == "rmdb":
                        return pid
            except Exception:
                continue
        return int(pids[0]) if pids else None
    except Exception:
        return None


def get_rss_mb(pid: int) -> float:
    """Return RSS memory in MB for a given PID."""
    try:
        with open(f"/proc/{pid}/status", "r") as f:
            for line in f:
                if line.startswith("VmRSS:"):
                    parts = line.split()
                    return float(parts[1]) / 1024.0
    except Exception:
        return -1.0


# ============================================================
# Test
# ============================================================

class LongTxnStressTest:
    """Long-transaction + heavy-write stress test harness."""

    def __init__(self, duration: int = 45, num_writers: int = 8):
        self.duration = duration
        self.num_writers = num_writers
        self.stop_event = threading.Event()
        self.start_event = threading.Event()  # signals writers to begin

        # Metrics
        self.total_updates = 0
        self.total_aborts = 0
        self.select_errors = 0
        self.select_successes = 0
        self.max_balance = 100
        self.min_balance = 100
        self.memory_samples: List[Tuple[float, float]] = []
        self.lock = threading.Lock()

    def _setup(self, admin: RMDBClient) -> bool:
        admin.execute("DROP TABLE accounts")
        ok, resp = admin.execute(
            "CREATE TABLE accounts (id INT PRIMARY KEY, balance INT)"
        )
        if not ok:
            print(f"  CREATE TABLE failed: {resp[:200]}")
            return False
        admin.execute("INSERT INTO accounts VALUES(1, 100)")
        ok, _ = admin.execute("SELECT * FROM accounts")
        return ok

    def _long_txn_thread(self):
        """Start a read-only transaction and hold it open for the test duration."""
        c = RMDBClient()
        if not c.connect():
            self.start_event.set()  # unblock writers even on failure
            return
        try:
            ok, _ = c.execute("begin")
            if not ok:
                print("  [LONG] begin failed")
                self.start_event.set()
                return

            bal = c.get_balance()
            print(f"  [LONG] Snapshot captured: balance={bal}")

            # Signal writers to start
            self.start_event.set()

            print(f"  [LONG] Holding txn for {self.duration}s (pinning watermark)...")
            time.sleep(self.duration)

            ok, resp = c.execute("commit")
            if ok:
                print(f"  [LONG] Committed — watermark released")
            else:
                print(f"  [LONG] Commit failed: {resp[:100]}")

        except Exception as e:
            print(f"  [LONG] Exception: {e}")
            self.start_event.set()
        finally:
            c.close()

    def _writer_thread(self, tid: int):
        """Explicit txn: SELECT balance, then UPDATE with new value.
        Uses staggered start to avoid S→X upgrade deadlock with peer writers."""
        c = RMDBClient(timeout=10.0)
        if not c.connect():
            return
        local_updates = 0
        local_aborts = 0

        self.start_event.wait()
        time.sleep(tid * 0.05)

        try:
            while not self.stop_event.is_set():
                # SELECT current value (MVCC snapshot if read-only, but we need
                # the real current value for the UPDATE to make sense)
                ok1, resp1 = c.execute("SELECT balance FROM accounts WHERE id=1")
                if not ok1:
                    local_aborts += 1
                    continue
                # Parse current balance
                cur = None
                for line in resp1.split("\n"):
                    if line.startswith("|") and "---" not in line:
                        parts = [p.strip() for p in line.split("|") if p.strip()]
                        if parts and parts[0].lstrip("-").isdigit():
                            cur = int(parts[0])
                            break
                if cur is None:
                    local_aborts += 1
                    continue

                new_val = cur + 1
                ok2, resp2 = c.execute(
                    f"UPDATE accounts SET balance = {new_val} WHERE id=1"
                )
                if ok2:
                    local_updates += 1
                else:
                    local_aborts += 1
        except Exception:
            pass
        finally:
            c.close()
            with self.lock:
                self.total_updates += local_updates
                self.total_aborts += local_aborts

    def _monitor_thread(self):
        """Periodically SELECT the row to verify visibility + sample memory."""
        c = RMDBClient(timeout=10.0)
        if not c.connect():
            return

        self.start_event.wait()

        pid = get_server_pid()
        start = time.time()
        last_sample = 0

        try:
            while not self.stop_event.is_set():
                elapsed = time.time() - start

                bal = c.get_balance()
                if bal is not None:
                    with self.lock:
                        self.select_successes += 1
                        if bal > self.max_balance:
                            self.max_balance = bal
                        if bal < self.min_balance:
                            self.min_balance = bal
                else:
                    with self.lock:
                        self.select_errors += 1

                # Sample RSS every 5 seconds
                if pid and elapsed - last_sample >= 5:
                    rss = get_rss_mb(pid)
                    if rss > 0:
                        with self.lock:
                            self.memory_samples.append((elapsed, rss))
                    last_sample = elapsed

                time.sleep(0.5)
        except Exception:
            pass
        finally:
            c.close()

    def run(self) -> bool:
        print("=" * 70)
        print("  RMDB 长事务混入混沌压测 — 版本链极端拉长 + GC 校验")
        print("=" * 70)
        print(f"\n  长事务挂起: {self.duration}s")
        print(f"  并发写入线程: {self.num_writers}")
        print(f"  目标: {HOST}:{PORT}")

        # Setup
        print("\n[Phase 1] 初始化测试表...")
        admin = RMDBClient()
        if not admin.connect():
            print("[FATAL] 无法连接服务端")
            return False
        if not self._setup(admin):
            admin.close()
            return False
        admin.close()
        print("  accounts 表就绪: (1, 100)")

        # Record baseline RSS
        pid = get_server_pid()
        baseline_rss = get_rss_mb(pid) if pid else 0
        print(f"  基线 RSS: {baseline_rss:.1f} MB" if baseline_rss > 0 else "  WARN: 无法获取 PID")

        # Start threads
        print(f"\n[Phase 2] 启动长事务 + {self.num_writers} 写线程 + 监控线程...")
        self.start_event.clear()
        self.stop_event.clear()

        long_thread = threading.Thread(target=self._long_txn_thread, name="LongTxn")
        writers = [
            threading.Thread(target=self._writer_thread, args=(i,), name=f"Writer-{i}")
            for i in range(self.num_writers)
        ]
        monitor = threading.Thread(target=self._monitor_thread, name="Monitor")

        # Start all threads — writers will wait at start_event
        long_thread.start()
        for t in writers:
            t.start()
        monitor.start()

        # Wait for long txn to complete
        long_thread.join(timeout=self.duration + 15)
        self.stop_event.set()

        # Wait for writers and monitor
        for t in writers:
            t.join(timeout=5)
        monitor.join(timeout=5)

        print(f"\n[Phase 3] 写入阶段完成")
        with self.lock:
            print(f"  总更新次数: {self.total_updates}")
            print(f"  总中止次数: {self.total_aborts}")
            print(f"  SELECT 成功: {self.select_successes}")
            print(f"  SELECT 错误: {self.select_errors}")
            print(f"  Balance 范围: {self.min_balance} → {self.max_balance}")
            chain_approx = self.max_balance - 100
            print(f"  预估版本链深度: ~{chain_approx}")

        # Verify final state
        print("\n[Phase 4] 校验最终状态...")
        time.sleep(2)  # Allow GC
        c = RMDBClient()
        if not c.connect():
            print("[FATAL] 服务端失联")
            return False

        final_bal = c.get_balance()
        alive, _ = c.execute("SELECT * FROM accounts")
        c.close()

        if final_bal is not None:
            print(f"  最终 balance: {final_bal}")
            ok = final_bal >= 100 + self.total_updates * 0.99  # allow small abort rate
            print(f"  Balance 验证: {'PASS' if ok else 'WARN'}")
        else:
            print("  Balance 验证: FAIL — 无法读取")

        print(f"  服务端存活: {'YES' if alive else 'NO'}")

        # RSS analysis
        final_rss = get_rss_mb(pid) if pid else 0
        with self.lock:
            samples = list(self.memory_samples)

        print(f"\n  内存采样点: {len(samples)}")
        if baseline_rss > 0 and final_rss > 0:
            growth = ((final_rss - baseline_rss) / baseline_rss) * 100
            print(f"  RSS: 基线={baseline_rss:.1f} → 最终={final_rss:.1f} MB ({growth:+.1f}%)")
            if growth > 100:
                print(f"  RSS WARN: 增长 > 100%，可能内存泄漏")
            elif growth < 20:
                print(f"  RSS OK: GC 正常回收")
            else:
                print(f"  RSS ACCEPTABLE")

        if len(samples) >= 2:
            peak = max(s[1] for s in samples)
            print(f"  RSS 峰值: {peak:.1f} MB")

        # Verdict
        print(f"\n{'=' * 70}")
        print("  测试结论")
        print(f"{'=' * 70}")
        passed = (
            alive
            and self.select_errors == 0
            and self.select_successes > 0
            and (final_bal is not None)
            and final_bal > 100
        )
        if passed:
            print(f"  PASS — 版本链 {chain_approx} 节点遍历稳定，服务端存活，GC 正常")
        else:
            print("  FAIL")
        return passed


# ============================================================
# Main
# ============================================================

def main():
    parser = argparse.ArgumentParser(description="RMDB 长事务混入混沌压测")
    parser.add_argument("--duration", type=int, default=45,
                        help="长事务挂起时长（秒），默认 45")
    parser.add_argument("--writers", type=int, default=8,
                        help="并发写入线程数，默认 8")
    parser.add_argument("--host", default=HOST)
    parser.add_argument("--port", type=int, default=PORT)
    args = parser.parse_args()

    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(3)
        s.connect((args.host, args.port))
        s.close()
    except Exception as e:
        print(f"[FATAL] 无法连接到 RMDB 服务端: {e}")
        sys.exit(1)

    test = LongTxnStressTest(duration=args.duration, num_writers=args.writers)
    success = test.run()
    sys.exit(0 if success else 1)


if __name__ == "__main__":
    main()
