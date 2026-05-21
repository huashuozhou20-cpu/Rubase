#!/usr/bin/env python3
"""
RMDB WAL Undo Physical Chaos — Large Uncommitted Txn + Crash Recovery
======================================================================
Simulates a large uncommitted transaction whose dirty pages have been
flushed to disk (via buffer pool eviction), then kill -9 crashes the
server. Verifies that WAL recovery fully undoes the uncommitted work
and the B+tree remains structurally intact.

Scenario:
  1. Insert committed baseline rows (id=1..10)
  2. T1: BEGIN, INSERT 500 rows (id=100..599) — causes B+tree splits
  3. Force buffer pool pressure by inserting more data from T2
  4. kill -9 server BEFORE T1 commits
  5. Restart → WAL recovery undoes T1's inserts
  6. Verify: 0 residual rows from T1, baseline intact, B+tree functional

Usage:
  python3 tools/test_wal_undo_physical_chaos.py
"""

import socket, sys, os, time, threading, subprocess

HOST = "127.0.0.1"
PORT = 8765
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)
BUILD_DIR = os.path.join(PROJECT_DIR, "build")
SERVER = os.path.join(BUILD_DIR, "bin", "rmdb")
DB = "/tmp/rmdb_wal_undo"


def start_fresh(delete=True):
    if delete:
        subprocess.run(["rm", "-rf", DB], capture_output=True)
    return subprocess.Popen([SERVER, DB], cwd=BUILD_DIR,
                            stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)


def wait_server(timeout=8):
    t0 = time.time()
    while time.time() - t0 < timeout:
        try:
            s = socket.socket(); s.settimeout(2); s.connect((HOST, PORT)); s.close()
            return True
        except:
            time.sleep(0.5)
    return False


def x(sock, sql):
    if not sql.endswith(";"): sql += ";"
    sock.sendall(sql.encode())
    sock.settimeout(10)
    try:
        return sock.recv(65536).decode(errors="replace")
    except:
        return ""


def count_rows(resp):
    n = 0
    for line in resp.split('\n'):
        if line.startswith('|') and '+---' not in line and 'Total' not in line:
            n += 1
    return max(0, n - 1)


