#!/bin/bash
# ============================================================================
# run_soak_test.sh — long-duration stability test with memory & latency probes
# ============================================================================
# Usage:  ./tools/run_soak_test.sh [duration_sec=300]
#
#  What it does:
#   1. Runs sysbench for the specified duration (default 5 min).
#   2. Every 5 s samples VmRSS to detect memory leaks in SimpleArena / BPM.
#   3. Extracts P95 / P99 / P99.9 latencies from sysbench histogram output.
#   4. Prints a final stability report with memory trend and latency summary.
# ============================================================================
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_DIR/build"
SERVER="$BUILD_DIR/bin/rmdb"
DB_PATH="/tmp/rmdb_soak"
PORT=18772
DURATION="${1:-300}"   # default 5 minutes

RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
YELLOW='\033[1;33m'
NC='\033[0m'
BOLD='\033[1m'

MEM_LOG="/tmp/rmdb_vmrss.log"
SYSBENCH_LOG="/tmp/rmdb_sysbench_soak.log"

cleanup_all() {
    echo -e "\n${CYAN}[cleanup]${NC} Stopping all processes..."
    pkill -9 rmdb      2>/dev/null || true
    pkill -9 sysbench  2>/dev/null || true
    rm -rf "$DB_PATH"
}
trap cleanup_all EXIT

# ---- Build check -----------------------------------------------------------
if [ ! -x "$SERVER" ]; then
    echo -e "${CYAN}[build]${NC} Building Release binary..."
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    cmake -DCMAKE_BUILD_TYPE=Release .. > /dev/null 2>&1
    make -j"$(nproc)" > /dev/null 2>&1
    cd "$PROJECT_DIR"
fi

# ---- Launch -----------------------------------------------------------------
echo -e "${BOLD}${CYAN}╔══════════════════════════════════════════════════════════╗${NC}"
echo -e "${BOLD}${CYAN}║     RuBase  Long-Soak  Stability  &  Latency  Test      ║${NC}"
echo -e "${BOLD}${CYAN}╚══════════════════════════════════════════════════════════╝${NC}"
echo -e "  Duration: ${BOLD}${DURATION}s${NC}   Threads: ${BOLD}4${NC}"
echo ""

cleanup_all
echo -e "${CYAN}[launch]${NC} Starting rmdb on port $PORT ..."
"$SERVER" "$DB_PATH" "$PORT" > /dev/null 2>&1 &
SERVER_PID=$!

for i in $(seq 1 30); do
    if python3 -c "
import socket, sys
try:
    s=socket.socket(); s.settimeout(1); s.connect(('127.0.0.1',$PORT)); s.close()
    sys.exit(0)
except: sys.exit(1)
" 2>/dev/null; then
        echo -e "${GREEN}[launch]${NC} Server ready (PID $SERVER_PID)."
        break
    fi
    sleep 0.5
done

# ---- Prepare ---------------------------------------------------------------
echo -e "${CYAN}[prepare]${NC} Creating sbtest table (10 000 rows for soak)..."
export RMDB_HOST="127.0.0.1"
export RMDB_PORT="$PORT"

sysbench "$SCRIPT_DIR/sysbench_rmdb.lua" --threads=1 prepare 2>&1 | tail -1

# ---- Memory monitor (background) -------------------------------------------
> "$MEM_LOG"
echo -e "${CYAN}[memlog]${NC} Starting VmRSS sampler every 5 s → ${MEM_LOG}"

(
    START_TS=$(date +%s)
    while true; do
        NOW=$(date +%s)
        ELAPSED=$((NOW - START_TS))
        if [ "$ELAPSED" -ge "$DURATION" ]; then break; fi
        if [ -f /proc/$SERVER_PID/status ]; then
            RSS_KB=$(grep VmRSS /proc/$SERVER_PID/status 2>/dev/null | awk '{print $2}')
            echo "$ELAPSED $RSS_KB" >> "$MEM_LOG"
        fi
        sleep 5
    done
) &
MEM_PID=$!

# ---- Run -------------------------------------------------------------------
echo -e "\n${CYAN}[run]${NC} Starting sysbench (4 threads, ${DURATION}s) with histogram..."
echo ""

sysbench "$SCRIPT_DIR/sysbench_rmdb.lua" \
    --threads=4 \
    --time="$DURATION" \
    --report-interval=5 \
    --percentile=99 \
    --histogram=on \
    --rand-type=special \
    run 2>&1 | tee "$SYSBENCH_LOG"

# ---- Wait for memory monitor -----------------------------------------------
wait "$MEM_PID" 2>/dev/null || true

# ---- Report: Memory --------------------------------------------------------
echo -e "\n${BOLD}${YELLOW}═══ Memory Stability Report (VmRSS) ═══${NC}"

