#!/bin/bash
# ============================================================================
# run_scalability_test.sh — EPS/P95/P99 vs thread count (1..64)
# ============================================================================
# Runs sysbench at thread counts 1, 2, 4, 8, 16, 32, 64 and collects
# sustained EPS + P95/P99 latency.  Produces a formatted report and
# identifies the knee point where adding threads stops helping.
# ============================================================================
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
SERVER="$PROJECT_DIR/build/bin/rmdb"
DB_PATH="/tmp/rmdb_scale"
PORT=18801

RED='\033[0;31m'; GREEN='\033[0;32m'; CYAN='\033[0;36m'
YELLOW='\033[1;33m'; BOLD='\033[1m'; NC='\033[0m'

THREAD_COUNTS=(1 2 4 8 16 32 64)
RUN_TIME=10  # seconds per thread level

cleanup_all() {
    pkill -9 rmdb 2>/dev/null || true
    pkill -9 sysbench 2>/dev/null || true
    rm -rf "$DB_PATH"
}
trap cleanup_all EXIT

if [ ! -x "$SERVER" ]; then
    echo -e "${RED}[fatal]${NC} Server not found. Build with Release first."
    exit 1
fi

echo -e "${BOLD}${CYAN}╔══════════════════════════════════════════════════════════╗${NC}"
echo -e "${BOLD}${CYAN}║     RuBase  Thread  Scalability  Benchmark              ║${NC}"
echo -e "${BOLD}${CYAN}╚══════════════════════════════════════════════════════════╝${NC}"
echo ""

declare -A EPS_MAP P95_MAP P99_MAP AVG_MAP

for THREADS in "${THREAD_COUNTS[@]}"; do
    cleanup_all

    echo -e "${YELLOW}[${THREADS} threads]${NC} Starting server..."
    "$SERVER" "$DB_PATH" "$PORT" > /dev/null 2>&1 &
    sleep 2

    export RMDB_HOST="127.0.0.1" RMDB_PORT="$PORT"

    # Prepare fresh data to avoid cumulative effects
    sysbench "$SCRIPT_DIR/sysbench_rmdb.lua" --threads=1 prepare 2>&1 | tail -1

    echo "  Running ${RUN_TIME}s benchmark..."
    LOG=$(timeout $((RUN_TIME + 10)) sysbench \
        "$SCRIPT_DIR/sysbench_rmdb.lua" \
        --threads="$THREADS" \
        --time="$RUN_TIME" \
        --report-interval=5 \
        --rand-type=special \
        run 2>&1) || true

    # Extract metrics
    EPS=$(echo "$LOG" | grep -oP 'events/s \(approx\):\s*\K[0-9.]+' || echo "$LOG" | grep "total number of events\|total time" | awk '/total number/{n=$NF} /total time/{t=$NF} END{if(n&&t) printf "%.1f", n/t}' 2>/dev/null || echo "0")
    P95=$(echo "$LOG" | grep -oP '95th percentile:\s*\K[0-9.]+' || echo "-")
    P99=$(echo "$LOG" | grep -oP '99th percentile:\s*\K[0-9.]+' || echo "-")
    AVG=$(echo "$LOG" | grep -oP 'avg:\s*\K[0-9.]+' || echo "-")

    # Fallback: compute EPS from totals
    if [ "$EPS" = "0" ] || [ -z "$EPS" ]; then
        TOTAL_EVENTS=$(echo "$LOG" | grep "total number of events:" | awk '{print $NF}')
        TOTAL_TIME=$(echo "$LOG" | grep "total time:" | awk '{print $NF}' | sed 's/s//')
        if [ -n "$TOTAL_EVENTS" ] && [ -n "$TOTAL_TIME" ]; then
            EPS=$(awk "BEGIN {printf \"%.1f\", $TOTAL_EVENTS/$TOTAL_TIME}" 2>/dev/null || echo "0")
        fi
    fi

    EPS_MAP[$THREADS]=$EPS
    P95_MAP[$THREADS]=$P95
    P99_MAP[$THREADS]=$P99
    AVG_MAP[$THREADS]=$AVG

    echo -e "  ${GREEN}EPS=${EPS}  P95=${P95}ms  P99=${P99}ms  Avg=${AVG}ms${NC}"
    echo ""

    pkill -9 rmdb 2>/dev/null || true
    sleep 1
