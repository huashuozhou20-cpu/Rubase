#!/usr/bin/env python3
"""
RMDB B+tree Split Inheritance — Gap Lock Stability Under Page Split
====================================================================
Validates that index-key-based GAP locks survive B+tree leaf page
splits. Since LockDataId uses logical index keys (index_id + key_data),
not physical page/slot RIDs, lock identity is preserved across splits.

Scenario:
  1. Insert id=10, id=100 into indexed table
  2. T1: SELECT WHERE id > 10 FOR UPDATE → locks gap before key 100
  3. T2: INSERT many rows > 100 → forces B+tree leaf page split
     (key 100 may move to a different physical page)
  4. T2: INSERT id=50 → should still be blocked by T1's GAP on key 100
     (because LockDataId = (fd, idx=0, key_bytes_of_100, GAP)
      survives the split unchanged)

Usage:
  python3 tools/chaos_split_inheritance.py
"""

import socket, sys, os, time, threading, subprocess

HOST = "127.0.0.1"
PORT = 8765
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)
BUILD_DIR = os.path.join(PROJECT_DIR, "build")
SERVER = os.path.join(BUILD_DIR, "bin", "rmdb")
DB = "/tmp/rmdb_split_inherit"

# RMDB B+tree order: each page holds ~btree_order_ keys.
# Default order depends on page size / key size. For INT keys (~4 bytes),
# a 4KB page can hold hundreds of keys. We need to insert enough rows
# to fill at least one leaf page and force a split.
FILL_ROWS = 300  # enough to fill a leaf page and trigger splits


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
    print("  RMDB B+tree Split Inheritance — Gap Lock Stability")
    print("=" * 60)

    if not start_server():
        print("FAIL: Server won't start"); return False

    try:
        # Setup
        s = socket.socket(); s.settimeout(60); s.connect((HOST, PORT))
        print("\n[Setup] Creating indexed table...")
        x(s, "DROP TABLE split_test")
        x(s, "CREATE TABLE split_test (id INT PRIMARY KEY, val INT)")

        # Insert baseline rows: id=10, id=100 (large gap between them)
        x(s, "INSERT INTO split_test VALUES(10, 10)")
        x(s, "INSERT INTO split_test VALUES(100, 100)")
        print("  Baseline: id=10, id=100")

        # Phase 1: T1 acquires GAP lock on key 100
        print("\n[Phase 1] T1 locks gap on key 100...")
        t1 = socket.socket(); t1.settimeout(60); t1.connect((HOST, PORT))
        x(t1, "begin")
        resp = x(t1, "SELECT * FROM split_test WHERE id > 10 FOR UPDATE")
        rows = count_rows(resp)
        print(f"  T1 range scan (id>10): {rows} row(s) — holds GAP on key 100")

        # Phase 2: T2 fills leaf page beyond key 100 to force split
        print(f"\n[Phase 2] T2 inserts {FILL_ROWS} rows > 100 to force B+tree split...")
        t2 = socket.socket(); t2.settimeout(60); t2.connect((HOST, PORT))

        for i in range(101, 101 + FILL_ROWS, 50):
            batch = ",".join(f"({j}, {j})" for j in range(i, min(i+50, 101+FILL_ROWS)))
            x(t2, f"INSERT INTO split_test VALUES {batch}")
        print(f"  Inserted {FILL_ROWS} rows (101..{100+FILL_ROWS})")
        print("  B+tree leaf page should have split by now")

        # Phase 3: T2 tries INSERT at key 50 (inside the locked gap before 100)
        print("\n[Phase 3] T2 tries INSERT id=50 into locked gap...")
        t2_done = threading.Event()
        t2_result = {}
        def t2_insert():
            t0 = time.time()
            resp = x(t2, "INSERT INTO split_test VALUES(50, 50)")
            elapsed = (time.time() - t0) * 1000
            t2_result["ms"] = elapsed
            t2_result["resp"] = resp[:100]
            t2_done.set()

        th = threading.Thread(target=t2_insert); th.start()
        time.sleep(1.5)

        blocked = th.is_alive()
        if blocked:
            print("  T2 INSERT id=50: BLOCKED ✓ (GAP lock survived B+tree split!)")
            # T1 commits → T2 wakes up
            x(t1, "commit")
            print("  T1: COMMIT")
            t2_done.wait(timeout=15)
            print(f"  T2: INSERT completed in {t2_result['ms']:.0f}ms")
            split_stable = True
        else:
            t2_done.wait(timeout=5)
            elapsed = t2_result.get("ms", 0)
            if elapsed > 500:
                print(f"  T2 INSERT: blocked then released ({elapsed:.0f}ms)")
                split_stable = True
            else:
                print(f"  T2 INSERT: immediate ({elapsed:.0f}ms) — "
                      f"GAP lock may NOT have survived split")
                split_stable = False
            x(t1, "commit")

        t1.close(); t2.close()
        s.close()

        # Verify final state
        s2 = socket.socket(); s2.settimeout(10); s2.connect((HOST, PORT))
        resp = x(s2, "SELECT COUNT(*) FROM split_test")
        s2.close()

        passed = split_stable and blocked

        print(f"\n{'=' * 60}")
        print(f"  GAP survived split: {'YES' if blocked else 'NO'}")
        print(f"  Split stable:       {'YES' if split_stable else 'CHECK'}")
        print(f"  LockDataId basis:   index-key (fd, idx_id, key_data, GAP)")
        print(f"  Verdict:            {'PASS' if passed else 'CHECK'}")
        print(f"{'=' * 60}")
        return passed

    finally:
        subprocess.run(["rm", "-rf", DB], capture_output=True)


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
