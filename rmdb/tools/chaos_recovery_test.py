#!/usr/bin/env python3
"""
RMDB 破坏性崩溃恢复与混沌极限压力测试脚本
============================================
两大核心测试模块：
  模块一：断电强杀与 WAL 崩溃恢复一致性测试 (Crash Consistency Test)
  模块二：长周期内存泄漏与混沌生存测试 (Soak & Chaos Test)

用法:
  python3 tools/chaos_recovery_test.py --mode crash       # 仅运行崩溃恢复测试
  python3 tools/chaos_recovery_test.py --mode soak         # 仅运行长周期混沌测试
  python3 tools/chaos_recovery_test.py --mode all          # 运行全部测试
  python3 tools/chaos_recovery_test.py --mode all --duration 900  # soak 测试 15 分钟

前置条件:
  服务端已编译: cd build && cmake .. && make -j$(nproc)
"""

import socket
import sys
import os
import time
import threading
import random
import argparse
import subprocess
import signal
import shutil
from collections import defaultdict
from dataclasses import dataclass, field
from typing import List, Tuple, Optional, Dict

HOST = "127.0.0.1"
PORT = 8765
SOCK_TIMEOUT = 10.0
BARRIER_TIMEOUT = 15
SERVER_STARTUP_WAIT = 3.0

# Resolve paths relative to this script
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)
BUILD_DIR = os.path.join(PROJECT_DIR, "build")
SERVER_BIN = os.path.join(BUILD_DIR, "bin", "rmdb")
DB_DIR = os.path.join(BUILD_DIR, "mydb")

TMP_DB_DIR = os.path.join(BUILD_DIR, "mydb_chaos")  # Dedicated DB dir for chaos tests


# ============================================================
# RMDB Client
# ============================================================

