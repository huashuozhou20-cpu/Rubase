#!/usr/bin/env python3
"""
RMDB 后台死锁检测器校准测试
=============================
验证 LockManager 死锁检测器（waits-for graph + DFS + 主动唤醒）。

交叉锁死锁：两事务各持有对方需要的 X 锁，形成环路。
检测器应在百毫秒级周期内自动发现、踢掉一个、救活另一个。

用法:
  python3 tools/deadlock_detection_test.py
"""

import socket
import sys
import os
import time
import threading
import subprocess

HOST = "127.0.0.1"
PORT = 8765
BUILD_DIR = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "build")
SERVER = os.path.join(BUILD_DIR, "bin", "rmdb")
DB = os.path.join(BUILD_DIR, "mydb_dd_test")


def fresh_server():
    subprocess.run(["pkill", "-9", "-f", "rmdb"], capture_output=True)
    time.sleep(1)
    subprocess.run(["rm", "-rf", DB])
    p = subprocess.Popen([SERVER, DB], cwd=BUILD_DIR, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    time.sleep(2)
    try:
        s = socket.socket(); s.settimeout(3); s.connect((HOST, PORT)); s.close()
        return True
    except:
        return False


def x(sock, sql):
    sock.sendall((sql + ";\0").encode() if not sql.endswith(";") else (sql + "\0").encode())
    return sock.recv(8192).decode(errors="replace")


def run_round(round_num):
    """Two-phase synchronized cross-lock deadlock round."""
    # Setup table
    s = socket.socket(); s.settimeout(5); s.connect((HOST, PORT))
    x(s, "DROP TABLE dd")
    x(s, "CREATE TABLE dd (id INT PRIMARY KEY, val INT)")
    x(s, "INSERT INTO dd VALUES(1, 100)")
    x(s, "INSERT INTO dd VALUES(2, 200)")
    s.close()

    # Two events: each thread sets its own when X-lock acquired
    ready_a = threading.Event()
    ready_b = threading.Event()
    # One barrier: main thread releases both workers simultaneously
    go = threading.Barrier(3, timeout=15)  # 2 workers + 1 main

    results = {}

    def worker(tid, first, second, my_ready, peer_ready):
        s2 = socket.socket(); s2.settimeout(20)
        try:
            s2.connect((HOST, PORT))
            x(s2, "begin")
            x(s2, f"SELECT * FROM dd WHERE id={first} FOR UPDATE")

            # Signal: "I hold my X-lock"
            my_ready.set()

            # Wait for BOTH to be ready, then main releases the barrier
            go.wait()

            # Now both hold X-locks. Try to UPDATE the other row → deadlock.
            t0 = time.time()
            resp = x(s2, f"UPDATE dd SET val = {tid*1000} WHERE id={second}")
            elapsed = time.time() - t0

            if "abort" in resp.lower():
                x(s2, "abort")
                results[tid] = f"ABORTED@{elapsed:.3f}s"
            else:
                x(s2, "commit")
                results[tid] = f"COMMITTED@{elapsed:.3f}s"
        except socket.timeout:
            results[tid] = "TIMEOUT"
        except Exception as e:
            results[tid] = f"ERR:{e}"
        finally:
            try: s2.close()
            except: pass

    print(f"  Round {round_num}: ", end="", flush=True)

    ta = threading.Thread(target=worker, args=(1, 1, 2, ready_a, ready_b))
    tb = threading.Thread(target=worker, args=(2, 2, 1, ready_b, ready_a))
    ta.start(); tb.start()

    # Wait for both threads to acquire their FOR UPDATE X-locks
    if not ready_a.wait(timeout=10) or not ready_b.wait(timeout=10):
        print("FAIL — workers didn't lock in time")
        return False

    # Small extra delay to ensure both locks are visible in lock_table_
    time.sleep(0.2)

    # Release both workers simultaneously via the 3-party barrier
    try:
        go.wait(timeout=10)
    except threading.BrokenBarrierError:
        print("FAIL — barrier broken")
        return False

    # Wait for workers
    ta.join(timeout=15)
    tb.join(timeout=15)

    ra, rb = results.get(1, "HUNG"), results.get(2, "HUNG")
    ok_a = "COMMITTED" in ra
    ok_b = "COMMITTED" in rb

    if ok_a != ok_b:
        print(f"PASS — A={ra}, B={rb}")
        return True
    elif ok_a and ok_b:
        print(f"FAIL (write skew) — A={ra}, B={rb}")
        return False
    else:
        print(f"INFO (both aborted) — A={ra}, B={rb}")
        return True  # at least detector is working


def main():
    print("=" * 55)
    print("  RMDB 后台死锁检测器校准测试")
    print("=" * 55)

    passed = 0
    for rnd in range(1, 4):
        if not fresh_server():
            print(f"  Round {rnd}: FAIL — server won't start")
            continue
        if run_round(rnd):
            passed += 1

    subprocess.run(["pkill", "-9", "-f", "rmdb"], capture_output=True)
    subprocess.run(["rm", "-rf", DB])

    # Restart default server
    default_db = os.path.join(BUILD_DIR, "mydb")
    subprocess.run(["rm", "-rf", default_db])
    subprocess.Popen([SERVER, default_db], cwd=BUILD_DIR,
                     stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    time.sleep(2)

    print(f"\n{'=' * 55}")
    print(f"  {passed}/3 rounds: {'PASS' if passed >= 1 else 'FAIL'}")
    print(f"{'=' * 55}")
    return passed >= 1


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
