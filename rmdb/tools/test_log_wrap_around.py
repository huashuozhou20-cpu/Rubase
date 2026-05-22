#!/usr/bin/env python3
"""
RMDB Log Buffer Overflow & Wrap-Around Crash Test
===================================================
Tests that the WAL LogManager gracefully handles buffer overflow (forced
flush mid-transaction) without data corruption, deadlock, or log overwrite.

Usage:
  python3 tools/test_log_wrap_around.py [--port PORT] [--skip-build]
"""

import socket
import sys
import os
import time
import subprocess
import shutil
import argparse
import test_harness as H


CONFIG_H = os.path.join(H.PROJECT_DIR, "src", "common", "config.h")
ORIG_LINE = "static constexpr int LOG_BUFFER_SIZE = (1024 * PAGE_SIZE);"
TEST_LINE = "static constexpr int LOG_BUFFER_SIZE = 2048;  // tiny — stress wrap-around"
CONFIG_BAK = CONFIG_H + ".bak"


def _replace_config_line(path, old_prefix, new_line):
    with open(path, 'r') as f:
        lines = f.readlines()
    with open(path, 'w') as f:
        for line in lines:
            if line.strip().startswith(old_prefix):
                f.write(new_line + '\n')
            else:
                f.write(line)


# ---------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--port', type=int, default=H.default_port_for("log_wrap"))
    ap.add_argument('--skip-build', action='store_true')
    args = ap.parse_args()

    PORT = args.port
    DB = "/tmp/rmdb_logwrap"

    print("=" * 60)
    print(f"  RMDB Log Buffer Overflow & Wrap-Around Crash Test  (port {PORT})")
    print("=" * 60)

    H.kill_all_servers()

    # ---- Step 0: Patch config + rebuild ---------------------------------
    if not args.skip_build:
        print("\n[Step 0] Patching LOG_BUFFER_SIZE → 2048 and rebuilding...")
        if not os.path.exists(CONFIG_BAK):
            shutil.copy(CONFIG_H, CONFIG_BAK)
        _replace_config_line(CONFIG_H,
                           "static constexpr int LOG_BUFFER_SIZE", TEST_LINE)
        subprocess.run(["rm", "-rf", H.BUILD_DIR], capture_output=True)
        os.makedirs(H.BUILD_DIR, exist_ok=True)
        ret = subprocess.run(
            ["cmake", "-DCMAKE_BUILD_TYPE=Release", ".."],
            cwd=H.BUILD_DIR, capture_output=True)
        if ret.returncode != 0:
            print("  cmake failed"); return False
        ret = subprocess.run(["make", "-j", str(os.cpu_count() or 4)],
                            cwd=H.BUILD_DIR, capture_output=True)
        if ret.returncode != 0:
            print("  make failed"); return False
        print("  Build complete ✓")
    else:
        print("\n[Step 0] Skipping build (--skip-build)")

    # ---- Phase 1: Setup table and committed baseline --------------------
    print("\n[Phase 1] Setting up table with TEXT column...")
    p = H.start_fresh_server(DB, PORT)
    if not H.wait_for_server(port=PORT):
        print("FAIL: Server won't start")
        return False

    s = H.connect(port=PORT)
    # TEXT = 256 bytes, id INT = 4 bytes → record = 284 bytes (fits RM_MAX_RECORD_SIZE=512)
    H.sql(s, "CREATE TABLE logtest (id INT PRIMARY KEY, payload TEXT)")
    H.sql(s, "INSERT INTO logtest VALUES(1, 'committed_baseline_1')")
    H.sql(s, "INSERT INTO logtest VALUES(2, 'committed_baseline_2')")
    resp = H.sql(s, "SELECT * FROM logtest")
    print(f"  Baseline: {H.count_rows(resp)} rows committed ✓")
    s.close()

    # ---- Phase 2: Large uncommitted transaction -------------------------
    print("\n[Phase 2] Beginning giant uncommitted transaction (500 INSERTs)...")
    t = H.connect(port=PORT, timeout=60)
    H.sql(t, "begin")

    payload = "X" * 200
    kill_at = 300

    for i in range(500):
        row_id = 100 + i
        stmt = f"INSERT INTO logtest VALUES({row_id}, '{payload}_{i}')"
        try:
            H.sql(t, stmt, timeout=5)
            if i < 3 or i % 100 == 0:
                print(f"  Row {i+1}/500 inserted (id={row_id})")
        except Exception as e:
            print(f"  INSERT failed at row {i}: {e}")
            break

        if i == kill_at - 1:
            print(f"\n[Phase 3] kill -9 at row {kill_at} (mid-overflow, no COMMIT)...")
            time.sleep(0.3)
            os.kill(p.pid, 9)
            p.wait(timeout=5)
            print(f"  Server PID {p.pid} killed with SIGKILL")
            try: t.close()
            except Exception: pass
            break

    # ---- Phase 4: Restart and verify ARIES recovery ---------------------
    print("\n[Phase 4] Restart server (WITHOUT deleting DB) — ARIES recovery...")
    time.sleep(1)
    H.kill_all_servers()  # ensure clean port state
    p2 = H.start_server(DB, PORT)
    if not H.wait_for_server(port=PORT, timeout=10):
        print("FAIL: Server won't restart after kill -9")
        return False

    s2 = H.connect(port=PORT)

    # Check committed baselines survived
    resp = H.sql(s2, "SELECT * FROM logtest WHERE id=1 OR id=2 ORDER BY id")
    rows = H.count_rows(resp)
    if rows >= 2:
        print(f"  ✓ Committed baselines survived: {rows} rows")
    else:
        print(f"  ✗ Baselines lost: expected 2, got {rows}")

    # Check uncommitted rows are rolled back
    resp = H.sql(s2, "SELECT * FROM logtest")
    total = H.count_rows(resp)
    if total == 2:
        print(f"  ✓ All uncommitted rows rolled back (total={total})")
    else:
        print(f"  ✗ Expected 2 rows, got {total} — recovery incomplete")

    # Check no residual from the uncommitted txn
    resp = H.sql(s2, "SELECT * FROM logtest WHERE id=150")
    if H.count_rows(resp) == 0:
        print("  ✓ No residual uncommitted row (id=150)")
    else:
        print("  ✗ Found uncommitted row id=150 — undo failed")

    # Check B+tree is consistent
    resp = H.sql(s2, "SELECT * FROM logtest WHERE id >= 1 ORDER BY id")
    idx_rows = H.count_rows(resp)
    if idx_rows == total:
        print(f"  ✓ B+tree index consistent ({idx_rows} rows via index scan)")
    else:
        print(f"  ✗ B+tree inconsistency: table={total}, index={idx_rows}")

    # ---- Phase 5: Post-recovery liveness check --------------------------
    print("\n[Phase 5] Post-recovery liveness — can we still INSERT/UPDATE/DELETE?")
    try:
        H.sql(s2, "INSERT INTO logtest VALUES(999, 'post_recovery_insert')")
        resp = H.sql(s2, "SELECT * FROM logtest WHERE id=999")
        assert "Total record(s): 1" in resp
        print("  ✓ INSERT after recovery OK")

        H.sql(s2, "DELETE FROM logtest WHERE id=999")
        resp = H.sql(s2, "SELECT * FROM logtest WHERE id=999")
        assert "Total record(s): 0" in resp
        print("  ✓ DELETE after recovery OK")
    except Exception as e:
        print(f"  ✗ Post-recovery liveness check failed: {e}")

    H.sql(s2, "DROP TABLE logtest")
    s2.close()

    p2.terminate()
    p2.wait(timeout=5)

    # ---- Restore config --------------------------------------------------
    if not args.skip_build and os.path.exists(CONFIG_BAK):
        shutil.move(CONFIG_BAK, CONFIG_H)
        print(f"\n  Config restored from {CONFIG_BAK}")

    # ---- Verdict ---------------------------------------------------------
    passed = (rows >= 2 and total == 2 and idx_rows == total)
    print(f"\n{'=' * 60}")
    print(f"  WAL buffer overflow: {'PASS' if passed else 'FAIL'}")
    print(f"  Verdict:             {'PASS' if passed else 'FAIL'}")
    print(f"{'=' * 60}")
    return passed


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
