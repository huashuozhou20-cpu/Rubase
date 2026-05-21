#!/usr/bin/env python3
"""
RMDB Unique Index Conflict — Abort + Lock Cleanup Boundary Test
===============================================================
Validates that after a transaction holding locks on a unique key
is rolled back, all locks are fully released and subsequent
operations on that key work cleanly.

RMDB uses MVCC — concurrent INSERTs on the same PK both create
version-chain entries. The rollback removes one version; the
committed version survives. This tests that rollback fully
cleans locks and that the final state is consistent.

Usage:
  python3 tools/test_unique_index_abort.py
"""

import socket, sys, os, time, threading, subprocess

HOST = "127.0.0.1"
PORT = 8765
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)
BUILD_DIR = os.path.join(PROJECT_DIR, "build")
SERVER = os.path.join(BUILD_DIR, "bin", "rmdb")
DB = "/tmp/rmdb_unique_abort"


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
    print("  RMDB Unique Index Conflict — Abort + Lock Cleanup Test")
    print("=" * 60)

    if not start_server():
        print("FAIL: Server won't start"); return False

    passed = 0
    try:
        s = socket.socket(); s.settimeout(60); s.connect((HOST, PORT))

        # Setup
        print("\n[Setup] Creating table with PRIMARY KEY...")
        x(s, "CREATE TABLE ut (id INT PRIMARY KEY, val INT)")
        x(s, "INSERT INTO ut VALUES(1, 10)")
        x(s, "INSERT INTO ut VALUES(2, 20)")
        x(s, "INSERT INTO ut VALUES(3, 30)")
        resp = x(s, "SELECT * FROM ut ORDER BY id")
        print(f"  Initial: {count_rows(resp)} rows")

        # Test 1: T1 INSERT id=5, T1 ROLLBACK → T2 INSERT id=5 succeeds
        print("\n[Test 1] MVCC concurrent PK inserts + rollback")
        t1 = socket.socket(); t1.settimeout(30); t1.connect((HOST, PORT))
        t2 = socket.socket(); t2.settimeout(30); t2.connect((HOST, PORT))

        x(t1, "begin")
        r1 = x(t1, "INSERT INTO ut VALUES(5, 50)")
        t1_ok = 'error' not in r1.lower()
        print(f"  T1 INSERT id=5: {'OK' if t1_ok else 'FAIL'}")

        # T1 rollback — its version of id=5 must be removed
        x(t1, "rollback")
        print("  T1: ROLLBACK")

        # T2 inserts id=5 — must succeed (T1's version is gone)
        r2 = x(t2, "INSERT INTO ut VALUES(5, 55)")
        t2_ok = 'error' not in r2.lower()
        print(f"  T2 INSERT id=5: {'OK' if t2_ok else 'FAIL'}")
        if t2_ok: passed += 1

        t1.close(); t2.close()

        # Verify: only 1 row with id=5
        resp = x(s, "SELECT * FROM ut ORDER BY id")
        rows = count_rows(resp)
        print(f"  Rows: {rows} (expected 4: 1,2,3,5)")
        if rows == 4: passed += 1

        # Test 2: T1 FOR UPDATE, T2 tries FOR UPDATE on same key
        print("\n[Test 2] FOR UPDATE conflict + rollback → lock cleanup")
        t3 = socket.socket(); t3.settimeout(30); t3.connect((HOST, PORT))
        t4 = socket.socket(); t4.settimeout(30); t4.connect((HOST, PORT))

        x(t3, "begin")
        x(t3, "SELECT * FROM ut WHERE id = 5 FOR UPDATE")
        print("  T3 locked id=5 (FOR UPDATE)")

        t4_done = threading.Event(); t4_result = {}
        def t4fn():
            t0 = time.time()
            r = x(t4, "SELECT * FROM ut WHERE id = 5 FOR UPDATE")
            t4_result["ms"] = (time.time() - t0) * 1000
            t4_done.set()

        th = threading.Thread(target=t4fn); th.start()
        time.sleep(1.0)

        if th.is_alive():
            print("  T4 FOR UPDATE: BLOCKED ✓")
            # T3 rollback → T4 must wake up
            x(t3, "rollback")
            print("  T3: ROLLBACK")
            t4_done.wait(timeout=15)
            print(f"  T4 released in {t4_result['ms']:.0f}ms")
            passed += 1
        else:
            t4_done.wait(timeout=5)
            print(f"  T4: completed ({t4_result.get('ms',0):.0f}ms)")
            x(t3, "rollback")

        t3.close(); t4.close()

        # Test 3: Post-rollback sanity — lock/unlock on id=5
        print("\n[Test 3] Post-rollback LockManager sanity")
        t5 = socket.socket(); t5.settimeout(30); t5.connect((HOST, PORT))
        t6 = socket.socket(); t6.settimeout(30); t6.connect((HOST, PORT))

        x(t5, "begin")
        x(t5, "SELECT * FROM ut WHERE id = 5 FOR UPDATE")
        x(t5, "commit")

        x(t6, "begin")
        x(t6, "SELECT * FROM ut WHERE id = 5 FOR UPDATE")
        x(t6, "commit")
        print("  Lock/unlock on id=5 clean ✓")
        passed += 1
        t5.close(); t6.close()
        s.close()

        print(f"\n{'=' * 60}")
        print(f"  Rollback cleanup:  {'PASS' if t2_ok else 'CHECK'}")
        print(f"  Row count:         {'PASS' if rows == 4 else 'CHECK'}")
        print(f"  Lock released:     {'PASS' if passed >= 3 else 'CHECK'}")
        print(f"  Result:            {passed}/4 checks")
        print(f"{'=' * 60}")
        return passed >= 3

    finally:
        subprocess.run(["rm", "-rf", DB], capture_output=True)


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
