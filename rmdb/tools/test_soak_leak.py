#!/usr/bin/env python3
"""
RMDB Long-Running Soak & Resource Leak Audit Test
===================================================
Subjects the engine to continuous mixed CRUD from 4 concurrent threads,
then validates that no memory or disk space has leaked.

Usage:
  python3 tools/test_soak_leak.py [--port PORT] [--duration SECONDS]
"""

import sys
import os
import time
import threading
import argparse
import test_harness as H


# ---------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--port', type=int, default=H.default_port_for("soak_leak"))
    ap.add_argument('--duration', type=int, default=180,
                    help='Soak duration in seconds (default: 180 = 3 min)')
    args = ap.parse_args()

    PORT = args.port
    DB = "/tmp/rmdb_soak"
    DURATION = args.duration
    SAMPLE_INTERVAL = 5

    print("=" * 60)
    print(f"  RMDB Soak & Resource Leak Audit ({DURATION}s)  (port {PORT})")
    print("=" * 60)

    H.kill_all_servers()

    # ---- Setup ----------------------------------------------------------
    print("\n[Setup] Starting server + populating baseline...")
    p = H.start_fresh_server(DB, PORT)
    if not H.wait_for_server(port=PORT):
        print("FAIL: Server won't start")
        return False

    pid = p.pid
    print(f"  Server PID: {pid}")

    admin = H.connect(port=PORT)
    H.sql(admin, "CREATE TABLE soak (id INT PRIMARY KEY, val INT, padding TEXT)")
    for i in range(1, 11):
        H.sql(admin, f"INSERT INTO soak VALUES({i}, {i*10}, 'baseline_row_{i}')")
    resp = H.sql(admin, "SELECT * FROM soak")
    bl = H.count_rows(resp)
    assert bl == 10, f"Baseline mismatch: expected 10, got {bl}"
    print(f"  Baseline: 10 rows committed ✓")

    data_files_before = {}
    for fname in os.listdir(DB):
        fpath = os.path.join(DB, fname)
        if os.path.isfile(fpath):
            data_files_before[fname] = os.path.getsize(fpath)
    print(f"  Pre-test data files: {data_files_before}")

    # ---- Worker threads -------------------------------------------------
    stop_event = threading.Event()
    error_events = []
    counter_lock = threading.Lock()
    counters = {"inserts": 0, "deletes": 0, "updates": 0, "errors": 0}

    def worker_fn(worker_id):
        try:
            sock = H.connect(port=PORT, timeout=10)
        except Exception as e:
            error_events.append(f"W{worker_id} connect: {e}")
            return

        row_id = 1000 + worker_id * 10000
        local_i = 0

        while not stop_event.is_set():
            local_i += 1
            rid = row_id + local_i
            try:
                H.sql(sock,
                      f"INSERT INTO soak VALUES({rid}, {rid}, "
                      f"'soak_padding_{worker_id}_{local_i}')",
                      timeout=5)
                with counter_lock: counters["inserts"] += 1

                H.sql(sock, f"UPDATE soak SET val=val+1 WHERE id={rid}", timeout=5)
                with counter_lock: counters["updates"] += 1

                H.sql(sock, f"DELETE FROM soak WHERE id={rid}", timeout=5)
                with counter_lock: counters["deletes"] += 1
            except Exception:
                with counter_lock: counters["errors"] += 1
                try: sock.close()
                except Exception: pass
                try:
                    sock = H.connect(port=PORT, timeout=10)
                except Exception:
                    time.sleep(0.5)

        try: sock.close()
        except Exception: pass

    # ---- Launch workers -------------------------------------------------
    print(f"\n[Soak] Launching 4 worker threads for {DURATION}s...")
    workers = []
    for wid in range(4):
        t = threading.Thread(target=worker_fn, args=(wid,))
        t.start()
        workers.append(t)

    # ---- Monitor loop ---------------------------------------------------
    rss_samples = []
    start_time = time.time()

    try:
        while time.time() - start_time < DURATION:
            time.sleep(SAMPLE_INTERVAL)
            elapsed = int(time.time() - start_time)
            rss = H.get_vmrss(pid)
            rss_samples.append((elapsed, rss))
            rss_mb = rss / 1024.0 if rss > 0 else -1
            print(f"  [{elapsed:4d}s] VmRSS={rss_mb:.1f} MB  "
                  f"ops(i={counters['inserts']} d={counters['deletes']} "
                  f"u={counters['updates']} e={counters['errors']})")
    except KeyboardInterrupt:
        print("\n  Interrupted by user")
    finally:
        stop_event.set()

    for t in workers:
        t.join(timeout=10)

    elapsed_total = int(time.time() - start_time)
    total_ops = sum(counters[k] for k in ['inserts', 'deletes', 'updates'])
    print(f"\n  Soak complete. Total: {elapsed_total}s  ops={total_ops}  errors={counters['errors']}")

    # ---- Cleanup --------------------------------------------------------
    print("\n[Cleanup] Removing all test data, keeping baseline rows...")
    try:
        H.sql(admin, "DELETE FROM soak WHERE id > 10", timeout=30)
        resp = H.sql(admin, "SELECT * FROM soak")
        remaining = H.count_rows(resp)
        print(f"  Remaining rows: {remaining} (expected 10)")
        if remaining != 10:
            print(f"  ⚠ Row count mismatch: got {remaining}, expected 10")
    except Exception as e:
        print(f"  ⚠ Cleanup error: {e}")

    admin.close()
    p.terminate()
    p.wait(timeout=10)
    time.sleep(1)

    # ---- Phase 1: Memory leak analysis ----------------------------------
    print("\n[Analysis] Memory leak detection...")
    mem_ok = True
    if len(rss_samples) < 3:
        print("  ⚠ Not enough samples for trend analysis")
    else:
        n = len(rss_samples)
        sum_x = sum(s[0] for s in rss_samples)
        sum_y = sum(s[1] for s in rss_samples)
        sum_xy = sum(s[0] * s[1] for s in rss_samples)
        sum_x2 = sum(s[0] * s[0] for s in rss_samples)
        denom = n * sum_x2 - sum_x * sum_x
        slope = (n * sum_xy - sum_x * sum_y) / denom if denom != 0 else 0

        first_rss = rss_samples[0][1]
        last_rss = rss_samples[-1][1]
        rss_growth = last_rss - first_rss
        GROWTH_THRESHOLD_KB = 20 * 1024  # 20 MB

        print(f"  First VmRSS: {first_rss} kB  |  Last VmRSS: {last_rss} kB")
        print(f"  Delta: {rss_growth:+d} kB  |  Slope: {slope:.2f} kB/s")

        if rss_growth > GROWTH_THRESHOLD_KB and slope > 0.1:
            print(f"  ✗ MEMORY LEAK SUSPECTED: VmRSS grew {rss_growth} kB "
                  f"(>{GROWTH_THRESHOLD_KB} kB) with positive slope")
            mem_ok = False
        else:
            print("  ✓ Memory stable (growth within acceptable bounds)")

    # ---- Phase 2: Disk space analysis -----------------------------------
    print("\n[Analysis] Disk space recovery...")
    disk_ok = True
    for fname in sorted(os.listdir(DB)):
        fpath = os.path.join(DB, fname)
        if not os.path.isfile(fpath) or fname == 'output.txt':
            continue
        size_after = H.get_file_size(fpath)
        size_before = data_files_before.get(fname, 0)
        growth = size_after - size_before
        mb = size_after / (1024 * 1024)

        label = ""
        if fname == 'db.log': label = " [WAL]"
        elif fname.endswith('.idx'): label = " [index]"
        elif fname == 'db.meta': label = " [metadata]"

        print(f"  {fname}: {size_after:>10,} B ({mb:.2f} MB) "
              f"| growth: {growth:+,} B{label}")

        if fname not in ('db.log', 'db.meta'):
            if size_after > 200 * 1024 * 1024:
                print(f"    ⚠ DISK BLOAT: {fname} abnormally large after cleanup")
                disk_ok = False
            elif growth > 50 * 1024 * 1024:
                print(f"    ⚠ DISK GROWTH: {fname} grew {growth:,} B")
                disk_ok = False

    # ---- Verdict ---------------------------------------------------------
    print(f"\n{'=' * 60}")
    print(f"  Memory leak:    {'PASS' if mem_ok else 'FAIL'}")
    print(f"  Disk recovery:  {'PASS' if disk_ok else 'WARN'}")
    print(f"  Total ops:      {total_ops}")
    print(f"  Errors:         {counters['errors']}")
    print(f"  Verdict:        {'PASS' if (mem_ok and disk_ok) else 'CHECK'}")
    print(f"{'=' * 60}")

    return mem_ok and disk_ok


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
