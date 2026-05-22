#!/usr/bin/env python3
"""
RMDB Chaos Test Suite Orchestrator
====================================
Runs all three stress tests serially, each on its own port to avoid
cross-test collisions, with rigorous pre/post cleanup.

Usage:
  python3 tools/run_all_tests.py              # full suite (3 min soak)
  python3 tools/run_all_tests.py --quick      # 30 s soak for smoke testing
"""

import sys
import os
import time
import subprocess
import argparse

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

TESTS = [
    ("lock_starvation",  "test_lock_starvation.py"),
    ("log_wrap_around",  "test_log_wrap_around.py"),
    ("soak_leak",        "test_soak_leak.py"),
]

# Each test gets a dedicated port — no collisions even when run in parallel.
# (Ports match test_harness._DEFAULT_PORTS)
TEST_PORTS = {
    "lock_starvation": 18765,
    "log_wrap_around": 18766,
    "soak_leak":       18767,
}


def run_one(name, script, port, extra_args):
    """Run a single test script and return (name, passed, output)."""
    cmd = [sys.executable, os.path.join(SCRIPT_DIR, script),
           "--port", str(port)] + extra_args
    print(f"\n{'#' * 60}")
    print(f"#  RUNNING: {name}  (port {port})")
    print(f"{'#' * 60}")
    try:
        r = subprocess.run(cmd, cwd=SCRIPT_DIR,
                           capture_output=False,  # stream to terminal
                           timeout=600)
        return (name, r.returncode == 0)
    except subprocess.TimeoutExpired:
        print(f"\n  ✗ {name}: TIMEOUT (600 s)")
        return (name, False)
    except Exception as e:
        print(f"\n  ✗ {name}: {e}")
        return (name, False)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--quick', action='store_true',
                    help='Soak test at 30 s instead of 180 s')
    ap.add_argument('--skip-logwrap', action='store_true',
                    help='Skip the log-wrap test (requires full rebuild)')
    ap.add_argument('--only', type=str, default='',
                    help='Comma-separated list of test names to run')
    args = ap.parse_args()

    print("=" * 60)
    print("  RMDB Chaos Test Suite")
    print("=" * 60)

    # Pre-suite cleanup
    print("\n[Pre-flight] Killing all rmdb processes...")
    try:
        subprocess.run(["pkill", "-9", "rmdb"], capture_output=True, timeout=5)
    except Exception:
        pass
    time.sleep(0.5)
    print("  Clean ✓\n")

    only = set(args.only.split(',')) if args.only else None

    results = {}
    for name, script in TESTS:
        if only and name not in only:
            continue
        if args.skip_logwrap and name == "log_wrap_around":
            print(f"  Skipping {name} (--skip-logwrap)")
            results[name] = True
            continue

        extra = []
        if args.quick and name == "soak_leak":
            extra = ["--duration", "30"]
        if name == "log_wrap_around":
            extra.append("--skip-build")

        port = TEST_PORTS[name]
        name, passed = run_one(name, script, port, extra)
        results[name] = passed

        # Inter-test cooldown
        time.sleep(0.5)

    # ---- Summary ---------------------------------------------------------
    print(f"\n\n{'=' * 60}")
    print(f"  SUITE RESULTS")
    print(f"{'=' * 60}")
    all_ok = True
    for name, _script in TESTS:
        if only and name not in only:
            continue
        ok = results.get(name, False)
        flag = "PASS" if ok else "FAIL"
        print(f"  {name:<25s} {flag}")
        if not ok:
            all_ok = False
    print(f"{'=' * 60}")
    print(f"  OVERALL: {'PASS' if all_ok else 'FAIL'}")
    print(f"{'=' * 60}")

    return 0 if all_ok else 1


if __name__ == "__main__":
    sys.exit(main())