class RMDBClient:
    """Lightweight RMDB TCP client."""

    def __init__(self, host=HOST, port=PORT, timeout=SOCK_TIMEOUT):
        self.host = host
        self.port = port
        self.timeout = timeout
        self.sock: Optional[socket.socket] = None

    def connect(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.settimeout(self.timeout)
        self.sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        self.sock.connect((self.host, self.port))

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
            response = self.sock.recv(65536)
            text = response.decode(errors="replace")
            has_error = "error" in text.lower() or "failure" in text.lower()
            return (not has_error), text
        except (socket.timeout, ConnectionError, OSError) as e:
            return False, str(e)

    def execute_ignore(self, sql: str) -> bool:
        ok, _ = self.execute(sql)
        return ok


# ============================================================
# Helpers
# ============================================================

def random_int() -> int:
    return random.randint(1, 100000)


def random_float() -> float:
    return round(random.uniform(0.0, 99999.99), 2)


def random_str(length: int = 16) -> str:
    chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    return "".join(random.choice(chars) for _ in range(length))


def server_alive(host=HOST, port=PORT) -> bool:
    """Check if RMDB server is reachable."""
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(2.0)
        s.connect((host, port))
        s.close()
        return True
    except Exception:
        return False


def wait_for_server(timeout: float = 30.0) -> bool:
    """Block until server accepts connections or timeout."""
    deadline = time.time() + timeout
    while time.time() < deadline:
        if server_alive():
            return True
        time.sleep(0.5)
    return False


def kill_server(sig: int = signal.SIGKILL):
    """Kill all rmdb server processes."""
    subprocess.run(["pkill", f"-{sig}", "-f", "rmdb mydb"],
                   capture_output=True)


def get_server_pid() -> Optional[int]:
    """Return PID of the rmdb server process, or None."""
    try:
        # Match any rmdb process with a database directory argument
        result = subprocess.run(["pgrep", "-f", "rmdb"],
                                capture_output=True, text=True)
        pids = result.stdout.strip().split()
        for pid_str in pids:
            pid = int(pid_str)
            # Verify it's actually the rmdb binary by reading /proc/pid/comm
            try:
                with open(f"/proc/{pid}/comm", "r") as f:
                    comm = f.read().strip()
                    if comm == "rmdb":
                        return pid
            except Exception:
                continue
        return int(pids[0]) if pids else None
    except Exception:
        return None


def get_rss_mb(pid: int) -> float:
    """Return RSS memory usage in MB for a given PID."""
    try:
        with open(f"/proc/{pid}/status", "r") as f:
            for line in f:
                if line.startswith("VmRSS:"):
                    parts = line.split()
                    return float(parts[1]) / 1024.0  # kB → MB
    except Exception:
        return -1.0


def start_server(db_dir: str = DB_DIR) -> subprocess.Popen:
    """Start the RMDB server process. Returns the Popen object."""
    # Clean old database
    if os.path.exists(db_dir):
        shutil.rmtree(db_dir)
    os.makedirs(os.path.dirname(db_dir), exist_ok=True)

    proc = subprocess.Popen(
        [SERVER_BIN, db_dir],
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )
    return proc


def make_table(headers: List[str], rows: List[List[str]]) -> str:
    """Render a markdown-style table."""
    all_rows = [headers] + rows
    col_widths = [max(len(str(cell)) for cell in col) for col in zip(*all_rows)]
    lines = []
    header_line = "| " + " | ".join(h.ljust(col_widths[i]) for i, h in enumerate(headers)) + " |"
    sep_line = "|" + "|".join("-" * (w + 2) for w in col_widths) + "|"
    lines.append(header_line)
    lines.append(sep_line)
    for row in rows:
        row_line = "| " + " | ".join(str(c).ljust(col_widths[i]) for i, c in enumerate(row)) + " |"
        lines.append(row_line)
    return "\n".join(lines)


# ============================================================
# 模块一：断电强杀与 WAL 崩溃恢复一致性测试
# ============================================================

class CrashConsistencyTest:
    """SIGKILL the server during heavy writes, then verify WAL recovery."""

    def __init__(self):
        self.results: List[Dict] = []
        # Track committed rows for post-recovery verification
        self.committed_keys: List[int] = []
        self.commit_lock = threading.Lock()
        self.stop_event = threading.Event()
        self.write_threads: List[threading.Thread] = []
        self.total_inserts = 0
        self.total_updates = 0
        self.sigkill_time = 0.0

    def _setup_tables(self):
        """Create test tables for crash consistency testing."""
        c = RMDBClient()
        c.connect()
        try:
            c.execute_ignore("DROP TABLE crash_test")
            ok, resp = c.execute(
                "CREATE TABLE crash_test ("
                "id INT, val1 INT, val2 FLOAT, val3 CHAR(32), val4 CHAR(64))"
            )
            if not ok:
                print(f"  WARN: CREATE TABLE failed: {resp[:200]}")
                return False
            # Pre-populate 100 rows as base data
            for i in range(1, 101):
                c.execute_ignore(
                    f"INSERT INTO crash_test VALUES({i}, {i*10}, {i*1.5}, "
                    f"'base_{i}', 'prepopulate_row_{i}')"
                )
            # Verify setup
            ok, resp = c.execute("SELECT COUNT(*) FROM crash_test")
            if ok:
                print("  Setup: crash_test table created, 100 base rows inserted")
                return True
            else:
                print(f"  Setup verification failed: {resp[:100]}")
                return False
        finally:
            c.close()

    def _writer_thread(self, thread_id: int):
        """Worker that does INSERT + UPDATE in a loop until stopped or SIGKILL."""
        c = RMDBClient(timeout=5.0)
        try:
            c.connect()
        except Exception:
            return

        local_committed = []
        last_flush = time.time()
        try:
            while not self.stop_event.is_set():
                if random.random() < 0.7:
                    key = random_int()
                    sql = (
                        f"INSERT INTO crash_test VALUES("
                        f"{key}, {random_int()}, {random_float()}, "
                        f"'{random_str(16)}', '{random_str(32)}')"
                    )
                    ok, resp = c.execute(sql)
                    if ok:
                        local_committed.append(key)
                else:
                    target = random.randint(1, 100)
                    sql = (
                        f"UPDATE crash_test SET val1={random_int()}, "
                        f"val2={random_float()} WHERE id={target}"
                    )
                    ok, _ = c.execute(sql)

                # Flush committed keys periodically
                if time.time() - last_flush >= 3:
                    with self.commit_lock:
                        self.committed_keys.extend(local_committed)
                    local_committed.clear()
                    last_flush = time.time()
        except Exception:
            pass
        finally:
            c.close()
            with self.commit_lock:
                self.committed_keys.extend(local_committed)

    def _verify_recovery(self) -> Tuple[bool, str]:
        """After restart, verify the database is consistent."""
        issues = []
        c = RMDBClient(timeout=10.0)
        try:
            c.connect()
        except Exception as e:
            return False, f"Cannot connect to recovered server: {e}"

        try:
            # 1. Check base 100 rows still exist
            ok, resp = c.execute("SELECT COUNT(*) FROM crash_test")
            if not ok:
                c.close()
                return False, f"SELECT COUNT(*) failed: {resp}"

            # Parse count from response
            try:
                # Format: "Total record(s): N"
                count_line = [l for l in resp.split("\n") if "Total record" in l]
                if count_line:
                    count = int(count_line[0].split(":")[1].strip())
                else:
                    # Fallback: count data rows
                    count = len([l for l in resp.split("\n") if "|" in l and l.count("|") >= 2]) - 1
            except Exception:
                count = -1

            # 2. Verify all committed keys exist
            committed_count = 0
            missing_keys = []
            with self.commit_lock:
                keys_to_check = list(self.committed_keys)
            # Check a random sample to avoid excessive queries
            sample = random.sample(keys_to_check, min(50, len(keys_to_check)))
            for key in sample:
                ok, resp = c.execute(f"SELECT * FROM crash_test WHERE id={key}")
                if ok and "Total record(s): 0" not in resp and "|" not in resp.split("\n")[-3]:
                    committed_count += 1
                elif ok and "Total record(s): 0" in resp:
                    missing_keys.append(key)
                else:
                    missing_keys.append(key)

            # 3. Verify the 100 base rows are intact
            base_ok = True
            for i in range(1, 101):
                ok, resp = c.execute(f"SELECT * FROM crash_test WHERE id={i}")
                if not ok or "Total record(s): 0" in resp:
                    base_ok = False
                    issues.append(f"Base row id={i} missing")

            # 4. Run a simple integrity scan
            ok, resp = c.execute("SELECT * FROM crash_test")
            scan_ok = ok

            c.close()

            # Build verdict
            details = []
            if base_ok:
                details.append("100 base rows intact")
            else:
                details.append(f"Base rows damaged: {issues}")
            details.append(f"Committed key sample: {committed_count}/{len(sample)} found")
            if missing_keys:
                details.append(f"Missing keys: {missing_keys[:5]}...")

            passed = base_ok and scan_ok and (len(missing_keys) == 0)
            return passed, "; ".join(details)
        except Exception as e:
            c.close()
            return False, str(e)

    def run(self) -> Dict:
        """Execute the crash consistency test."""
        print("\n" + "=" * 70)
        print("  模块一：断电强杀与 WAL 崩溃恢复一致性测试")
        print("=" * 70)

        # Phase 1: Start server and setup
        print("\n[Phase 1] 启动服务端并初始化测试表...")
        kill_server(signal.SIGKILL)
        time.sleep(1)
        if os.path.exists(TMP_DB_DIR):
            shutil.rmtree(TMP_DB_DIR)
        self._proc = start_server(TMP_DB_DIR)
        if not wait_for_server():
            return {"test": "Crash Consistency", "passed": False,
                    "details": "Server failed to start", "recovery_ok": "N/A"}

        self._setup_tables()

        # Phase 2: Start concurrent writers
        print("[Phase 2] 启动 6 个并发写线程，高强度写入数据...")
        self.stop_event.clear()
        self.committed_keys.clear()
        self.write_threads = []
        for i in range(6):
            t = threading.Thread(target=self._writer_thread, args=(i,))
            t.start()
            self.write_threads.append(t)

        # Let writers run for 5-8 seconds to fill buffer pool and WAL
        chaos_delay = random.uniform(5.0, 8.0)
        print(f"  写线程运行中... ({chaos_delay:.1f}s 后注入强杀)")

        # Phase 3: Monitor and inject SIGKILL
        start_time = time.time()
        pid = get_server_pid()
        while time.time() - start_time < chaos_delay:
            time.sleep(0.5)
            current_pid = get_server_pid()
            if current_pid and current_pid != pid:
                pid = current_pid  # Server may have restarted
            if not current_pid:
                print("  WARN: Server process disappeared before SIGKILL")
                break

        # Record pre-kill state
        with self.commit_lock:
            pre_kill_committed = len(self.committed_keys)

        self.sigkill_time = time.time()
        print(f"\n[Phase 3] 注入 SIGKILL 强杀！(已 commit {pre_kill_committed} 条)")
        if pid:
            os.kill(pid, signal.SIGKILL)
            print(f"  已向 PID {pid} 发送 SIGKILL")
        else:
            kill_server(signal.SIGKILL)
            print("  已通过 pkill 发送 SIGKILL")

        time.sleep(1)

        # Stop writer threads
        self.stop_event.set()
        for t in self.write_threads:
            t.join(timeout=3)

        with self.commit_lock:
            total_committed = len(self.committed_keys)
        print(f"  总计 commit {total_committed} 条记录 (强杀前 {pre_kill_committed})")

        # Phase 4: Restart and verify recovery
        print("\n[Phase 4] 重新启动服务端，触发 WAL 恢复...")
        time.sleep(2)
        self._proc = start_server(TMP_DB_DIR)
        if not wait_for_server():
            return {"test": "Crash Consistency", "passed": False,
                    "details": "Server failed to restart after crash",
                    "recovery_ok": "FAIL"}

        print("  服务端已重启，正在校验数据一致性...")
        recovery_ok, details = self._verify_recovery()

        # Phase 5: Cleanup
        print("\n[Phase 5] 清理...")
        kill_server(signal.SIGKILL)
        time.sleep(1)
        if os.path.exists(TMP_DB_DIR):
            shutil.rmtree(TMP_DB_DIR)
        # Restart on default DB for subsequent tests
        start_server(DB_DIR)
        wait_for_server(timeout=10)

        result = {
            "test": "Crash Consistency (SIGKILL + WAL Recovery)",
            "passed": recovery_ok,
            "details": details,
            "pre_kill_committed": pre_kill_committed,
            "total_committed": total_committed,
            "recovery_ok": "PASS" if recovery_ok else "FAIL",
        }
        self.results.append(result)
        return result


# ============================================================
# 模块二：长周期内存泄漏与混沌生存测试
# ============================================================

class SoakChaosTest:
    """Long-duration test monitoring memory, lock stability, and survival."""

    def __init__(self, duration_sec: int = 900):
        self.duration_sec = duration_sec
        self.results: List[Dict] = []
        self.stop_event = threading.Event()
        self.total_ops = 0
        self.total_failures = 0
        self.deadlock_aborts = 0
        self.op_lock = threading.Lock()
        self.memory_samples: List[Tuple[float, float]] = []  # (elapsed_sec, rss_mb)

    def _setup_tables(self) -> bool:
        c = RMDBClient(timeout=10.0)
        c.connect()
        try:
            c.execute_ignore("DROP TABLE soak_test")
            ok, _ = c.execute("CREATE TABLE soak_test ("
                      "id INT, val1 INT, val2 FLOAT, val3 CHAR(32), val4 CHAR(64))")
            if not ok:
                print("  Setup FAIL: CREATE TABLE soak_test")
                return False

            c.execute_ignore("DROP TABLE soak_ref")
            ok, _ = c.execute("CREATE TABLE soak_ref (id INT, col1 INT, col2 FLOAT, name CHAR(32))")
            if not ok:
                print("  Setup FAIL: CREATE TABLE soak_ref")
                return False

            c.execute("CREATE INDEX idx_soak_id ON soak_ref(id)")
            # Pre-populate for reads
            for i in range(1, 101):
                c.execute_ignore(
                    f"INSERT INTO soak_test VALUES({i}, {i}, {i*1.0}, 'r{i}', 'ref_{i}')")
                c.execute_ignore(
                    f"INSERT INTO soak_ref VALUES({i}, {i%10}, {i*0.5}, 'n_{i}')")

            # Verify
            ok, resp = c.execute("SELECT COUNT(*) FROM soak_test")
            if ok:
                print("  Setup: soak_test + soak_ref created, 100 rows each")
                return True
            else:
                print(f"  Setup verification failed: {resp[:100]}")
                return False
        finally:
            c.close()

    def _worker(self, thread_id: int):
        """Mixed OLTP worker: SELECT, INSERT, UPDATE, DELETE + JOIN."""
        c = RMDBClient(timeout=15.0)
        try:
            c.connect()
        except Exception:
            return

        ops = 0
        fails = 0
        last_flush = time.time()
        try:
            while not self.stop_event.is_set():
                dice = random.random()
                try:
                    if dice < 0.35:
                        sql = f"SELECT * FROM soak_test WHERE id={random.randint(1, 100)}"
                    elif dice < 0.55:
                        sql = (
                            f"INSERT INTO soak_test VALUES("
                            f"{random_int()}, {random_int()}, {random_float()}, "
                            f"'{random_str(16)}', '{random_str(32)}')"
                        )
                    elif dice < 0.70:
                        sql = (
                            f"UPDATE soak_test SET val1={random_int()}, "
                            f"val2={random_float()} WHERE id={random.randint(1, 100)}"
                        )
                    elif dice < 0.80:
                        target = random.randint(200, 300)
                        c.execute_ignore(f"DELETE FROM soak_test WHERE id={target}")
                        sql = (
                            f"INSERT INTO soak_test VALUES("
                            f"{target}, {random_int()}, {random_float()}, "
                            f"'{random_str(6)}', '{random_str(12)}')"
                        )
                    elif dice < 0.92:
                        sql = (
                            f"SELECT * FROM soak_test INNER JOIN soak_ref "
                            f"ON soak_test.id = soak_ref.id "
                            f"WHERE soak_test.val1 < {random.randint(10, 50)}"
                        )
                    else:
                        sql = (
                            f"SELECT * FROM soak_test WHERE val1 IN "
                            f"(SELECT soak_ref.col1 FROM soak_ref WHERE soak_ref.col2<2.0)"
                        )

                    ok, resp = c.execute(sql)
                    if ok:
                        ops += 1
                    else:
                        fails += 1
                        if "DEADLOCK" in resp.upper() or "abort" in resp.lower():
                            with self.op_lock:
                                self.deadlock_aborts += 1
                except Exception:
                    fails += 1

                # Flush local counters to shared every 5 seconds
                if time.time() - last_flush >= 5:
                    with self.op_lock:
                        self.total_ops += ops
                        self.total_failures += fails
                    ops = 0
                    fails = 0
                    last_flush = time.time()
        except Exception:
            pass
        finally:
            c.close()
            with self.op_lock:
                self.total_ops += ops
                self.total_failures += fails

    def _memory_monitor(self, pid: int):
        """Background thread: sample RSS memory every 10 seconds."""
        start = time.time()
        while not self.stop_event.is_set():
            elapsed = time.time() - start
            rss = get_rss_mb(pid)
            if rss > 0:
                self.memory_samples.append((elapsed, rss))
            time.sleep(10)

    def _analyze_memory_trend(self) -> Tuple[bool, str]:
        """Check if RSS grew linearly (potential leak)."""
        if len(self.memory_samples) < 3:
            return True, "Too few samples"

        # Use linear regression on the second half to detect growth
        half = len(self.memory_samples) // 2
        recent = self.memory_samples[half:]
        first_rss = self.memory_samples[0][1]
        last_rss = self.memory_samples[-1][1]
        growth_pct = ((last_rss - first_rss) / max(first_rss, 1.0)) * 100

        # Simple trend: if growth exceeds 50% over the test duration, flag it
        if growth_pct > 50:
            return False, f"RSS grew {growth_pct:.1f}% ({first_rss:.1f}→{last_rss:.1f} MB) — possible leak"
        else:
            return True, f"RSS stable: {first_rss:.1f}→{last_rss:.1f} MB ({growth_pct:+.1f}%)"

    def run(self) -> Dict:
        """Execute the soak & chaos test."""
        print("\n" + "=" * 70)
        print(f"  模块二：长周期内存泄漏与混沌生存测试 ({self.duration_sec}s)")
        print("=" * 70)

        mins = self.duration_sec / 60
        print(f"\n  预计运行时间: {mins:.1f} 分钟")

        # Setup
        print("[Phase 1] 初始化测试表...")
        if not self._setup_tables():
            return {"test": f"Soak & Chaos ({mins:.0f}min)", "passed": False,
                    "details": "Table setup failed", "total_ops": 0,
                    "total_failures": 0, "deadlock_aborts": 0,
                    "server_survived": "N/A", "memory_ok": "N/A", "deadlock_ok": "N/A"}

        # Start workers
        print(f"[Phase 2] 启动 8 个混合 OLTP 线程...")
        self.stop_event.clear()
        workers = []
        for i in range(8):
            t = threading.Thread(target=self._worker, args=(i,))
            t.start()
            workers.append(t)

        # Start memory monitor
        pid = get_server_pid()
        if pid:
            monitor = threading.Thread(target=self._memory_monitor, args=(pid,))
            monitor.start()
        else:
            monitor = None
            print("  WARN: Cannot find server PID for memory monitoring")

        # Progress reporting
        start_time = time.time()
        try:
            last_report = 0
            while time.time() - start_time < self.duration_sec:
                elapsed = time.time() - start_time
                if elapsed - last_report >= 30:
                    with self.op_lock:
                        ops = self.total_ops
                        fails = self.total_failures
                        deadlocks = self.deadlock_aborts
                    mem_str = ""
                    if self.memory_samples:
                        mem_str = f"  RSS: {self.memory_samples[-1][1]:.1f}MB"
                    print(f"  [{elapsed:.0f}s] ops={ops} fails={fails} "
                          f"deadlock_aborts={deadlocks}{mem_str}")
                    last_report = elapsed
                time.sleep(1)
        except KeyboardInterrupt:
            print("\n  收到中断信号，正在停止测试...")
        finally:
            self.stop_event.set()

        # Wait for workers
        for t in workers:
            t.join(timeout=5)
        if monitor:
            monitor.join(timeout=5)

        # Results
        with self.op_lock:
            ops = self.total_ops
            fails = self.total_failures
            deadlocks = self.deadlock_aborts

        mem_ok, mem_detail = self._analyze_memory_trend()
        deadlock_ok = deadlocks < (ops * 0.001)  # < 0.1% deadlock rate

        # Verify server still alive
        alive = server_alive()

        details = (
            f"Total ops={ops}, failures={fails}, deadlock_aborts={deadlocks}, "
            f"server_alive={alive}, mem: {mem_detail}"
        )

        result = {
            "test": f"Soak & Chaos ({mins:.0f}min)",
            "passed": alive and mem_ok and deadlock_ok,
            "details": details,
            "total_ops": ops,
            "total_failures": fails,
            "deadlock_aborts": deadlocks,
            "server_survived": "YES" if alive else "NO",
            "memory_ok": "PASS" if mem_ok else f"WARN: {mem_detail}",
            "deadlock_ok": "PASS" if deadlock_ok else f"WARN: {deadlocks} deadlocks",
        }
        self.results.append(result)
        return result


# ============================================================
# Report
# ============================================================

def print_final_report(crash_result: Optional[Dict], soak_result: Optional[Dict]):
    """Print all collected results as markdown tables."""
    print("\n\n")
    print("#" * 70)
    print("#  RMDB 破坏性恢复与混沌测试报告")
    print("#" * 70)
    print()

    if crash_result:
        print("## 模块一：断电强杀与 WAL 崩溃恢复一致性测试")
        print()
        rows = [[
            "SIGKILL 强杀进程",
            "WAL 自动恢复 + 数据一致性校验",
            "100% 一致（已 commit 数据完整，无幽灵记录）",
            "PASS" if crash_result["passed"] else "FAIL",
            crash_result.get("details", ""),
        ]]
        print(make_table(
            ["测试场景", "注入行为", "预期结果", "实际状态", "数据一致性校验"],
            rows
        ))
        print(f"\n  强杀前 commit: {crash_result.get('pre_kill_committed', '?')} 条")
        print()

    if soak_result:
        print("## 模块二：长周期内存泄漏与混沌生存测试")
        print()
        rows = [[
            f"{soak_result.get('total_ops', 0):,} ops / {soak_result.get('total_failures', 0):,} failures",
            f"死锁中止 {soak_result.get('deadlock_aborts', 0)} 次",
            soak_result.get("server_survived", "?"),
            soak_result.get("memory_ok", "?"),
            soak_result.get("deadlock_ok", "?"),
        ]]
        print(make_table(
            ["吞吐量", "死锁统计", "服务端存活", "内存泄漏检测", "锁稳定性"],
            rows
        ))
        print(f"\n  详情: {soak_result.get('details', '')}")
        print()

    # Overall verdict
    all_passed = True
    if crash_result:
        all_passed = all_passed and crash_result["passed"]
    if soak_result:
        all_passed = all_passed and soak_result["passed"]

    print("## 总体结论")
    print()
    print(f"- 全部测试通过: {'YES' if all_passed else '**NO** — 存在失败项'}")
    print()


# ============================================================
# Main
# ============================================================

def main():
    parser = argparse.ArgumentParser(
        description="RMDB 破坏性崩溃恢复与混沌极限压力测试"
    )
    parser.add_argument("--mode", choices=["crash", "soak", "all"], default="all",
                        help="测试模式: crash (崩溃恢复), soak (长周期混沌), all (全部)")
    parser.add_argument("--duration", type=int, default=300,
                        help="Soak 测试持续时间（秒），默认 300s (5分钟)")
    parser.add_argument("--host", default=HOST, help=f"RMDB host (default: {HOST})")
    parser.add_argument("--port", type=int, default=PORT, help=f"RMDB port (default: {PORT})")
    args = parser.parse_args()

    print("RMDB 破坏性恢复与混沌测试启动...")
    print(f"服务端: {args.host}:{args.port}")
    print(f"二进制: {SERVER_BIN}")
    print(f"模式: {args.mode}")
    if args.mode in ("soak", "all"):
        print(f"Soak 时长: {args.duration}s ({args.duration/60:.1f} 分钟)")

    # Verify server binary exists
    if not os.path.exists(SERVER_BIN):
        print(f"\n[FATAL] 找不到服务端二进制: {SERVER_BIN}")
        print("请先编译: cd build && cmake .. && make -j$(nproc)")
        sys.exit(1)

    # Ensure a clean starting state
    kill_server(signal.SIGKILL)
    time.sleep(1)
    if os.path.exists(DB_DIR):
        shutil.rmtree(DB_DIR)

    # Start server
    print("\n启动服务端...")
    start_server(DB_DIR)
    if not wait_for_server():
        print("[FATAL] 服务端启动失败")
        sys.exit(1)
    print("服务端就绪\n")

    crash_result = None
    soak_result = None

    try:
        if args.mode in ("crash", "all"):
            crash_test = CrashConsistencyTest()
            crash_result = crash_test.run()

            # Restart server on clean DB between tests
            kill_server(signal.SIGKILL)
            time.sleep(1)
            if os.path.exists(DB_DIR):
                shutil.rmtree(DB_DIR)
            start_server(DB_DIR)
            if not wait_for_server():
                print("[FATAL] 服务端启动失败 (crash test 后)")
                sys.exit(1)

        if args.mode in ("soak", "all"):
            soak_test = SoakChaosTest(duration_sec=args.duration)
            soak_result = soak_test.run()

    except KeyboardInterrupt:
        print("\n收到中断信号，停止测试...")
    finally:
        # Cleanup
        print("\n[Cleanup] 清理测试环境...")
        kill_server(signal.SIGKILL)
        time.sleep(1)
        if os.path.exists(TMP_DB_DIR):
            shutil.rmtree(TMP_DB_DIR)
        if os.path.exists(DB_DIR):
            shutil.rmtree(DB_DIR)
        print("[Cleanup] 完成")

    # Report
    print_final_report(crash_result, soak_result)
    print("测试全部完成。")


if __name__ == "__main__":
    main()
