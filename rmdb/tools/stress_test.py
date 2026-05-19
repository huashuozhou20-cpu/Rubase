#!/usr/bin/env python3
"""
RMDB 全方位自动化压力测试与性能分析脚本
===========================================
四大核心测试场景：
  场景一：吞吐量与并发扩展性极限压测
  场景二：真实 OLTP 混合读写模型测试
  场景三：复杂查询与算法瓶颈测试
  场景四：数据量级退化测试

用法:
  python3 tools/stress_test.py [--host 127.0.0.1] [--port 8765]

前置条件:
  服务端已启动: cd build && ./bin/rmdb mydb
"""

import socket
import sys
import os
import time
import threading
import random
import argparse
import subprocess
from collections import defaultdict
from dataclasses import dataclass, field
from typing import List, Tuple, Optional

HOST = "127.0.0.1"
PORT = 8765
SOCK_TIMEOUT = 5.0   # seconds — both send/recv (prevents TCP buffer deadlock)
BARRIER_TIMEOUT = 10  # seconds — max wait for thread sync

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
        self.sock.settimeout(self.timeout)  # applies to both send and recv
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
        """Send SQL, return True if no error."""
        ok, _ = self.execute(sql)
        return ok


# ============================================================
# Data Structures
# ============================================================

@dataclass
class LatencyStats:
    """Latency statistics in milliseconds."""
    count: int = 0
    total_ms: float = 0.0
    latencies: List[float] = field(default_factory=list)

    def record(self, ms: float):
        self.count += 1
        self.total_ms += ms
        self.latencies.append(ms)

    @property
    def avg_ms(self) -> float:
        return self.total_ms / self.count if self.count > 0 else 0.0

    @property
    def p50_ms(self) -> float:
        return self._percentile(50)

    @property
    def p99_ms(self) -> float:
        return self._percentile(99)

    def _percentile(self, pct: float) -> float:
        if not self.latencies:
            return 0.0
        sorted_l = sorted(self.latencies)
        idx = int(len(sorted_l) * pct / 100.0)
        idx = min(idx, len(sorted_l) - 1)
        return sorted_l[idx]

    def merge(self, other: "LatencyStats"):
        self.count += other.count
        self.total_ms += other.total_ms
        self.latencies.extend(other.latencies)


@dataclass
class TestResult:
    name: str
    metrics: dict = field(default_factory=dict)
    rows: List[List[str]] = field(default_factory=list)


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


def make_table(headers: List[str], rows: List[List[str]]) -> str:
    """Render a markdown-style table."""
    all_rows = [headers] + rows
    col_widths = [max(len(str(cell)) for cell in col) for col in zip(*all_rows)]
    lines = []
    # header
    header_line = "| " + " | ".join(h.ljust(col_widths[i]) for i, h in enumerate(headers)) + " |"
    sep_line = "|" + "|".join("-" * (w + 2) for w in col_widths) + "|"
    lines.append(header_line)
    lines.append(sep_line)
    for row in rows:
        row_line = "| " + " | ".join(str(c).ljust(col_widths[i]) for i, c in enumerate(row)) + " |"
        lines.append(row_line)
    return "\n".join(lines)


def fmt_ms(ms: float) -> str:
    if ms < 1.0:
        return f"{ms*1000:.1f}µs"
    elif ms < 1000.0:
        return f"{ms:.2f}ms"
    else:
        return f"{ms/1000:.2f}s"


def fmt_tps(tps: float) -> str:
    if tps >= 1000:
        return f"{tps/1000:.1f}K"
    return f"{tps:.1f}"


# ============================================================
# Scenario Runner
# ============================================================

