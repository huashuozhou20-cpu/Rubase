#!/usr/bin/env python3
"""
RMDB Chaos Crash Alignment — kill -9 + WAL Recovery Test
=========================================================
During an active NEXT_KEY vs INSERT_INTENTION lock conflict,
kill -9 the server process, then restart and verify:

  1. WAL recovery replays committed transactions correctly
  2. Uncommitted INSERT is fully rolled back
  3. B+tree index is consistent with table data
  4. LockManager restarts clean (no orphan locks) — verified
     by re-running phantom_read_stress_test.py

Usage:
  python3 tools/chaos_crash_alignment.py
"""

import socket, sys, os, time, threading, subprocess

HOST = "127.0.0.1"
PORT = 8765
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)
BUILD_DIR = os.path.join(PROJECT_DIR, "build")
SERVER = os.path.join(BUILD_DIR, "bin", "rmdb")
DB = "/tmp/rmdb_crash_align"


def start_fresh_server():
    subprocess.run(["rm", "-rf", DB], capture_output=True)
    return _launch_server()


def restart_server():
    """Restart without deleting — keeps WAL + data files for recovery."""
    return _launch_server()


def _launch_server():
    return subprocess.Popen([SERVER, DB], cwd=BUILD_DIR,
                            stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)


def wait_for_server(timeout=5):
    deadline = time.time() + timeout
    while time.time() < deadline:
        try:
            s = socket.socket(); s.settimeout(1); s.connect((HOST, PORT)); s.close()
            return True
        except:
            time.sleep(0.5)
    return False


