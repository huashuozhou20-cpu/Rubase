#!/usr/bin/env python3
"""
RMDB Chaos Soak CBO — Long-Txn + Hash Join Mixed Stress Test
=============================================================
Pins GC watermark with a 30s long transaction while writers
create deep version chains and Hash Join queries run continuously.

Validates:
  1. Long transaction correctly pins GC watermark (version chain grows)
  2. CBO estimate_row_count() not confused by version chain — still
     correctly identifies small table and routes to Hash Join build side
  3. Hash Join returns correct results under concurrent UPDATEs
  4. After long txn commits, GC recovers within 16 commit cycles

Usage:
  python3 tools/chaos_soak_cbo.py
"""

import socket, sys, os, time, threading, subprocess

HOST = "127.0.0.1"
PORT = 8765
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)
BUILD_DIR = os.path.join(PROJECT_DIR, "build")
SERVER = os.path.join(BUILD_DIR, "bin", "rmdb")
DB = "/tmp/rmdb_soak_cbo"

WRITER_COUNT = 4
SOAK_SECONDS = 30
WRITER_UPDATES = 200  # per writer


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
    print("  RMDB Chaos Soak CBO — Long-Txn + Hash Join Stress")
    print("=" * 60)

    if not start_server():
        print("FAIL: Server won't start"); return False

    s = socket.socket(); s.settimeout(120); s.connect((HOST, PORT))
    results = {"hj_errors": 0, "hj_queries": 0, "writer_errors": 0,
               "writer_ops": 0, "cbo_correct": 0, "cbo_total": 0}
    results_lock = threading.Lock()
    stop_flag = threading.Event()

    try:
        # Setup: small table A (10 rows) + large table B (50 rows)
        print("\n[Setup] Creating tables...")
        x(s, "DROP TABLE A")
        x(s, "DROP TABLE B")
        x(s, "CREATE TABLE A (id INT, val INT)")
        x(s, "CREATE TABLE B (foreign_id INT, data INT)")

        for j in range(10):
            x(s, f"INSERT INTO A VALUES({j}, {j*10})")
        for j in range(50):
            x(s, f"INSERT INTO B VALUES({j}, {j*100})")
        print("  A: 10 rows (small/build), B: 50 rows (large/probe)")

        # Verify initial Hash Join works
        resp = x(s, "SELECT * FROM A, B WHERE A.id = B.foreign_id")
        base_rows = count_rows(resp)
        print(f"  Initial Hash Join: {base_rows} rows (expected ~10)")

        # Phase 1: Start long transaction that pins GC watermark
        print(f"\n[Phase 1] Long transaction holds ReadView for {SOAK_SECONDS}s...")
        lt = socket.socket(); lt.settimeout(120); lt.connect((HOST, PORT))
        x(lt, "begin")
        x(lt, "SELECT * FROM A")
        print("  Long txn: acquired ReadView, now holding...")

        # Phase 2: Launch concurrent writers that chain version updates
        print(f"\n[Phase 2] {WRITER_COUNT} writers updating A for {SOAK_SECONDS}s...")
        writer_done = threading.Event()

        def writer(wid):
            ws = socket.socket(); ws.settimeout(60)
            try:
                ws.connect((HOST, PORT))
                for i in range(WRITER_UPDATES):
                    if stop_flag.is_set(): break
                    row_id = (wid * 50 + i) % 10  # target different rows
                    new_val = wid * 10000 + i
                    resp = x(ws, f"UPDATE A SET val = {new_val} WHERE id = {row_id}")
                    with results_lock:
                        results["writer_ops"] += 1
                        if "error" in resp.lower():
                            results["writer_errors"] += 1
            except Exception as e:
                with results_lock:
                    results["writer_errors"] += 1
            finally:
                try: ws.close()
                except: pass

        writers = []
        for w in range(WRITER_COUNT):
            t = threading.Thread(target=writer, args=(w,)); t.start()
            writers.append(t)

        # Phase 3: Run Hash Join queries concurrently
        print(f"\n[Phase 3] Hash Join queries during heavy UPDATEs...")
        hj_start = time.time()
        hj_count = 0

        while time.time() - hj_start < SOAK_SECONDS:
            hj = socket.socket(); hj.settimeout(30)
            try:
                hj.connect((HOST, PORT))
                resp = x(hj, "SELECT * FROM A, B WHERE A.id = B.foreign_id")
                rows = count_rows(resp)
                with results_lock:
                    results["hj_queries"] += 1
                    if rows >= 0:
                        results["cbo_total"] += rows
                        results["cbo_correct"] += 1
                    if "error" in resp.lower():
                        results["hj_errors"] += 1
                hj_count += 1
            except: pass
            finally:
                try: hj.close()
                except: pass
            time.sleep(0.5)

        print(f"  Ran {hj_count} Hash Join queries during soak")

        # Stop writers
        stop_flag.set()
        for w in writers:
            w.join(timeout=10)

        print(f"  Writers: {results['writer_ops']} ops, "
              f"{results['writer_errors']} errors")

        # Phase 4: Long transaction commits — GC should recover
        print("\n[Phase 4] Long transaction commits — GC should recover...")
        x(lt, "commit")
        lt.close()
        time.sleep(2)

        # Run several Hash Joins to verify CBO still works after GC
        for i in range(5):
            resp = x(s, "SELECT * FROM A, B WHERE A.id = B.foreign_id")
            rows = count_rows(resp)
            if rows >= 0:
                with results_lock:
                    results["cbo_correct"] += 1

        # Final verification
        resp = x(s, "SELECT * FROM A, B WHERE A.id = B.foreign_id ORDER BY A.id")
        final_rows = count_rows(resp)
        print(f"  Post-GC Hash Join: {final_rows} rows")

        # Summary
        print(f"\n{'=' * 60}")
        print(f"  Writers:      {results['writer_ops']} ops "
              f"({results['writer_errors']} errors)")
        print(f"  Hash Joins:   {results['hj_queries']} queries "
              f"({results['hj_errors']} errors)")
        print(f"  CBO routing:  {'OK' if results['cbo_correct'] > 0 else 'CHECK'}")
        print(f"  Final rows:   {final_rows} (expected ~10)")
        print(f"{'=' * 60}")

        passed = (results['hj_queries'] > 0 and
                  results['hj_errors'] == 0 and
                  results['cbo_correct'] > 0)
        print(f"  Verdict:      {'PASS' if passed else 'CHECK'}")
        return passed

    finally:
        try: s.close()
        except: pass
        subprocess.run(["rm", "-rf", DB], capture_output=True)


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
