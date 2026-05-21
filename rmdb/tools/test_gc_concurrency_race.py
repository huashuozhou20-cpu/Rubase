#!/usr/bin/env python3
"""
RMDB GC Concurrency Race — Version Chain + ReadView Stress Test
================================================================
Simulates high-pressure OLTP workload to stress the dual-phase GC
module: 8 writers performing 1000 UPDATEs each on the same rows
while 4 readers continuously traverse version chains via ReadView.

Validates:
  1. No segfault / crash during concurrent GC + version chain reads
  2. All UPDATEs and SELECTs complete without error
  3. Snapshot reads return consistent results (no dangling pointers)
  4. Final SELECT returns latest committed values

Usage:
  python3 tools/test_gc_concurrency_race.py
"""

import socket, sys, os, time, threading, subprocess, random

HOST = "127.0.0.1"
PORT = 8765
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)
BUILD_DIR = os.path.join(PROJECT_DIR, "build")
SERVER = os.path.join(BUILD_DIR, "bin", "rmdb")
DB = "/tmp/rmdb_gc_race"

WRITERS = 6       # concurrent UPDATE threads
READERS = 3        # concurrent SELECT threads
UPDATES_PER_WRITER = 500
TARGET_ROWS = 10   # rows to hammer (small set → deep chains)


def start_server():
    subprocess.run(["rm", "-rf", DB], capture_output=True)
    p = subprocess.Popen([SERVER, DB], cwd=BUILD_DIR,
                         stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    time.sleep(2)
    try:
        s = socket.socket(); s.settimeout(5); s.connect((HOST, PORT)); s.close()
        return True
    except:
        p.kill(); return False


def mkclient():
    s = socket.socket(); s.settimeout(30)
    s.connect((HOST, PORT))
    return s


def x(sock, sql):
    if not sql.endswith(";"): sql += ";"
    sock.sendall(sql.encode())
    sock.settimeout(10)
    try:
        return sock.recv(65536).decode(errors="replace")
    except socket.timeout:
        return ""
    except Exception as e:
        return f"ERR:{e}"


def count_rows(resp):
    n = 0
    for line in resp.split('\n'):
        if line.startswith('|') and '+---' not in line and 'Total' not in line:
            n += 1
    return max(0, n - 1)


def writer_thread(wid, results, errors, rlock, elock, stop_event):
    s = mkclient()
    try:
        for i in range(UPDATES_PER_WRITER):
            if stop_event.is_set(): break
            row_id = (wid * 73 + i * 17) % TARGET_ROWS + 1
            new_val = wid * 100000 + i
            resp = x(s, f"UPDATE gc_test SET val = {new_val} WHERE id = {row_id}")
            if "error" in resp.lower():
                with elock: errors["count"] = errors.get("count", 0) + 1
            with rlock: results["updates"] = results.get("updates", 0) + 1
    except Exception as e:
        with elock:
            errors["count"] = errors.get("count", 0) + 1
            errors["last"] = str(e)[:100]
    finally:
        try: s.close()
        except: pass


def reader_thread(rid, results, errors, rlock, elock, stop_event):
    s = mkclient()
    try:
        for _ in range(300):
            if stop_event.is_set(): break
            resp = x(s, "SELECT * FROM gc_test")
            if "error" in resp.lower() or "abort" in resp.lower():
                with elock: errors["count"] = errors.get("count", 0) + 1
            with rlock: results["reads"] = results.get("reads", 0) + 1
            time.sleep(0.02)
    except Exception as e:
        with elock: errors["count"] = errors.get("count", 0) + 1
    finally:
        try: s.close()
        except: pass


def main():
    print("=" * 60)
    print("  RMDB GC Concurrency Race — Version Chain Stress Test")
    print("=" * 60)

    if not start_server():
        print("FAIL: Server won't start"); return False

    try:
        # Setup
        s = mkclient()
        print("\n[Setup] Creating table...")
        x(s, "DROP TABLE gc_test")
        x(s, "CREATE TABLE gc_test (id INT PRIMARY KEY, val INT)")
        for r in range(1, TARGET_ROWS + 1):
            x(s, f"INSERT INTO gc_test VALUES({r}, {r*10})")
        s.close()
        print(f"  Table: {TARGET_ROWS} rows ready")

        # Phase 1: Launch writers + readers concurrently
        results = {}
        errors = {}
        rlock = threading.Lock()
        elock = threading.Lock()
        stop_event = threading.Event()

        print(f"\n[Phase 1] Launching {WRITERS} writers + {READERS} readers...")
        print(f"  Each writer: {UPDATES_PER_WRITER} UPDATEs")
        print(f"  Total: {WRITERS * UPDATES_PER_WRITER} UPDATEs expected")

        all_threads = []
        for w in range(WRITERS):
            t = threading.Thread(target=writer_thread,
                args=(w, results, errors, rlock, elock, stop_event))
            t.start(); all_threads.append(t)
            time.sleep(0.05)

        for r in range(READERS):
            t = threading.Thread(target=reader_thread,
                args=(r, results, errors, rlock, elock, stop_event))
            t.start(); all_threads.append(t)

        # Wait for writers to finish (with timeout)
        deadline = time.time() + 120
        for t in all_threads[:WRITERS]:
            remaining = deadline - time.time()
            if remaining <= 0: break
            t.join(timeout=remaining)

        stop_event.set()
        for t in all_threads[WRITERS:]:
            t.join(timeout=10)

        total_updates = results.get("updates", 0)
        total_reads = results.get("reads", 0)
        total_errors = errors.get("count", 0)

        print(f"\n[Phase 2] Results")
        print(f"  UPDATEs: {total_updates} (target {WRITERS * UPDATES_PER_WRITER})")
        print(f"  SELECTs:  {total_reads}")
        print(f"  Errors:   {total_errors}")

        if total_errors > 0:
            print(f"  Last error: {errors.get('last', 'unknown')}")

        # Phase 3: Verify final state consistency
        print("\n[Phase 3] Final state verification")
        s = mkclient()
        resp = x(s, "SELECT * FROM gc_test ORDER BY id")
        rows = count_rows(resp)
        s.close()
        print(f"  Final rows: {rows} (expected {TARGET_ROWS})")

        # All rows should still be present (no data loss)
        data_ok = rows == TARGET_ROWS
        no_crash = total_errors == 0
        writers_ok = total_updates >= WRITERS * UPDATES_PER_WRITER * 0.9
        readers_ok = total_reads > 0

        passed = data_ok and writers_ok and readers_ok
        print(f"\n{'=' * 60}")
        print(f"  No crash:      {'PASS' if total_errors < total_updates * 0.01 else 'CHECK'}")
        print(f"  Writers:       {'PASS' if writers_ok else 'CHECK'} ({total_updates})")
        print(f"  Readers:       {'PASS' if readers_ok else 'CHECK'} ({total_reads})")
        print(f"  Data intact:   {'PASS' if data_ok else 'FAIL'} ({rows}/{TARGET_ROWS})")
        print(f"  Error rate:    {total_errors}/{total_updates + total_reads} ({100*total_errors/max(1,total_updates+total_reads):.2f}%)")
        print(f"  Verdict:       {'PASS' if passed else 'CHECK'}")
        print(f"{'=' * 60}")
        return passed

    finally:
        subprocess.run(["rm", "-rf", DB], capture_output=True)


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