if [ -s "$MEM_LOG" ]; then
    SAMPLES=$(wc -l < "$MEM_LOG")
    FIRST_RSS=$(head -1 "$MEM_LOG" | awk '{print $2}')
    LAST_RSS=$(tail -1 "$MEM_LOG" | awk '{print $2}')
    MIN_RSS=$(awk '{print $2}' "$MEM_LOG" | sort -n | head -1)
    MAX_RSS=$(awk '{print $2}' "$MEM_LOG" | sort -n | tail -1)

    if [ "$FIRST_RSS" -gt 0 ] 2>/dev/null; then
        DELTA=$((LAST_RSS - FIRST_RSS))
        DELTA_MB=$(awk "BEGIN {printf \"%.1f\", $DELTA/1024}")
        FIRST_MB=$(awk "BEGIN {printf \"%.1f\", $FIRST_RSS/1024}")
        LAST_MB=$(awk "BEGIN {printf \"%.1f\", $LAST_RSS/1024}")
    else
        DELTA=0; DELTA_MB="0.0"; FIRST_MB="?"; LAST_MB="?"
    fi

    echo "  Samples:       $SAMPLES  (every 5 s)"
    echo "  VmRSS start:   ${FIRST_MB} MB"
    echo "  VmRSS end:     ${LAST_MB} MB"
    echo "  VmRSS min:     $(awk "BEGIN {printf \"%.1f\", $MIN_RSS/1024}") MB"
    echo "  VmRSS max:     $(awk "BEGIN {printf \"%.1f\", $MAX_RSS/1024}") MB"
    echo "  Delta:         ${DELTA_MB} MB"

    # Leak verdict
    if [ "${DELTA#-}" -gt 51200 ] 2>/dev/null; then   # > 50 MB
        echo -e "  ${RED}${BOLD}Verdict: POSSIBLE LEAK${NC} (Δ > 50 MB)"
    elif [ "${DELTA#-}" -gt 10240 ] 2>/dev/null; then  # > 10 MB
        echo -e "  ${YELLOW}${BOLD}Verdict: MONITOR${NC} (Δ > 10 MB)"
    else
        echo -e "  ${GREEN}${BOLD}Verdict: STABLE${NC} (Δ < 10 MB)"
    fi
else
    echo -e "  ${RED}No memory samples collected (server may have exited early).${NC}"
fi

# ---- Report: Latency percentile extraction ---------------------------------
echo -e "\n${BOLD}${YELLOW}═══ High-Resolution Latency Percentiles ═══${NC}"

# sysbench --histogram=on outputs a latency histogram at the end.
# Extract percentiles by parsing the cumulative distribution.
if [ -s "$SYSBENCH_LOG" ]; then
    # First, print sysbench's own summary lines
    grep -E "95th|99th|percentile|thds:|transactions|total time|total number|events" \
        "$SYSBENCH_LOG" 2>/dev/null | tail -20 || true

    echo ""
    echo -e "${CYAN}[histogram]${NC} Parsing sysbench latency histogram..."

    # sysbench histogram format (after the run):
    #   [bucket_start_ms]  count
    # We compute approximate percentiles from the cumulative distribution.
    python3 << 'PYEOF' "$SYSBENCH_LOG" 2>/dev/null || echo "(histogram parse skipped — Python unavailable)"
import sys, re

log_file = sys.argv[1]
buckets = []
total = 0

with open(log_file) as f:
    in_hist = False
    for line in f:
        line = line.strip()
        if 'Latency histogram' in line:
            in_hist = True
            continue
        if in_hist:
            m = re.match(r'^\s*\[?\s*([0-9.]+)\s*\]?\s+(\d+)', line)
            if m:
                val = float(m.group(1))
                cnt = int(m.group(2))
                buckets.append((val, cnt))
                total += cnt
            elif buckets and not line:
                break  # empty line after histogram → done

if not buckets or total == 0:
    sys.exit(0)

# Compute cumulative and report target percentiles
targets = [50.0, 95.0, 99.0, 99.9]
cum = 0
results = {}
ti = 0
for val, cnt in buckets:
    cum += cnt
    pct = cum * 100.0 / total
    while ti < len(targets) and pct >= targets[ti]:
        results[targets[ti]] = val
        ti += 1

print("  Cumulative event count: %d" % total)
for t in targets:
    if t in results:
        print("  P%-5s  %8.3f ms" % (str(t), results[t]))
    else:
        print("  P%-5s  (not reached)" % str(t))
PYEOF
else
    echo "  (sysbench log missing — no histogram data)"
fi

# ---- Per-interval EPS summary ----------------------------------------------
echo -e "\n${BOLD}${YELLOW}═══ Throughput Stability (per 5 s interval) ═══${NC}"
grep "eps:" "$SYSBENCH_LOG" 2>/dev/null | head -20 || echo "(no interval data)"

echo -e "\n${GREEN}${BOLD}Soak test complete.${NC}"
echo "  Memory log:  $MEM_LOG"
echo "  Full log:    $SYSBENCH_LOG"
