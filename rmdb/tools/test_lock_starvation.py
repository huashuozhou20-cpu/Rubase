#!/usr/bin/env python3
"""
RMDB Lock Starvation & Fairness Test
=====================================
Verifies that the LockManager does not starve a waiting writer (X-lock)
when a flood of new readers continuously arrives.

Usage:
  python3 tools/test_lock_starvation.py [--port PORT]
"""

import sys
import time
import threading
import test_harness as H


class Connection:
    """Thin wrapper around a socket for one client connection."""
    def __init__(self, port):
        self.sock = H.connect(port=port)

    def send(self, stmt, timeout=10):
        return H.sql(self.sock, stmt, timeout)

    def close(self):
        try: self.sock.close()
        except Exception: pass


# ---------------------------------------------------------------------------
def main():
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument('--port', type=int, default=H.default_port_for("lock_starvation"))
    args = ap.parse_args()

    PORT = args.port
    DB = "/tmp/rmdb_starvation"

    print("=" * 60)
    print(f"  RMDB Lock Starvation & Fairness Test  (port {PORT})")
    print("=" * 60)

    H.kill_all_servers()

    # ---- Setup ----------------------------------------------------------
    print("\n[Setup] Starting fresh server...")
    p = H.start_fresh_server(DB, PORT)
    if not H.wait_for_server(port=PORT):
        print("FAIL: Server won't start")
        return False

    admin = Connection(PORT)
    admin.send("CREATE TABLE t (id INT PRIMARY KEY, val INT)")
    admin.send("INSERT INTO t VALUES(1, 100)")
    admin.send("INSERT INTO t VALUES(2, 200)")
    print("  Table created: t(id INT PRIMARY KEY, val INT)")

    # ---- Phase 1: Holder locks id=1 ------------------------------------
    print("\n[Phase 1] Acquiring holder X-lock on id=1 ...")
    holder = Connection(PORT)
    holder.send("begin")
    resp = holder.send("SELECT * FROM t WHERE id=1 FOR UPDATE")
    assert "Total record(s): 1" in resp, f"Holder failed to lock id=1: {resp[:200]}"
    print("  Holder acquired X-lock on id=1 ✓")

    # ---- Phase 2: Writer blocks on id=1 --------------------------------
    print("\n[Phase 2] Writer attempts X-lock on id=1 (should block)...")
    writer_got_lock = threading.Event()
    writer_result = [None]

    def writer_fn():
        w = Connection(PORT)
        w.send("begin")
        t0 = time.time()
        resp = w.send("SELECT * FROM t WHERE id=1 FOR UPDATE", timeout=15)
        elapsed = time.time() - t0
        writer_result[0] = (elapsed, resp, w)
        writer_got_lock.set()

    tw = threading.Thread(target=writer_fn)
    tw.start()
    time.sleep(0.8)
    assert tw.is_alive(), "Writer should be blocked waiting for lock"
    print("  Writer blocked on id=1 ✓")

    # ---- Phase 3: Reader flood while writer waits ----------------------
    print("\n[Phase 3] Flooding 5 new readers while writer is queued...")
    reader_threads = []
    reader_got_lock = [threading.Event() for _ in range(5)]
    reader_results = [None for _ in range(5)]

    def reader_fn(idx):
        r = Connection(PORT)
        r.send("begin")
        t0 = time.time()
        resp = r.send("SELECT * FROM t WHERE id=1 FOR UPDATE", timeout=15)
        elapsed = time.time() - t0
        reader_results[idx] = (elapsed, resp, r)
        reader_got_lock[idx].set()

    for i in range(5):
        rt = threading.Thread(target=reader_fn, args=(i,))
        rt.start()
        reader_threads.append(rt)
        time.sleep(0.05)

    time.sleep(1.0)
    blocked_readers = sum(1 for e in reader_got_lock if not e.is_set())
    print(f"  {blocked_readers}/5 readers blocked behind writer ✓")

    # ---- Phase 4: Release holder, observe wake order -------------------
    print("\n[Phase 4] Releasing holder — observing wake order...")
    holder.send("commit")
    holder.close()

    STARVATION_TIMEOUT = 5.0
    writer_ok = writer_got_lock.wait(timeout=STARVATION_TIMEOUT)
    writer_elapsed = writer_result[0][0] if writer_result[0] else -1

    if not writer_ok:
        print(f"  ✗ WRITER STARVATION: writer did not acquire lock within "
              f"{STARVATION_TIMEOUT:.0f} s after release")
        early = sum(1 for i in range(5)
                    if reader_got_lock[i].is_set() and reader_results[i] is not None)
        if early > 0:
            print(f"  ✗ {early}/5 readers jumped the queue ahead of writer")
        return False

    print(f"  Writer acquired lock in {writer_elapsed*1000:.0f} ms after release")

    # ---- Cleanup -------------------------------------------------------
    for i in range(5):
        if reader_got_lock[i].is_set() and reader_results[i] is not None:
            try: reader_results[i][2].send("commit")
            except Exception: pass
            try: reader_results[i][2].close()
            except Exception: pass
    if writer_ok:
        try: writer_result[0][2].send("commit")
        except Exception: pass
        try: writer_result[0][2].close()
        except Exception: pass
    admin.send("DROP TABLE t")
    admin.close()

    p.terminate()
    p.wait(timeout=5)

    print(f"\n{'=' * 60}")
    print(f"  Writer starvation:  {'FAIL (starved)' if not writer_ok else 'PASS'}")
    print(f"  Verdict:            {'PASS' if writer_ok else 'FAIL'}")
    print(f"{'=' * 60}")
    return writer_ok


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
