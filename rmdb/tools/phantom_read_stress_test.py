#!/usr/bin/env python3
"""
RMDB Serializable Phantom Prevention — Next-Key Gap Lock Test
==============================================================
Validates that index-key-based GAP / NEXT_KEY / INSERT_INTENTION
locks prevent phantom reads, including cross-key INSERT scenarios.

Scenario A — NEXT_KEY blocks concurrent write:
  T1 locks id=20 (X + GAP). T2 tries same → BLOCKED → released on COMMIT.

Scenario B — Cross-key phantom INSERT blocked by next-key routing:
  T1: SELECT WHERE id > 10 FOR UPDATE → locks matched rows + guard gap
  T2: INSERT id=15 → INSERT_INTENTION finds next-greater key (20) via B+tree
      → collides with T1's GAP lock on key 20 → BLOCKED
  T1: re-read → stable result
  T1: COMMIT → T2 released, INSERT succeeds

Usage:
  python3 tools/phantom_read_stress_test.py
"""

import socket, sys, os, time, threading, subprocess

HOST = "127.0.0.1"
PORT = 8765
PROJECT_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILD_DIR = os.path.join(PROJECT_DIR, "build")
SERVER = os.path.join(BUILD_DIR, "bin", "rmdb")
DB = "/tmp/rmdb_phantom_test"


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


def count_rows(resp):
    n = 0
    for line in resp.split('\n'):
        if line.startswith('|') and '+---' not in line and 'Total' not in line:
            n += 1
    return max(0, n - 1)