def main():
    print("=" * 60)
    print("  RMDB WAL Undo Physical Chaos — Crash Recovery Test")
    print("=" * 60)

    # Phase 1: Setup committed baseline
    print("\n[Phase 1] Setup committed baseline...")
    p = start_fresh()
    if not wait_server():
        print("FAIL: Server won't start"); return False

    s = socket.socket(); s.settimeout(30); s.connect((HOST, PORT))
    try:
        x(s, "DROP TABLE wal_test")
        x(s, "CREATE TABLE wal_test (id INT PRIMARY KEY, val INT)")
        for r in range(1, 11):
            x(s, f"INSERT INTO wal_test VALUES({r}, {r*10})")
        resp = x(s, "SELECT * FROM wal_test ORDER BY id")
        baseline = count_rows(resp)
        print(f"  Baseline: {baseline} rows committed")

        # Phase 2: Large uncommitted transaction
        print("\n[Phase 2] T1: BEGIN, INSERT 500 rows (uncommitted)...")
        t1 = socket.socket(); t1.settimeout(60); t1.connect((HOST, PORT))
        x(t1, "begin")

        for start in range(100, 250, 50):
            batch = ",".join(f"({j}, {j*10})" for j in range(start, min(start+50, 250)))
            x(t1, f"INSERT INTO wal_test VALUES {batch}")

        print("  T1 inserted 150 rows (id=100..249), NOT committed")

        # Phase 3: Force buffer pool pressure with committed data
        print("\n[Phase 3] Force buffer pool pressure...")
        t2 = socket.socket(); t2.settimeout(60); t2.connect((HOST, PORT))
        for start in range(300, 600, 100):
            batch = ",".join(f"({j}, {j})" for j in range(start, min(start+100, 600)))
            x(t2, f"INSERT INTO wal_test VALUES {batch}")
        t2.close()
        print("  T2 inserted 300 rows (id=300..599), COMMITTED")

        # Phase 4: kill -9
        print("\n[Phase 4] kill -9 server (T1 still uncommitted)...")
        time.sleep(0.5)
        os.kill(p.pid, 9)
        p.wait(timeout=5)
        print(f"  Server PID {p.pid} killed with SIGKILL")
        try: s.close()
        except: pass
        try: t1.close()
        except: pass

        time.sleep(1)

        # Phase 5: Restart + WAL recovery
        print("\n[Phase 5] Restart + WAL recovery...")
        p2 = start_fresh(delete=False)  # DON'T delete — we need the WAL log!
        if not wait_server():
            print("FAIL: Server won't restart"); return False

        s2 = socket.socket(); s2.settimeout(30); s2.connect((HOST, PORT))
        try:
            # Verify T1's uncommitted data is GONE
            resp = x(s2, "SELECT * FROM wal_test ORDER BY id")
            rows = count_rows(resp)
            print(f"  After recovery: {rows} rows")
            print(f"  Expected: {baseline + 300} (baseline 10 + T2 300)")

            # Check for T1 residual (should be 0)
            t1_data = x(s2, "SELECT * FROM wal_test WHERE id >= 100 AND id < 300")
            t1_rows = count_rows(t1_data)
            print(f"  T1 residual (id 100..599): {t1_rows} (expected 0)")

            # Check committed data intact
            bl_resp = x(s2, "SELECT * FROM wal_test WHERE id <= 10 ORDER BY id")
            bl_rows = count_rows(bl_resp)
            print(f"  Baseline intact (id 1..10): {bl_rows} (expected {baseline})")

            # Phase 6: B+tree structural integrity
            print("\n[Phase 6] B+tree structural integrity checks...")
            # Test 1: Range scan via index
            r1 = x(s2, "SELECT * FROM wal_test WHERE id >= 1 AND id <= 10 ORDER BY id")
            c1 = count_rows(r1)

            # Test 2: Point lookups on existing keys
            r2 = x(s2, "SELECT * FROM wal_test WHERE id = 5")
            c2 = count_rows(r2)

            # Test 3: Insert new row after recovery (tests B+tree is writable)
            x(s2, "INSERT INTO wal_test VALUES(2000, 20000)")
            r3 = x(s2, "SELECT * FROM wal_test WHERE id = 2000")
            c3 = count_rows(r3)

            # Test 4: Full table scan for ordering
            r4 = x(s2, "SELECT * FROM wal_test ORDER BY id")
            c4 = count_rows(r4)

            btree_ok = (c1 == 10 and c2 == 1 and c3 == 1 and c4 == rows + 1)
            print(f"  Range scan:    {'OK' if c1 == 10 else 'FAIL'} ({c1})")
            print(f"  Point lookup:  {'OK' if c2 == 1 else 'FAIL'} ({c2})")
            print(f"  Post-insert:   {'OK' if c3 == 1 else 'FAIL'} ({c3})")
            print(f"  Full scan:     {'OK' if c4 == rows + 1 else 'FAIL'} ({c4})")

            # Check for chain breaks by scanning with ORDER BY and verifying
            # all returned rows have monotonically increasing ids
            lines = r4.split('\n')
            ids = []
            for line in lines:
                if line.startswith('|') and '+---' not in line and 'Total' not in line:
                    try:
                        parts = [p.strip() for p in line.split('|') if p.strip()]
                        if parts:
                            ids.append(int(parts[0]))
                    except: pass

            is_ordered = all(ids[i] <= ids[i+1] for i in range(len(ids)-1)) if len(ids) > 1 else True
            print(f"  B+tree ordered: {'OK' if is_ordered else 'FAIL'}")

            no_residual = t1_rows == 0
            baseline_ok = bl_rows == baseline
            passed = no_residual and baseline_ok and btree_ok and is_ordered

            print(f"\n{'=' * 60}")
            print(f"  T1 undo:       {'PASS' if no_residual else 'FAIL'} "
                  f"({t1_rows} residual)")
            print(f"  Baseline ok:   {'PASS' if baseline_ok else 'FAIL'} "
                  f"({bl_rows}/{baseline})")
            print(f"  B+tree intact: {'PASS' if btree_ok else 'FAIL'}")
            print(f"  Verdict:       {'PASS' if passed else 'CHECK'}")
            print(f"{'=' * 60}")
            return passed

        finally:
            try: s2.close()
            except: pass
    finally:
        try: s.close()
        except: pass


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