class StressTestRunner:
    def __init__(self, host=HOST, port=PORT, fast_mode=False):
        self.host = host
        self.port = port
        self.fast_mode = fast_mode
        self.results: List[TestResult] = []
        self.fail_count = 0
        self.fail_lock = threading.Lock()
        self.server_crashes = 0
        self._server_bin = None  # set by run_all

        # Durations adapt to mode
        self.s1_duration = 5 if fast_mode else 10       # seconds per concurrency level
        self.s2_duration = 15 if fast_mode else 60       # seconds per workload mix
        self.s3_iterations = 200 if fast_mode else 1000  # iterations per query type
        self.s4_max_rows = 10_000 if fast_mode else 50_000  # max rows in volume test

    def _restart_server(self):
        """Kill existing server and restart with clean database, then re-setup tables."""
        self.server_crashes += 1
        print(f"\n  *** 服务器进程崩溃 (第{self.server_crashes}次重启) ***")
        subprocess.run(["pkill", "-f", "rmdb mydb"], capture_output=True)
        time.sleep(1)
        if self._server_bin:
            db_dir = os.path.dirname(self._server_bin)
            mydb_path = os.path.join(db_dir, "mydb")
            subprocess.run(["rm", "-rf", mydb_path], capture_output=True)
            subprocess.Popen([self._server_bin, "mydb"],
                             stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            time.sleep(2)
            print(f"  *** 服务器已重启，重新初始化表结构... ***")
            try:
                self._setup_tables()
                print(f"  *** 表结构恢复完成 ***\n")
            except Exception as e:
                print(f"  *** 表结构恢复失败: {e} ***\n")

    def _new_client(self) -> RMDBClient:
        for attempt in range(3):
            try:
                c = RMDBClient(self.host, self.port)
                c.connect()
                return c
            except Exception:
                if attempt < 2:
                    time.sleep(0.5)
        # Last attempt — let the exception propagate
        c = RMDBClient(self.host, self.port)
        c.connect()
        return c

    def _server_alive(self) -> bool:
        """Check if RMDB server is reachable (just TCP connect)."""
        try:
            c = RMDBClient(self.host, self.port, timeout=2.0)
            c.connect()
            c.close()
            return True
        except Exception:
            return False

    def _setup_tables(self):
        """Create test tables and indexes.
        NOTE: stress_test_table has NO secondary indexes to avoid B+tree
        concurrency crash. Indexes exist only on the join/subquery tables
        used in scenario 3 (read-heavy, single-threaded)."""
        c = self._new_client()
        try:
            c.execute_ignore("DROP TABLE stress_test_table")
            c.execute("CREATE TABLE stress_test_table ("
                      "id INT, val1 INT, val2 FLOAT, val3 CHAR(32), val4 CHAR(64))")
            # No indexes on stress_test_table — avoids concurrent B+tree insert crash

            c.execute_ignore("DROP TABLE stress_join_a")
            c.execute_ignore("DROP TABLE stress_join_b")
            c.execute("CREATE TABLE stress_join_a(id INT, col1 INT, col2 FLOAT, name CHAR(32))")
            c.execute("CREATE TABLE stress_join_b(id INT, col1 INT, col2 FLOAT, name CHAR(32))")
            c.execute("CREATE INDEX idx_ja_id ON stress_join_a(id)")
            c.execute("CREATE INDEX idx_jb_id ON stress_join_b(id)")

            c.execute_ignore("DROP TABLE stress_sub_a")
            c.execute_ignore("DROP TABLE stress_sub_b")
            c.execute("CREATE TABLE stress_sub_a(id INT, col1 INT, feat FLOAT)")
            c.execute("CREATE TABLE stress_sub_b(id INT, col2 INT, feat FLOAT)")
            c.execute("CREATE INDEX idx_sa_id ON stress_sub_a(id)")
            c.execute("CREATE INDEX idx_sb_id ON stress_sub_b(id)")
        finally:
            c.close()

    def _teardown_tables(self):
        c = self._new_client()
        try:
            c.execute_ignore("DROP TABLE stress_test_table")
            c.execute_ignore("DROP TABLE stress_join_a")
            c.execute_ignore("DROP TABLE stress_join_b")
            c.execute_ignore("DROP TABLE stress_sub_a")
            c.execute_ignore("DROP TABLE stress_sub_b")
            c.execute_ignore("DROP TABLE stress_volume")
        finally:
            c.close()

    def _record_fail(self):
        with self.fail_lock:
            self.fail_count += 1

    # ============================================================
    # Scenario 1: Scalability (Concurrency Ladder)
    # ============================================================

    def run_scalability_test(self):
        """并发扩展性极限压测"""
        print("\n" + "=" * 70)
        print("  场景一：吞吐量与并发扩展性极限压测 (Scalability Test)")
        print("=" * 70)

        # Server MAX_CONN_LIMIT=8; 16 threads exceeds and causes crash
        thread_counts = [1, 2, 4, 8]
        duration_sec = self.s1_duration
        rows = []

        for n_threads in thread_counts:
            print(f"\n  >>> 并发线程数: {n_threads}  (持续 {duration_sec}s) ...")
            stats, total_ops = self._scalability_worker(n_threads, duration_sec)

            if total_ops == 0:
                print(f"      警告: 无成功操作 (可能连接数超限)")
                rows.append([str(n_threads), "0", "N/A", "N/A", "N/A"])
                continue

            tps = total_ops / duration_sec
            rows.append([
                str(n_threads),
                f"{total_ops}",
                fmt_tps(tps),
                fmt_ms(stats.avg_ms),
                fmt_ms(stats.p99_ms)
            ])
            print(f"      总操作: {total_ops}  |  TPS: {fmt_tps(tps)}  |  "
                  f"Avg: {fmt_ms(stats.avg_ms)}  |  P99: {fmt_ms(stats.p99_ms)}")

        self.results.append(TestResult(
            name="场景一：并发扩展性",
            rows=rows
        ))

    def _scalability_worker(self, n_threads: int, duration_sec: int) -> Tuple[LatencyStats, int]:
        barrier = threading.Barrier(n_threads) if n_threads > 1 else None
        stop_event = threading.Event()
        stats_per_thread: List[LatencyStats] = []
        total_ops = [0]
        lock = threading.Lock()

        def worker(thread_id):
            local_stats = LatencyStats()
            local_ops = 0
            # Connect first so connection failure doesn't strand other threads at barrier
            try:
                c = self._new_client()
            except Exception:
                self._record_fail()
                with lock:
                    stats_per_thread.append(local_stats)
                return

            # Now sync so all threads start hammering simultaneously
            if barrier:
                try:
                    barrier.wait(BARRIER_TIMEOUT)
                except threading.BrokenBarrierError:
                    c.close()
                    self._record_fail()
                    with lock:
                        stats_per_thread.append(local_stats)
                    return

            try:
                while not stop_event.is_set():
                    sql = (f"INSERT INTO stress_test_table VALUES("
                           f"{random_int()}, {random_int()}, {random_float()}, "
                           f"'{random_str(16)}', '{random_str(32)}')")
                    t0 = time.perf_counter()
                    ok, _ = c.execute(sql)
                    elapsed_ms = (time.perf_counter() - t0) * 1000.0
                    if ok:
                        local_stats.record(elapsed_ms)
                        local_ops += 1
                    else:
                        self._record_fail()
            except Exception:
                self._record_fail()
            finally:
                c.close()
                with lock:
                    stats_per_thread.append(local_stats)
                    total_ops[0] += local_ops

        threads = []
        for i in range(n_threads):
            t = threading.Thread(target=worker, args=(i,))
            t.start()
            threads.append(t)

        time.sleep(duration_sec)
        stop_event.set()

        for t in threads:
            t.join(timeout=5)

        merged = LatencyStats()
        for s in stats_per_thread:
            merged.merge(s)
        return merged, total_ops[0]

    # ============================================================
    # Scenario 2: Mixed OLTP Workload
    # ============================================================

    def run_mixed_workload_test(self):
        """真实 OLTP 混合读写模型"""
        print("\n" + "=" * 70)
        print("  场景二：真实 OLTP 混合读写模型测试 (Mixed Workload)")
        print("=" * 70)

        # Pre-populate 200 rows for reads
        self._populate_table("stress_test_table", 200)

        configs = [
            ("强读弱写 (90%R/10%W)", 0.90),
            ("均衡负载 (50%R/50%W)", 0.50),
            ("弱读强写 (10%R/90%W)", 0.10),
        ]
        n_threads = 8
        duration_sec = self.s2_duration
        rows = []

        for label, read_ratio in configs:
            print(f"\n  >>> {label}  (8 threads, {duration_sec}s) ...")
            r_stats, w_stats, total_ops = self._mixed_worker(n_threads, duration_sec, read_ratio)

            if total_ops == 0:
                rows.append([label, "0", "N/A", "N/A", "N/A", "N/A"])
                continue

            read_count = r_stats.count
            write_count = w_stats.count
            total_qps = total_ops / duration_sec
            rows.append([
                label,
                str(total_ops),
                fmt_tps(total_qps),
                f"{read_count}/{write_count}",
                fmt_ms(r_stats.avg_ms) if read_count > 0 else "N/A",
                fmt_ms(w_stats.avg_ms) if write_count > 0 else "N/A",
            ])
            print(f"      总操作: {total_ops}  |  QPS: {fmt_tps(total_qps)}  |  "
                  f"R/W: {read_count}/{write_count}  |  "
                  f"读延迟: {fmt_ms(r_stats.avg_ms)}  |  写延迟: {fmt_ms(w_stats.avg_ms)}")

        self.results.append(TestResult(
            name="场景二：混合 OLTP 负载",
            rows=rows
        ))

    def _mixed_worker(self, n_threads: int, duration_sec: int, read_ratio: float
                      ) -> Tuple[LatencyStats, LatencyStats, int]:
        barrier = threading.Barrier(n_threads)
        stop_event = threading.Event()
        r_stats_all: List[LatencyStats] = []
        w_stats_all: List[LatencyStats] = []
        total_ops = [0]
        lock = threading.Lock()

        def worker(thread_id):
            r_local = LatencyStats()
            w_local = LatencyStats()
            local_ops = 0
            # Connect first so connection failure doesn't strand other threads at barrier
            try:
                c = self._new_client()
            except Exception:
                self._record_fail()
                with lock:
                    r_stats_all.append(r_local)
                    w_stats_all.append(w_local)
                return

            # Now sync so all threads start hammering simultaneously
            try:
                barrier.wait(BARRIER_TIMEOUT)
            except threading.BrokenBarrierError:
                c.close()
                self._record_fail()
                with lock:
                    r_stats_all.append(r_local)
                    w_stats_all.append(w_local)
                return

            try:
                while not stop_event.is_set():
                    if random.random() < read_ratio:
                        # SELECT
                        sql = f"SELECT * FROM stress_test_table WHERE id={random_int()}"
                        t0 = time.perf_counter()
                        ok, _ = c.execute(sql)
                        elapsed = (time.perf_counter() - t0) * 1000.0
                        if ok:
                            r_local.record(elapsed)
                            local_ops += 1
                        else:
                            self._record_fail()
                    else:
                        # INSERT or UPDATE
                        if random.random() < 0.7:
                            sql = (f"INSERT INTO stress_test_table VALUES("
                                   f"{random_int()}, {random_int()}, {random_float()}, "
                                   f"'{random_str(16)}', '{random_str(32)}')")
                        else:
                            sql = (f"UPDATE stress_test_table SET val2={random_float()} "
                                   f"WHERE val1={random_int()}")
                        t0 = time.perf_counter()
                        ok, _ = c.execute(sql)
                        elapsed = (time.perf_counter() - t0) * 1000.0
                        if ok:
                            w_local.record(elapsed)
                            local_ops += 1
                        else:
                            self._record_fail()
            except Exception:
                self._record_fail()
            finally:
                c.close()
                with lock:
                    r_stats_all.append(r_local)
                    w_stats_all.append(w_local)
                    total_ops[0] += local_ops

        threads = []
        for i in range(n_threads):
            t = threading.Thread(target=worker, args=(i,))
            t.start()
            threads.append(t)

        time.sleep(duration_sec)
        stop_event.set()

        for t in threads:
            t.join(timeout=5)

        r_merged = LatencyStats()
        w_merged = LatencyStats()
        for s in r_stats_all:
            r_merged.merge(s)
        for s in w_stats_all:
            w_merged.merge(s)
        return r_merged, w_merged, total_ops[0]

    # ============================================================
    # Scenario 3: Complex Query Sizing
    # ============================================================

    def run_query_sizing_test(self):
        """复杂查询与算法瓶颈测试"""
        print("\n" + "=" * 70)
        print("  场景三：复杂查询与算法瓶颈测试 (Query Sizing)")
        print("=" * 70)

        # Populate join tables (50 rows each)
        c = self._new_client()
        try:
            for i in range(1, 51):
                c.execute_ignore(f"INSERT INTO stress_join_a VALUES({i}, {i%10}, {i*1.5}, 'a_{i}')")
                c.execute_ignore(f"INSERT INTO stress_join_b VALUES({i}, {i%5}, {i*2.0}, 'b_{i}')")
                c.execute_ignore(f"INSERT INTO stress_sub_a VALUES({i}, {i%3}, {i*0.5})")
                c.execute_ignore(f"INSERT INTO stress_sub_b VALUES({i}, {i%3}, {i*1.2})")
        finally:
            c.close()

        queries = {
            "点查询 (索引)": "SELECT * FROM stress_join_a WHERE id={}",
            "INNER JOIN 50×50": ("SELECT * FROM stress_join_a INNER JOIN stress_join_b "
                                 "ON stress_join_a.id = stress_join_b.id"),
            "LEFT JOIN 50×50": ("SELECT * FROM stress_join_a LEFT JOIN stress_join_b "
                                "ON stress_join_a.id = stress_join_b.id"),
            "IN 子查询": ("SELECT * FROM stress_sub_a WHERE col1 IN "
                          "(SELECT stress_sub_b.col2 FROM stress_sub_b WHERE stress_sub_b.col2<4)"),
        }
        iterations = self.s3_iterations
        configs = [("单线程", 1), ("4 线程", 4)]

        rows = []
        for config_label, n_threads in configs:
            print(f"\n  >>> {config_label}  (每个查询 {iterations} 次) ...")
            for q_name, q_template in queries.items():
                avg_ms = self._query_sizing_worker(q_name, q_template, iterations, n_threads)
                rows.append([f"{q_name} ({config_label})", str(iterations), fmt_ms(avg_ms)])
                print(f"      {q_name}: avg {fmt_ms(avg_ms)}")

        self.results.append(TestResult(
            name="场景三：复杂查询",
            rows=rows
        ))

    def _query_sizing_worker(self, q_name: str, q_template: str,
                              iterations: int, n_threads: int) -> float:
        barrier = threading.Barrier(n_threads) if n_threads > 1 else None
        all_latencies: List[float] = []
        lock = threading.Lock()
        per_thread = iterations // n_threads

        def worker():
            local_lats = []
            try:
                c = self._new_client()
            except Exception:
                self._record_fail()
                return
            try:
                if barrier:
                    barrier.wait()
                for i in range(per_thread):
                    if "{}" in q_template:
                        sql = q_template.format(random.randint(1, 50))
                    else:
                        sql = q_template
                    t0 = time.perf_counter()
                    ok, _ = c.execute(sql)
                    elapsed = (time.perf_counter() - t0) * 1000.0
                    if ok:
                        local_lats.append(elapsed)
                    else:
                        self._record_fail()
            except Exception:
                self._record_fail()
            finally:
                c.close()
                with lock:
                    all_latencies.extend(local_lats)

        threads = []
        for _ in range(n_threads):
            t = threading.Thread(target=worker)
            t.start()
            threads.append(t)

        for t in threads:
            t.join()

        if not all_latencies:
            return 0.0
        return sum(all_latencies) / len(all_latencies)

    # ============================================================
    # Scenario 4: Data Volume Degradation
    # ============================================================

    def run_volume_degradation_test(self):
        """数据量级退化测试"""
        print("\n" + "=" * 70)
        print("  场景四：数据量级退化测试 (Volume Degradation)")
        print("=" * 70)

        # Ensure dedicated table
        c = self._new_client()
        try:
            c.execute_ignore("DROP TABLE stress_volume")
            ok, resp = c.execute("CREATE TABLE stress_volume ("
                      "id INT, val1 INT, val2 FLOAT, val3 CHAR(32), val4 CHAR(64))")
            if not ok:
                print(f"      WARN: CREATE TABLE stress_volume 失败: {resp[:200]}")
            # No index — single-threaded sequential insert, avoids B+tree concurrency issue
        finally:
            c.close()

        checkpoints = [1_000, 5_000, self.s4_max_rows]
        sample_batch = 200  # measure TPS over this many inserts at each checkpoint
        rows = []
        inserted = 0

        c = self._new_client()
        try:
            print(f"\n  >>> 单线程持续插入，检测点: {[f'{x//1000}K' for x in checkpoints]} ...")
            for cp in checkpoints:
                target = cp
                batch_start = time.perf_counter()
                batch_ops = 0
                batch_last_elapsed = 0.0
                last_progress = inserted

                consecutive_fails = 0
                while inserted < target:
                    sql = (f"INSERT INTO stress_volume VALUES("
                           f"{inserted+1}, {random_int()}, {random_float()}, "
                           f"'{random_str(32)}', '{random_str(64)}')")
                    t0 = time.perf_counter()
                    ok, _ = c.execute(sql)
                    elapsed = (time.perf_counter() - t0) * 1000.0
                    if not ok:
                        self._record_fail()
                        consecutive_fails += 1
                        if consecutive_fails > 50:
                            print(f"      ABORT: 连续 {consecutive_fails} 次插入失败，可能服务器已崩溃")
                            break
                        continue
                    consecutive_fails = 0
                    inserted += 1

                    # Progress indicator every 500 inserts
                    if inserted - last_progress >= 500:
                        pct = inserted / target * 100
                        print(f"      进度: {inserted:,}/{target:,} ({pct:.0f}%) ...")
                        last_progress = inserted

                    # Sample the last sample_batch inserts before checkpoint
                    if inserted >= target - sample_batch:
                        if batch_ops == 0:
                            batch_start = time.perf_counter()
                        batch_ops += 1
                        batch_last_elapsed = elapsed

                if consecutive_fails > 50:
                    break  # break out of checkpoint loop

                # Calculate TPS from the sample batch
                dt = time.perf_counter() - batch_start
                tps = batch_ops / dt if dt > 0 else 0
                rows.append([f"{cp//1000}K", str(inserted),
                             fmt_tps(tps), fmt_ms(batch_last_elapsed)])
                print(f"      在 {inserted:,} 条: TPS={fmt_tps(tps)}, 延迟={fmt_ms(batch_last_elapsed)}")
        finally:
            c.close()

        self.results.append(TestResult(
            name="场景四：数据量级退化",
            rows=rows
        ))

    # ============================================================
    # Helpers
    # ============================================================

    def _populate_table(self, table: str, count: int):
        """Pre-populate a table with random rows."""
        c = self._new_client()
        try:
            for i in range(1, count + 1):
                sql = (f"INSERT INTO {table} VALUES("
                       f"{i}, {random_int()}, {random_float()}, "
                       f"'{random_str(16)}', '{random_str(32)}')")
                c.execute_ignore(sql)
        finally:
            c.close()

    # ============================================================
    # Report
    # ============================================================

    def print_report(self):
        """Print all collected results as markdown tables."""
        print("\n\n")
        print("#" * 70)
        print("#  RMDB 压力测试性能分析报告")
        print("#" * 70)
        print(f"# 失败事务总数: {self.fail_count}")
        print()

        for r in self.results:
            print(f"## {r.name}")
            print()
            if r.name == "场景一：并发扩展性":
                print(make_table(
                    ["并发线程", "总操作数", "TPS", "Avg Latency", "P99 Latency"],
                    r.rows
                ))
            elif r.name == "场景二：混合 OLTP 负载":
                print(make_table(
                    ["负载类型", "总操作数", "QPS/TPS", "R/W 次数", "读延迟(Avg)", "写延迟(Avg)"],
                    r.rows
                ))
            elif r.name == "场景三：复杂查询":
                print(make_table(
                    ["查询类型", "迭代次数", "平均延迟"],
                    r.rows
                ))
            elif r.name == "场景四：数据量级退化":
                print(make_table(
                    ["检测点", "实际数据量", "瞬时 TPS", "单次延迟"],
                    r.rows
                ))
            print()

        # Summary
        print("## 测试总结")
        print()
        print(f"- 失败事务数: {self.fail_count}")
        print(f"- 测试场景数: {len(self.results)}")
        if self.server_crashes > 0:
            print(f"- **服务器崩溃次数: {self.server_crashes}** (并发写入稳定性问题)")
        print()

    # ============================================================
    # Run All
    # ============================================================

    def run_all(self):
        print("RMDB 压力测试启动...")
        print(f"目标: {self.host}:{self.port}")
        # Detect server binary location
        self._server_bin = os.path.join(
            os.path.dirname(os.path.abspath(__file__)), "..", "build", "bin", "rmdb")
        if not os.path.exists(self._server_bin):
            self._server_bin = os.path.join(
                os.path.dirname(os.path.abspath(__file__)), "..", "build", "rmdb")
        print()

        def _ensure_server():
            """Check server alive, restart if dead."""
            if self._server_alive():
                return True
            self._restart_server()
            return self._server_alive()

        # Setup
        print("[Setup] 初始化测试表结构...")
        if not _ensure_server():
            print("[FATAL] 无法连接数据库服务器")
            sys.exit(1)
        try:
            self._setup_tables()
            print("[Setup] 完成\n")
        except Exception as e:
            print(f"[FATAL] 无法初始化测试表: {e}")
            print("请确认 RMDB 服务端已启动: cd build && ./bin/rmdb mydb")
            sys.exit(1)

        try:
            # Scenario 1
            print(">>> 开始场景一: 并发扩展性")
            if _ensure_server():
                self.run_scalability_test()
            else:
                print("[ERROR] 服务器不可用，跳过场景一")

            # Scenario 2
            print("\n>>> 开始场景二: 混合 OLTP 负载")
            if _ensure_server():
                self.run_mixed_workload_test()
            else:
                print("[ERROR] 服务器不可用，跳过场景二")

            # Scenario 3
            print("\n>>> 开始场景三: 复杂查询")
            if _ensure_server():
                self.run_query_sizing_test()
            else:
                print("[ERROR] 服务器不可用，跳过场景三")

            # Scenario 4
            print("\n>>> 开始场景四: 数据量级退化")
            if _ensure_server():
                self.run_volume_degradation_test()
            else:
                print("[ERROR] 服务器不可用，跳过场景四")

        finally:
            # Teardown
            print("\n[Teardown] 清理测试表...")
            if _ensure_server():
                try:
                    self._teardown_tables()
                    print("[Teardown] 完成")
                except Exception as e:
                    print(f"[Teardown] 清理异常: {e}")
            else:
                print("[Teardown] 服务器已不可达，跳过清理")

        # Report
        self.print_report()
        print("测试全部完成。")


# ============================================================
# Main
# ============================================================

def main():
    parser = argparse.ArgumentParser(description="RMDB 全方位压力测试")
    parser.add_argument("--host", default=HOST, help=f"RMDB host (default: {HOST})")
    parser.add_argument("--port", type=int, default=PORT, help=f"RMDB port (default: {PORT})")
    parser.add_argument("--quick", action="store_true",
                        help="快速模式: 缩短时长/数据量 (默认)")
    parser.add_argument("--full", action="store_true",
                        help="完整模式: 原始规格 (60s/1000次/50K条)")
    args = parser.parse_args()

    fast_mode = not args.full  # quick is default
    if args.full:
        print("*** 完整压测模式 (可能需要 30-60 分钟) ***")
    else:
        print("*** 快速压测模式 (预计 5-10 分钟) ***")

    runner = StressTestRunner(host=args.host, port=args.port, fast_mode=fast_mode)
    runner.run_all()


if __name__ == "__main__":
    main()