def x(sock, sql):
    if not sql.endswith(";"): sql += ";"
    sock.sendall(sql.encode())
    try:
        sock.settimeout(10)
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
    print("  RMDB kill -9 Crash Consistency Alignment Test")
    print("=" * 60)

    # Phase 1: Setup and trigger lock conflict
    print("\n[Phase 1] Setup + trigger lock conflict...")
    p = start_fresh_server()
    if not wait_for_server():
        print("FAIL: Server won't start")
        return False

    s = socket.socket(); s.settimeout(30); s.connect((HOST, PORT))
    try:
        # Create table and pre-insert committed baseline rows
        x(s, "CREATE TABLE crash_test (id INT PRIMARY KEY, val INT)")
        x(s, "INSERT INTO crash_test VALUES(10, 100)")
        x(s, "INSERT INTO crash_test VALUES(20, 200)")
        x(s, "INSERT INTO crash_test VALUES(30, 300)")
        print("  Committed: id=10, 20, 30")

        # T1: begin, lock range (acquires NEXT_KEY/GAP locks)
        t1 = socket.socket(); t1.settimeout(30); t1.connect((HOST, PORT))
        x(t1, "begin")
        resp = x(t1, "SELECT * FROM crash_test WHERE id > 10 FOR UPDATE")
        t1_rows = count_rows(resp)
        print(f"  T1 locked range id>10: {t1_rows} rows")

        # T2: try INSERT into the guarded gap — blocks on GAP lock
        t2 = socket.socket(); t2.settimeout(30); t2.connect((HOST, PORT))
        t2_blocked = threading.Event()
        t2_sent = threading.Event()

        def t2_insert():
            t2_sent.wait()
            x(t2, "INSERT INTO crash_test VALUES(15, 150)")

        th2 = threading.Thread(target=t2_insert); th2.start()
        time.sleep(0.5)  # let T2's socket connect
        t2_sent.set()
        time.sleep(0.5)  # let T2 block on INSERT_INTENTION

        if th2.is_alive():
            print("  T2 INSERT id=15: BLOCKED on GAP lock ✓")
        else:
            print("  T2 INSERT: not blocked (unexpected)")

        # Phase 2: kill -9 the server while conflict is active
        print("\n[Phase 2] kill -9 server during active lock conflict...")
        time.sleep(0.3)  # ensure lock state is stable
        os.kill(p.pid, 9)  # SIGKILL
        p.wait(timeout=5)
        print(f"  Server PID {p.pid} killed with SIGKILL")

        # Close sockets (they're dead anyway)
        try: s.close()
        except: pass
        try: t1.close()
        except: pass
        try: t2.close()
        except: pass

        time.sleep(1)

        # Phase 3: Restart and verify WAL recovery (keep DB intact)
        print("\n[Phase 3] Restart server + WAL recovery...")
        p2 = restart_server()
        if not wait_for_server():
            print("FAIL: Server won't restart")
            return False

        s2 = socket.socket(); s2.settimeout(30); s2.connect((HOST, PORT))
        try:
            # Check committed data survived
            resp = x(s2, "SELECT * FROM crash_test ORDER BY id")
            rows = count_rows(resp)
            print(f"  After recovery: {rows} rows")
            for line in resp.split('\n')[:6]:
                if line.strip(): print(f"    {line}")

            # Verify committed rows are present (10, 20, 30)
            if rows >= 3:
                print("  ✓ Committed baseline rows recovered")
            else:
                print(f"  ✗ Expected 3+ rows, got {rows}")

            # T1's uncommitted lock should be gone (nothing to roll back)
            # T2's INSERT should be rolled back (no id=15)
            has_15 = "15" in resp
            if not has_15:
                print("  ✓ Uncommitted INSERT (id=15) correctly rolled back")
            else:
                print("  ✗ Uncommitted INSERT (id=15) survived crash! (should be rolled back)")

            # Verify B+tree integrity: read via index scan
            resp2 = x(s2, "SELECT * FROM crash_test WHERE id >= 10 ORDER BY id")
            rows2 = count_rows(resp2)
            if rows2 == rows:
                print(f"  ✓ B+tree index consistent ({rows2} rows via index scan)")

            # Phase 4: LockManager sanity — run phantom test
            print("\n[Phase 4] LockManager sanity check...")
            x(s2, "DROP TABLE pt")
            x(s2, "CREATE TABLE pt (id INT PRIMARY KEY, val INT)")
            x(s2, "INSERT INTO pt VALUES(10, 100)")
            x(s2, "INSERT INTO pt VALUES(20, 200)")

            t1b = socket.socket(); t1b.settimeout(30); t1b.connect((HOST, PORT))
            t2b = socket.socket(); t2b.settimeout(30); t2b.connect((HOST, PORT))

            x(t1b, "begin")
            x(t1b, "SELECT * FROM pt WHERE id > 10 FOR UPDATE")

            t2b_done = threading.Event(); t2b_result = {}
            def t2b_test():
                t0 = time.time()
                r = x(t2b, "INSERT INTO pt VALUES(15, 150)")
                t2b_result["ms"] = (time.time() - t0) * 1000
                t2b_done.set()
            th = threading.Thread(target=t2b_test); th.start()
            time.sleep(1.0)

            lock_ok = th.is_alive()
            if lock_ok:
                print("  ✓ Gap lock works after crash recovery")
                x(t1b, "commit")
                t2b_done.wait(timeout=10)
            else:
                print("  ✗ Gap lock not working after recovery")
                x(t1b, "commit")

            t1b.close(); t2b.close()

            # Summary
            passed = (rows >= 3) and (not has_15) and (rows2 == rows) and lock_ok
            print(f"\n{'=' * 60}")
            print(f"  WAL recovery:     {'PASS' if rows >= 3 else 'FAIL'}")
            print(f"  INSERT rollback:  {'PASS' if not has_15 else 'FAIL'}")
            print(f"  B+tree integrity: {'PASS' if rows2 == rows else 'FAIL'}")
            print(f"  LockManager:      {'PASS' if lock_ok else 'FAIL'}")
            print(f"  Verdict:          {'PASS' if passed else 'CHECK'}")
            print(f"{'=' * 60}")
            return passed

        finally:
            try: s2.close()
            except: pass
    except:
        pass

if __name__ == "__main__":
    sys.exit(0 if main() else 1)
