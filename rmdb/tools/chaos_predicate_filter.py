#!/usr/bin/env python3
"""
RMDB Multi-Predicate Index Scan — Gap Lock Boundary Test
=========================================================
Validates that IndexScan/SeqScan acquires NEXT_KEY/GAP locks
on ALL index entries touched during range scan, even those
filtered out by non-indexed predicates.

Scenario:
  1. Table with index on (age), columns: age INT, status VARCHAR(20)
  2. Insert: age=20, status='inactive'
  3. T1: SELECT * FROM t WHERE age > 10 AND status = 'active' FOR UPDATE
     → Index scan touches age=20 (matches age>10)
     → Predicate 'status=active' filters it out → 0 result rows
     → BUT: the index scan still traversed age=20
  4. T2: INSERT INTO t VALUES(15, 'active')
     → age=15 falls in gap before age=20
     → Should T2 be blocked?

  InnoDB behavior: gap locks are applied at the INDEX level, independent
  of non-indexed predicate filtering. Records touched by the index scan
  get NEXT_KEY locks regardless of whether they pass the full WHERE clause.

  Our implementation: check_all_conds() determines whether GAP locks
  are applied. If the first index-matching record is filtered out,
  has_match_ stays false → no GAP lock is set → potential phantom.

Usage:
  python3 tools/chaos_predicate_filter.py
"""

import socket, sys, os, time, threading, subprocess

HOST = "127.0.0.1"
PORT = 8765
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)
BUILD_DIR = os.path.join(PROJECT_DIR, "build")
SERVER = os.path.join(BUILD_DIR, "bin", "rmdb")
DB = "/tmp/rmdb_predicate"


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


def main():
    print("=" * 60)
    print("  RMDB Predicate Filter — Index Gap Lock Boundary Test")
    print("=" * 60)

    if not start_server():
        print("FAIL: Server won't start"); return False

    try:
        # Setup
        s = socket.socket(); s.settimeout(60); s.connect((HOST, PORT))
        print("\n[Setup] Creating table with index on (age)...")
        x(s, "DROP TABLE pred_test")
        x(s, "CREATE TABLE pred_test (age INT, status VARCHAR(20))")
        x(s, "CREATE INDEX pred_test (age)")  # index on age only
        x(s, "INSERT INTO pred_test VALUES(20, 'inactive')")  # won't match status filter
        x(s, "INSERT INTO pred_test VALUES(30, 'active')")    # WILL match
        print("  Rows: (20,'inactive'), (30,'active')")
        print("  Index on (age). status is NOT indexed.")

        # Phase 1: T1 does range scan with composite predicate
        print("\n[Phase 1] T1: SELECT WHERE age>10 AND status='active' FOR UPDATE")
        t1 = socket.socket(); t1.settimeout(30); t1.connect((HOST, PORT))
        x(t1, "begin")
        resp = x(t1, "SELECT * FROM pred_test WHERE age > 10 AND status = 'active' FOR UPDATE")
        rows = count_rows(resp)
        print(f"  T1 result: {rows} row(s) (expected 1: age=30,status='active')")
        print(f"  Index scan touched: age=20 (filtered by status) AND age=30 (matched)")
        print(f"  Question: is GAP before age=20 locked?")

        # Phase 2: T2 tries INSERT that would fall in gap before age=20
        print("\n[Phase 2] T2 tries INSERT age=15 into gap before age=20...")
        t2 = socket.socket(); t2.settimeout(30); t2.connect((HOST, PORT))
        t2_done = threading.Event()
        t2_result = {}

        def t2_insert():
            t0 = time.time()
            resp = x(t2, "INSERT INTO pred_test VALUES(15, 'active')")
            elapsed = (time.time() - t0) * 1000
            t2_result["ms"] = elapsed
            t2_result["resp"] = resp[:100]
            t2_done.set()

        th = threading.Thread(target=t2_insert); th.start()
        time.sleep(1.5)

        blocked = th.is_alive()
        if blocked:
            print("  T2 INSERT age=15: BLOCKED ✓")
            print("  → GAP lock protects index range regardless of predicate filtering")
            x(t1, "commit")
            print("  T1: COMMIT")
            t2_done.wait(timeout=15)
            print(f"  T2: INSERT completed in {t2_result['ms']:.0f}ms")
            predicate_protected = True
        else:
            t2_done.wait(timeout=5)
            elapsed = t2_result.get("ms", 0)
            if elapsed > 500:
                print(f"  T2 INSERT: blocked then released ({elapsed:.0f}ms)")
                predicate_protected = True
            else:
                print(f"  T2 INSERT: immediate ({elapsed:.0f}ms)")
                print("  → GAP NOT locked for predicate-filtered index entries")
                print("  → Non-indexed predicate filtering creates a phantom window")
                predicate_protected = False
            x(t1, "commit")

        t1.close(); t2.close()
        s.close()

        # Summary
        print(f"\n{'=' * 60}")
        print(f"  Index entries touched:    2 (age=20 filtered, age=30 matched)")
        print(f"  GAP on filtered entry:    {'LOCKED' if blocked else 'NOT LOCKED'}")
        print(f"  Phantom window:           {'NONE' if blocked else 'PRESENT'}")
        if not blocked:
            print(f"  NOTE: has_match_ flag only set after check_all_conds()")
            print(f"        passes; filtered entries don't trigger GAP locks.")
            print(f"        InnoDB-style index-level gap locking would fix this.")
        print(f"{'=' * 60}")
        return predicate_protected

    finally:
        subprocess.run(["rm", "-rf", DB], capture_output=True)


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