done

# ---- Report ----------------------------------------------------------------
echo -e "\n${BOLD}${CYAN}═══ Scalability Report ═══${NC}"
printf "  %-10s %12s %10s %10s %10s\n" "Threads" "EPS" "P95(ms)" "P99(ms)" "Avg(ms)"
printf "  %-10s %12s %10s %10s %10s\n" "-------" "-----------" "--------" "--------" "--------"

BEST_EPS=0; BEST_THREADS=0; KNEE_THREADS=0

for THREADS in "${THREAD_COUNTS[@]}"; do
    EPS_VAL=$(awk "BEGIN {printf \"%.0f\", ${EPS_MAP[$THREADS]}}" 2>/dev/null || echo "0")
    printf "  %-10s %12s %10s %10s %10s\n" \
        "$THREADS" "${EPS_MAP[$THREADS]}" "${P95_MAP[$THREADS]}" "${P99_MAP[$THREADS]}" "${AVG_MAP[$THREADS]}"

    if [ "$EPS_VAL" -gt "$BEST_EPS" ] 2>/dev/null; then
        BEST_EPS=$EPS_VAL
        BEST_THREADS=$THREADS
        KNEE_THREADS=$THREADS
    fi

    # Detect knee: if EPS drops >15% from best, mark the previous as knee
    if [ "$BEST_EPS" -gt 0 ] 2>/dev/null; then
        DROP_PCT=$(awk "BEGIN {printf \"%.0f\", 100*(1 - $EPS_VAL/$BEST_EPS)}" 2>/dev/null || echo "0")
        if [ "${DROP_PCT%.*}" -gt 15 ] 2>/dev/null && [ "$KNEE_THREADS" -eq "$BEST_THREADS" ] 2>/dev/null; then
            KNEE_THREADS=$BEST_THREADS
        fi
    fi
done

echo ""
echo -e "  ${BOLD}Peak throughput:${NC} ${BEST_EPS} EPS at ${BEST_THREADS} threads"
if [ "$KNEE_THREADS" -gt 0 ] 2>/dev/null; then
    echo -e "  ${BOLD}Scalability knee:${NC} ~${KNEE_THREADS} threads (diminishing returns beyond this)"
fi

# Diagnosis
LAST_EPS=$(awk "BEGIN {printf \"%.0f\", ${EPS_MAP[64]}}" 2>/dev/null || echo "0")
if [ "$LAST_EPS" -gt 0 ] 2>/dev/null && [ "$BEST_EPS" -gt 0 ] 2>/dev/null; then
    DEGRADE=$(awk "BEGIN {printf \"%.0f\", 100*(1 - $LAST_EPS/$BEST_EPS)}" 2>/dev/null || echo "0")
    if [ "${DEGRADE%.*}" -gt 30 ] 2>/dev/null; then
        echo -e "  ${RED}${BOLD}Severe degradation:${NC} 64-thread EPS is ${DEGRADE}% below peak."
        echo -e "  Likely bottleneck: root_latch_ serialising all index writes"
        echo -e "  Recommended: implement Crab Latching for concurrent B+tree writes"
    elif [ "${DEGRADE%.*}" -gt 10 ] 2>/dev/null; then
        echo -e "  ${YELLOW}Moderate degradation:${NC} 64-thread EPS is ${DEGRADE}% below peak."
        echo -e "  Acceptable contention under current locking model."
    else
        echo -e "  ${GREEN}Good scalability:${NC} 64-thread EPS within ${DEGRADE}% of peak."
    fi
fi

echo -e "\n${GREEN}${BOLD}Scalability test complete.${NC}"
cleanup_all
