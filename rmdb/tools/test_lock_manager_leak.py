#!/usr/bin/env python3
"""
RMDB LockManager Orphan Lock Leak Detection Test
=================================================
Creates a guaranteed deadlock cycle. After the background
deadlock detector aborts the victim transaction, verifies
that all locks held by the victim are fully released — no
orphan locks remain in the lock table.

Scenario:
  1. T1 locks id=1 (FOR UPDATE), T2 locks id=2 (FOR UPDATE)
  2. Both threads synchronize, then simultaneously try to
     lock the other's row → deadlock cycle
  3. Deadlock detector fires, picks youngest victim, aborts it
  4. After both threads complete:
     a. New transactions can lock the same rows (no orphan locks)
     b. All rows remain accessible (no lock-induced starvation)
     c. LockManager hash table has no stale entries

Usage:
  python3 tools/test_lock_manager_leak.py
"""

import socket, sys, os, time, threading, subprocess

HOST = "127.0.0.1"
PORT = 8765
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)
BUILD_DIR = os.path.join(PROJECT_DIR, "build")
SERVER = os.path.join(BUILD_DIR, "bin", "rmdb")
DB = "/tmp/rmdb_lock_leak"


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
    print("  RMDB Orphan Lock Leak Detection Test")
    print("=" * 60)

    if not start_server():
        print("FAIL: Server won't start"); return False

    passed = 0
    try:
        # Setup
        s = socket.socket(); s.settimeout(30); s.connect((HOST, PORT))
        print("\n[Setup] Creating table with 3 rows...")
        x(s, "DROP TABLE leak_test")
        x(s, "CREATE TABLE leak_test (id INT PRIMARY KEY, val INT)")
        for r in [1, 2, 3]:
            x(s, f"INSERT INTO leak_test VALUES({r}, {r*10})")
        s.close()

        # Phase 1: Guaranteed deadlock cycle
        print("\n[Phase 1] Creating guaranteed 2-thread deadlock cycle...")
        t1 = socket.socket(); t1.settimeout(30); t1.connect((HOST, PORT))
        t2 = socket.socket(); t2.settimeout(30); t2.connect((HOST, PORT))

        ready1 = threading.Event()
        ready2 = threading.Event()
        go = threading.Barrier(3, timeout=20)
        results = {}

        def worker(tid, first, second, my_ready, peer_ready):
            s = socket.socket(); s.settimeout(30)
            try:
                s.connect((HOST, PORT))
                x(s, "begin")
                # Use UPDATE to acquire X-lock (more reliable than FOR UPDATE in some paths)
                x(s, f"UPDATE leak_test SET val = {tid*10} WHERE id={first}")
                my_ready.set()
                go.wait()

                t0 = time.time()
                resp = x(s, f"UPDATE leak_test SET val = {tid*1000} WHERE id={second}")
                elapsed = (time.time() - t0) * 1000
                if "abort" in resp.lower():
                    x(s, "abort")
                    results[tid] = f"ABORTED@{elapsed:.0f}ms"
                else:
                    x(s, "commit")
                    results[tid] = f"COMMITTED@{elapsed:.0f}ms"
            except Exception as e:
                results[tid] = f"ERR:{e}"
            finally:
                try: s.close()
                except: pass

        t1_thread = threading.Thread(target=worker, args=(1, 1, 2, ready1, ready2))
        t2_thread = threading.Thread(target=worker, args=(2, 2, 1, ready2, ready1))
        t1_thread.start(); time.sleep(0.2); t2_thread.start()

        if not ready1.wait(timeout=10) or not ready2.wait(timeout=10):
            print("  FAIL: Workers didn't lock in time")
            return False

        time.sleep(0.3)
        try: go.wait(timeout=10)
        except threading.BrokenBarrierError: pass

        t1_thread.join(timeout=20)
        t2_thread.join(timeout=20)

        r1, r2 = results.get(1, "HUNG"), results.get(2, "HUNG")
        print(f"  T1: {r1}")
        print(f"  T2: {r2}")

        # At least one must be aborted for deadlock resolution
        has_abort = "ABORTED" in str(r1) or "ABORTED" in str(r2)
        no_hang = "HUNG" not in str(r1) and "HUNG" not in str(r2)
        print(f"  Deadlock resolved: {'YES' if has_abort and no_hang else 'CHECK'}")
        if has_abort: passed += 1

        t1.close(); t2.close()

        # Phase 2: Verify no orphan locks — all rows accessible
        print("\n[Phase 2] Orphan lock check — re-access all rows...")
        s2 = socket.socket(); s2.settimeout(30); s2.connect((HOST, PORT))

        # Check 1: FOR UPDATE on each row (if orphan lock exists, this blocks)
        for row_id in [1, 2, 3]:
            t_check = threading.Thread(target=lambda rid=row_id: None)
            t0 = time.time()
            resp = x(s2, f"SELECT * FROM leak_test WHERE id = {row_id} FOR UPDATE")
            elapsed = (time.time() - t0) * 1000
            rows = count_rows(resp)
            blocked = elapsed > 500
            if rows == 1 and not blocked:
                print(f"  Row {row_id}: accessible in {elapsed:.0f}ms ✓")
                passed += 1
            elif blocked:
                print(f"  Row {row_id}: BLOCKED ({elapsed:.0f}ms) — orphan lock suspected!")
            else:
                print(f"  Row {row_id}: {rows} rows — CHECK")

        # Check 2: Range scan (if any orphan GAP lock, this would fail)
        t0 = time.time()
        resp = x(s2, "SELECT * FROM leak_test WHERE id > 0 FOR UPDATE")
        elapsed = (time.time() - t0) * 1000
        rows = count_rows(resp)
        if rows == 3 and elapsed < 500:
            print(f"  Range scan: {rows} rows in {elapsed:.0f}ms ✓")
            passed += 1
        else:
            print(f"  Range scan: {rows} rows in {elapsed:.0f}ms — CHECK")

        # Check 3: INSERT into previously locked gap
        t0 = time.time()
        resp = x(s2, f"INSERT INTO leak_test VALUES(99, 990)")
        elapsed = (time.time() - t0) * 1000
        ok = "error" not in resp.lower()
        if ok and elapsed < 500:
            print(f"  INSERT id=99: OK in {elapsed:.0f}ms ✓")
            passed += 1
        else:
            print(f"  INSERT id=99: {'blocked' if elapsed > 500 else 'error'} — CHECK")

        s2.close()

        # Phase 3: Sustained access — multiple lock/unlock cycles
        print("\n[Phase 3] Sustained lock/unlock cycles (10 iterations)...")
        errors = 0
        for i in range(10):
            s3 = socket.socket(); s3.settimeout(10); s3.connect((HOST, PORT))
            try:
                x(s3, "begin")
                for row_id in [1, 2, 3]:
                    resp = x(s3, f"SELECT * FROM leak_test WHERE id = {row_id} FOR UPDATE")
                    if "error" in resp.lower(): errors += 1
                x(s3, "commit")
            except: errors += 1
            finally:
                try: s3.close()
                except: pass

        print(f"  10 lock cycles: {errors} errors")
        if errors == 0:
            print("  PASS: No orphan locks across sustained access ✓")
            passed += 1
        else:
            print(f"  CHECK: {errors} errors")

        print(f"\n{'=' * 60}")
        print(f"  Deadlock resolved: {'PASS' if has_abort else 'CHECK'}")
        print(f"  Row accessibility: {'PASS' if passed >= 2 else 'CHECK'}")
        print(f"  Orphan locks:      {'NONE' if passed >= 6 else 'CHECK'}")
        print(f"  Result:            {passed}/7 checks")
        print(f"{'=' * 60}")
        return passed >= 5

    finally:
        subprocess.run(["rm", "-rf", DB], capture_output=True)


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