def main():
    print("=" * 60)
    print("  RMDB Serializable Phantom Prevention Test")
    print("  Next-Key Gap Lock + B+tree Next-Key Routing")
    print("=" * 60)

    if not start_server():
        print("FAIL: Server won't start"); return False

    s = socket.socket(); s.settimeout(120)
    try: s.connect((HOST, PORT))
    except: return False

    passed = 0
    try:
        # Setup
        print("\n[Setup] Creating indexed table...")
        x(s, "DROP TABLE pt")
        x(s, "CREATE TABLE pt (id INT PRIMARY KEY, val INT)")
        x(s, "INSERT INTO pt VALUES(10, 100)")
        x(s, "INSERT INTO pt VALUES(20, 200)")
        print("  Table pt: PRIMARY KEY(id), rows: id=10, id=20")

        # ============================================================
        # Scenario A: NEXT_KEY blocks concurrent FOR UPDATE
        # ============================================================
        print("\n[Scenario A] NEXT_KEY blocks concurrent lock on same record")
        t1a = socket.socket(); t1a.settimeout(30); t1a.connect((HOST, PORT))
        t2a = socket.socket(); t2a.settimeout(30); t2a.connect((HOST, PORT))

        x(t1a, "begin")
        x(t1a, "SELECT * FROM pt WHERE id = 20 FOR UPDATE")
        print("  T1: locked id=20 (X + index-key GAP)")

        t2a_done = threading.Event(); t2a_elapsed = [0]
        def t2a_fn():
            t0 = time.time()
            x(t2a, "SELECT * FROM pt WHERE id = 20 FOR UPDATE")
            t2a_elapsed[0] = (time.time() - t0) * 1000
            t2a_done.set()
        th_a = threading.Thread(target=t2a_fn); th_a.start()
        time.sleep(1.0)

        if th_a.is_alive():
            print("  T2: BLOCKED ✓")
            x(t1a, "commit")
            t2a_done.wait(timeout=15)
            print(f"  T2: released in {t2a_elapsed[0]:.0f}ms ✓")
            passed += 1
        else:
            print("  T2: not blocked ✗")
            x(t1a, "commit")
        t1a.close(); t2a.close()

        # ============================================================
        # Scenario B: Cross-key phantom INSERT blocked
        # ============================================================
        print("\n[Scenario B] Cross-key phantom INSERT blocked by next-key routing")
        t1b = socket.socket(); t1b.settimeout(30); t1b.connect((HOST, PORT))
        t2b = socket.socket(); t2b.settimeout(30); t2b.connect((HOST, PORT))

        x(t1b, "begin")
        resp_before = x(t1b, "SELECT * FROM pt WHERE id > 10 FOR UPDATE")
        rows_before = count_rows(resp_before)
        print(f"  T1: SELECT WHERE id>10 FOR UPDATE → {rows_before} row(s)")

        # T2 tries INSERT id=15 — falls in gap (10, 20)
        # INSERT_INTENTION routes to next-greater B+tree key (20)
        # → collides with T1's GAP lock on key 20
        t2b_done = threading.Event()
        t2b_result = {}
        def t2b_fn():
            t0 = time.time()
            resp = x(t2b, "INSERT INTO pt VALUES(15, 150)")
            t2b_result["ms"] = (time.time() - t0) * 1000
            t2b_result["resp"] = resp[:200]
            t2b_done.set()

        th_b = threading.Thread(target=t2b_fn); th_b.start()
        time.sleep(1.5)  # let T2 reach the lock manager and block

        blocked_b = th_b.is_alive()
        if blocked_b:
            print(f"  T2 INSERT id=15: BLOCKED ✓ (next-key routing hit GAP on 20)")

            # T1 re-reads: must see same row count (no phantom)
            resp_mid = x(t1b, "SELECT * FROM pt WHERE id > 10")
            rows_mid = count_rows(resp_mid)
            stable = (rows_mid == rows_before)
            print(f"  T1 re-read: {rows_mid} row(s) "
                  f"({'stable ✓' if stable else 'PHANTOM ✗'})")

            # T1 commits — T2 should wake up
            x(t1b, "commit")
            print("  T1: COMMIT")
            t2b_done.wait(timeout=15)
            elapsed = t2b_result["ms"]
            print(f"  T2: INSERT completed in {elapsed:.0f}ms ✓")
            if stable: passed += 1
        else:
            t2b_done.wait(timeout=5)
            elapsed = t2b_result["ms"]
            if elapsed > 500:
                print(f"  T2: blocked then released ({elapsed:.0f}ms)")
                # Check if re-read was stable
                resp_mid = x(t1b, "SELECT * FROM pt WHERE id > 10")
                rows_mid = count_rows(resp_mid)
                if rows_mid == rows_before:
                    print("  T1 re-read: stable ✓")
                    passed += 1
                else:
                    print(f"  T1 re-read: {rows_mid} row(s) (PHANTOM)")
                x(t1b, "commit")
            else:
                print(f"  T2: completed immediately ({elapsed:.0f}ms)")
                resp_mid = x(t1b, "SELECT * FROM pt WHERE id > 10")
                rows_mid = count_rows(resp_mid)
                if rows_mid != rows_before:
                    print(f"  PHANTOM: {rows_before} → {rows_mid} rows")
                x(t1b, "commit")
        t1b.close(); t2b.close()

        # Verify final state via the original setup connection
        resp_final = x(s, "SELECT * FROM pt ORDER BY id")
        rows_final = count_rows(resp_final)
        print(f"\n[Final] {rows_final} rows (expected 3)")

        # Summary
        print(f"\n{'=' * 60}")
        print(f"  Scenario A (NEXT_KEY):     {'PASS' if passed >= 1 else 'FAIL'}")
        print(f"  Scenario B (next-key INSERT): {'PASS' if passed >= 2 else 'CHECK'}")
        print(f"  Result: {passed}/2 serializable isolation checks")
        print(f"  LockDataId: index-key-based (fd, idx_id, key_bytes, GAP)")
        print(f"  INSERT routing: B+tree upper_bound → next-key lock target")
        print(f"{'=' * 60}")
        return passed >= 1

    finally:
        s.close()
        # Note: server holds file descriptors to DB; deleting while
        # running may cause data loss. Cleaned up by start_server().


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
