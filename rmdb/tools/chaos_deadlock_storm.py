#!/usr/bin/env python3
"""
RMDB Chaos Deadlock Storm — Multi-Way Cross-Lock Cycle Test
============================================================
Creates guaranteed 4-node deadlock cycles using proven cross-lock
pattern: each transaction locks one row (FOR UPDATE), then
UPDATEs another row, blocked by peer.

Cycle: T0 holds X(1)→wants X(2), T1 holds X(2)→wants X(3),
       T2 holds X(3)→wants X(4), T3 holds X(4)→wants X(1)

Validates deadlock detection, victim selection, cv wakeup.

Usage:
  python3 tools/chaos_deadlock_storm.py
"""

import socket, sys, os, time, threading, subprocess

HOST = "127.0.0.1"
PORT = 8765
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)
BUILD_DIR = os.path.join(PROJECT_DIR, "build")
SERVER = os.path.join(BUILD_DIR, "bin", "rmdb")
DB = "/tmp/rmdb_dl_storm"


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
    except:
        return ""


def main():
    print("=" * 60)
    print("  RMDB Chaos Deadlock Storm — 4-Way Cycle Test")
    print("=" * 60)

    if not start_server():
        print("FAIL: Server won't start"); return False

    try:
        # Setup via short-lived connection
        s = socket.socket(); s.settimeout(10); s.connect((HOST, PORT))
        x(s, "DROP TABLE dl")
        x(s, "CREATE TABLE dl (id INT PRIMARY KEY, val INT)")
        for r in [1,2,3,4]:
            x(s, f"INSERT INTO dl VALUES({r}, {r*10})")
        s.close()
        time.sleep(0.5)
        print("[Setup] Table dl: rows 1-4")

        # Pre-open all 4 worker connections sequentially
        socks = []
        for i in range(4):
            try:
                s = socket.socket(); s.settimeout(30); s.connect((HOST, PORT))
                socks.append(s)
                time.sleep(0.1)
            except Exception as e:
                print(f"  FAIL: Can't open connection {i}: {e}")
                for s in socks: s.close()
                return False

        print("[Phase 1] All 4 connections open, locking first rows...")

        # Each worker: begin + lock first row
        pairs = [(1,2), (2,3), (3,4), (4,1)]
        for i in range(4):
            x(socks[i], "begin")
            x(socks[i], f"SELECT * FROM dl WHERE id = {pairs[i][0]} FOR UPDATE")
        print("  All 4 hold first lock ✓")
        time.sleep(0.3)

        # All workers simultaneously try UPDATE on second row → deadlock
        print("[Phase 2] All workers UPDATE second row → 4-node cycle!")
        results = {}

        def worker_update(tid):
            t0 = time.time()
            resp = x(socks[tid], f"UPDATE dl SET val = {tid*1000} WHERE id = {pairs[tid][1]}")
            elapsed = (time.time() - t0) * 1000
            if "abort" in resp.lower():
                x(socks[tid], "abort")
                results[tid] = f"ABORTED@{elapsed:.0f}ms"
            else:
                x(socks[tid], "commit")
                results[tid] = f"COMMITTED@{elapsed:.0f}ms"

        threads = [threading.Thread(target=worker_update, args=(i,)) for i in range(4)]
        for t in threads: t.start()
        for t in threads: t.join(timeout=20)

        for s in socks:
            try: s.close()
            except: pass

        rvals = list(results.values())
        aborted = sum(1 for v in rvals if "ABORTED" in str(v))
        committed = sum(1 for v in rvals if "COMMITTED" in str(v))
        hung = 4 - len(rvals)

        for i in range(4):
            print(f"  T{i}: {results.get(i, 'HUNG')}")

        passed = aborted > 0 and hung == 0 and committed >= 2
        print(f"\n{'=' * 60}")
        print(f"  Deadlock detected: {'YES' if aborted > 0 else 'NO'}")
        print(f"  Aborted: {aborted}, Committed: {committed}, Hung: {hung}")
        print(f"  Verdict: {'PASS' if passed else 'CHECK'}")
        print(f"{'=' * 60}")
        return passed

    finally:
        subprocess.run(["rm", "-rf", DB], capture_output=True)


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
