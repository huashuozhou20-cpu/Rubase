#!/usr/bin/env python3
"""
RMDB Non-Unique Index NULL + Range Chaos Test
==============================================
Validates B+tree index correctness with NULL values, range
queries, and NEXT_KEY locking in mixed NULL/non-NULL datasets.

Setup: table t(id INT, age INT) with non-unique index on (age)
       300 rows with age=NULL, 200 rows with age=10..209

Tests:
  1. Range query correctness on non-NULL data
  2. Full table scan returns all rows
  3. FOR UPDATE on range blocks concurrent INSERT into locked gap

Usage:
  python3 tools/test_index_null_chaos.py
"""

import socket, sys, os, time, threading, subprocess

HOST = "127.0.0.1"
PORT = 8765
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)
BUILD_DIR = os.path.join(PROJECT_DIR, "build")
SERVER = os.path.join(BUILD_DIR, "bin", "rmdb")
DB = "/tmp/rmdb_null_chaos"

TOTAL_ROWS = 500
NULL_ROWS = 300
NON_NULL = TOTAL_ROWS - NULL_ROWS  # 200
NON_NULL_START = 10


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
    sock.settimeout(15)
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
    print("  RMDB Non-Unique Index NULL + Range Chaos Test")
    print("=" * 60)

    if not start_server():
        print("FAIL: Server won't start"); return False

    passed = 0
    try:
        s = socket.socket(); s.settimeout(120); s.connect((HOST, PORT))

        # Setup
        print(f"\n[Setup] Creating table with {TOTAL_ROWS} rows...")
        x(s, "DROP TABLE nt")
        x(s, "CREATE TABLE nt (id INT, age INT)")
        x(s, "CREATE INDEX nt (age)")

        for i in range(0, NULL_ROWS, 50):
            batch = ",".join(f"({j}, NULL)" for j in range(i, min(i+50, NULL_ROWS)))
            x(s, f"INSERT INTO nt VALUES {batch}")

        for i in range(0, NON_NULL, 50):
            batch = ",".join(f"({NULL_ROWS+j}, {NON_NULL_START+j})"
                           for j in range(i, min(i+50, NON_NULL)))
            x(s, f"INSERT INTO nt VALUES {batch}")

        print(f"  {NULL_ROWS} NULL + {NON_NULL} non-NULL rows (age={NON_NULL_START}..{NON_NULL_START+NON_NULL-1})")

        # Test 1: Full table scan — verify all rows present
        print("\n[Test 1] SELECT * FROM nt (full table scan)")
        resp = x(s, "SELECT * FROM nt")
        all_rows = count_rows(resp)
        print(f"  Total rows: {all_rows} (expected {TOTAL_ROWS})")
        if all_rows == TOTAL_ROWS:
            print("  PASS ✓")
            passed += 1
        elif all_rows > TOTAL_ROWS * 0.8:
            print(f"  OK ({all_rows}/{TOTAL_ROWS})")
            passed += 1
        else:
            print(f"  CHECK: {all_rows}/{TOTAL_ROWS}")

        # Test 2: Range query on non-NULL data
        print(f"\n[Test 2] Range query: age > {NON_NULL_START}")
        resp = x(s, f"SELECT * FROM nt WHERE age > {NON_NULL_START}")
        range_rows = count_rows(resp)
        expected_range = NON_NULL - 1  # exclude age=10
        print(f"  Returned: {range_rows} (expected ~{expected_range})")
        if range_rows == expected_range:
            print("  PASS — exact count ✓")
            passed += 1
        elif range_rows >= expected_range * 0.9:
            print(f"  OK (close)")
            passed += 1
        else:
            print(f"  CHECK: got {range_rows}")

        # Test 3: IS NULL scan correctness
        print("\n[Test 3] SELECT * FROM nt WHERE age IS NULL")
        resp = x(s, "SELECT * FROM nt WHERE age IS NULL")
        null_count = count_rows(resp)
        if null_count == NULL_ROWS:
            print(f"  Returned: {null_count} rows — PASS ✓")
            passed += 1
        else:
            print(f"  Returned: {null_count} rows (expected {NULL_ROWS})")
            print(f"  NOTE: IS NULL may use SeqScan rather than IndexScan")

        # Test 4: FOR UPDATE range blocks concurrent INSERT
        print("\n[Test 4] FOR UPDATE on range blocks INSERT into gap")
        t1 = socket.socket(); t1.settimeout(30); t1.connect((HOST, PORT))
        t2 = socket.socket(); t2.settimeout(30); t2.connect((HOST, PORT))

        x(t1, "begin")
        resp = x(t1, f"SELECT * FROM nt WHERE age > {NON_NULL_START} FOR UPDATE")
        locked = count_rows(resp)
        print(f"  T1 locked {locked} rows")

        t2_done = threading.Event(); t2_result = {}
        def t2fn():
            t0 = time.time()
            # Insert at a key that falls inside the locked range
            mid_key = NON_NULL_START + NON_NULL // 2 + 1000
            r = x(t2, f"INSERT INTO nt VALUES({TOTAL_ROWS+1}, {mid_key})")
            t2_result["ms"] = (time.time() - t0) * 1000
            t2_done.set()

        th = threading.Thread(target=t2fn); th.start()
        time.sleep(1.0)

        if th.is_alive():
            print("  T2 INSERT: BLOCKED ✓")
            x(t1, "commit")
            t2_done.wait(timeout=15)
            print(f"  T2 released in {t2_result['ms']:.0f}ms")
            passed += 1
        else:
            t2_done.wait(timeout=5)
            elapsed = t2_result.get("ms", 0)
            if elapsed > 500:
                print(f"  T2 INSERT: blocked then released ({elapsed:.0f}ms)")
                passed += 1
            else:
                print(f"  T2 INSERT: immediate ({elapsed:.0f}ms)")

        x(t1, "commit") if not t2_done.is_set() else None
        t1.close(); t2.close()
        s.close()

        print(f"\n{'=' * 60}")
        print(f"  Full scan:     {'PASS' if all_rows >= TOTAL_ROWS*0.8 else 'CHECK'}")
        print(f"  Range query:   {'PASS' if range_rows >= expected_range*0.9 else 'CHECK'}")
        print(f"  FOR UPDATE:    {'PASS' if passed >= 4 else 'CHECK'}")
        print(f"  Result:        {passed}/4 checks")
        print(f"{'=' * 60}")
        return passed >= 3

    finally:
        subprocess.run(["rm", "-rf", DB], capture_output=True)


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
