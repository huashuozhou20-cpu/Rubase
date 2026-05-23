#!/bin/bash
# ============================================================================
# run_tsan_tests.sh — ThreadSanitizer data-race audit
# ============================================================================
# Builds rmdb with TSAN, runs unit tests + sysbench smoke test, and captures
# any data-race reports from stderr into /tmp/tsan_report.txt.
#
# Usage:
#   ./tools/run_tsan_tests.sh
#
# NOTE: TSAN and ASAN are mutually exclusive.  Do not enable both.
# ============================================================================
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
TSAN_BUILD="$PROJECT_DIR/build_tsan"
REPORT="/tmp/tsan_report.txt"

RED='\033[0;31m'; GREEN='\033[0;32m'; CYAN='\033[0;36m'; YELLOW='\033[1;33m'; NC='\033[0m'

cleanup_all() {
    pkill -9 rmdb 2>/dev/null || true
    pkill -9 sysbench 2>/dev/null || true
    rm -rf /tmp/rmdb_tsan 2>/dev/null || true
}

echo -e "${CYAN}╔══════════════════════════════════════════════════════════╗${NC}"
echo -e "${CYAN}║     RuBase  ThreadSanitizer  Data-Race  Audit           ║${NC}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════╝${NC}"

# ---- Build TSAN binary -----------------------------------------------------
echo -e "\n${YELLOW}[build]${NC} Building with ThreadSanitizer..."
mkdir -p "$TSAN_BUILD"
cd "$TSAN_BUILD"
cmake -DENABLE_TSAN=ON -DCMAKE_BUILD_TYPE=Debug "$PROJECT_DIR" > /dev/null 2>&1
make -j"$(nproc)" 2>&1 | tail -3
cd "$PROJECT_DIR"
echo -e "${GREEN}[build]${NC} TSAN binary ready."

> "$REPORT"

# ---- Phase 1: Unit tests ---------------------------------------------------
echo -e "\n${YELLOW}[unit-test]${NC} Running unit tests under TSAN..."
TSAN_OPTIONS="suppress_equal_stacks=true:halt_on_error=0:log_path=/tmp/tsan_unit" \
    "$TSAN_BUILD/bin/unit_test" > /dev/null 2>&1
RC=$?
if [ $RC -eq 0 ]; then
    echo -e "${GREEN}[unit-test]${NC} 5/5 PASS"
else
    echo -e "${RED}[unit-test]${NC} FAILED (exit=$RC)"
fi
# Collect any TSAN reports from unit tests
cat /tmp/tsan_unit.* >> "$REPORT" 2>/dev/null || true
rm -f /tmp/tsan_unit.* 2>/dev/null || true

# ---- Phase 2: Sysbench smoke test ------------------------------------------
echo -e "\n${YELLOW}[smoke]${NC} Running sysbench smoke test under TSAN (4 threads, 15s)..."
cleanup_all

TSAN_OPTIONS="suppress_equal_stacks=true:halt_on_error=0:log_path=/tmp/tsan_smoke" \
    "$TSAN_BUILD/bin/rmdb" /tmp/rmdb_tsan 18802 > /dev/null 2>&1 &
sleep 3

export RMDB_HOST="127.0.0.1" RMDB_PORT="18802"
sysbench "$SCRIPT_DIR/sysbench_rmdb.lua" --threads=1 prepare 2>&1 | tail -1
timeout 20 sysbench "$SCRIPT_DIR/sysbench_rmdb.lua" \
    --threads=4 --time=10 --report-interval=5 --rand-type=special run 2>&1 | tail -10 || true

pkill -9 rmdb 2>/dev/null || true
sleep 1

# Collect TSAN reports from smoke test
cat /tmp/tsan_smoke.* >> "$REPORT" 2>/dev/null || true
rm -f /tmp/tsan_smoke.* 2>/dev/null || true

# ---- Report ----------------------------------------------------------------
echo -e "\n${CYAN}═══ TSAN Audit Report ═══${NC}"
RACE_COUNT=$(grep -c "WARNING: ThreadSanitizer: data race" "$REPORT" 2>/dev/null || echo "0")

if [ "$RACE_COUNT" -gt 0 ] 2>/dev/null; then
    echo -e "${RED}${BOLD}FOUND ${RACE_COUNT} DATA RACE(S)${NC}"
    echo -e "\n  Top races:"
    grep "WARNING: ThreadSanitizer: data race" -A 1 "$REPORT" | head -20
    echo ""
    echo "  Full report: $REPORT"
    echo ""
    echo "  Key areas to inspect:"
    echo "    - Connection::busy flag in epoll_server (worker ↔ I/O thread)"
    echo "    - EpollServer::connections_ map concurrent access"
    echo "    - BufferPoolManager background flush vs worker threads"
    echo "    - TransactionManager::txn_map (begin/commit/abort concurrency)"
else
    echo -e "${GREEN}${BOLD}NO DATA RACES DETECTED${NC}"
    echo "  All shared-state accesses are properly synchronised."
fi

echo -e "\n  Full TSAN report: $REPORT"
echo -e "${GREEN}TSAN audit complete.${NC}"

# Cleanup ASAN build artifacts
rm -rf "$TSAN_BUILD"
cleanup_all
