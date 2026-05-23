#!/bin/bash
# ============================================================================
# run_profiling.sh — one-click FlameGraph profiling (built-in sampler)
# ============================================================================
# Usage:  ./tools/run_profiling.sh [duration_sec=15]
#
#  Uses rmdb's built-in timer-based sampler (100 Hz, no external tools needed).
#  Post-processes raw backtraces via addr2line and renders an interactive
#  FlameGraph SVG in the project root.
# ============================================================================
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_DIR/build"
SERVER="$BUILD_DIR/bin/rmdb"
DB_PATH="/tmp/rmdb_profiling"
PORT=18771
DURATION="${1:-15}"

RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
YELLOW='\033[1;33m'
NC='\033[0m'
BOLD='\033[1m'

SAMPLE_FILE="/tmp/rmdb_samples.bin"
OUTPUT_SVG="$PROJECT_DIR/database_perf.svg"

cleanup_all() {
    echo -e "\n${CYAN}[cleanup]${NC} Stopping all processes..."
    pkill -9 rmdb      2>/dev/null || true
    pkill -9 sysbench  2>/dev/null || true
    rm -rf "$DB_PATH" "$SAMPLE_FILE" 2>/dev/null || true
}
trap cleanup_all EXIT

# ---- Banner ----------------------------------------------------------------
echo -e "${BOLD}${CYAN}╔══════════════════════════════════════════════════════════╗${NC}"
echo -e "${BOLD}${CYAN}║  RuBase  FlameGraph  Profiling  (built-in  sampler)     ║${NC}"
echo -e "${BOLD}${CYAN}╚══════════════════════════════════════════════════════════╝${NC}"
echo ""

# ---- Build (if needed) -----------------------------------------------------
if [ ! -x "$SERVER" ]; then
    echo -e "${CYAN}[build]${NC} Building Release binary..."
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    cmake -DCMAKE_BUILD_TYPE=Release .. > /dev/null 2>&1
    make -j"$(nproc)" > /dev/null 2>&1
    cd "$PROJECT_DIR"
fi

# ---- Check addr2line -------------------------------------------------------
if ! command -v addr2line &>/dev/null; then
    echo -e "${RED}[fatal]${NC} 'addr2line' not found (part of binutils)."
    exit 1
fi

# ---- Launch server ---------------------------------------------------------
cleanup_all
echo -e "${CYAN}[launch]${NC} Starting rmdb with built-in sampler..."
echo -e "  Samples → ${YELLOW}$SAMPLE_FILE${NC}"
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

sleep 1  # let sampler thread start

# ---- Prepare ---------------------------------------------------------------
echo -e "${CYAN}[prepare]${NC} Creating sbtest table ..."
export RMDB_HOST="127.0.0.1"
export RMDB_PORT="$PORT"

sysbench "$SCRIPT_DIR/sysbench_rmdb.lua" --threads=1 prepare 2>&1 | tail -1

# ---- Run benchmark ----------------------------------------------------------
SAMPLING_SEC=$((DURATION > 15 ? 15 : DURATION))
echo -e "\n${CYAN}[bench]${NC} Running sysbench (4 threads, ${DURATION}s)..."
echo -e "  Sampling for ${SAMPLING_SEC}s at 100 Hz..."

sysbench "$SCRIPT_DIR/sysbench_rmdb.lua" \
    --threads=4 \
    --time="$DURATION" \
    --report-interval=5 \
    --rand-type=special \
    run 2>&1 | tail -20

# ---- Stop server (which stops the sampler) ---------------------------------
echo -e "\n${CYAN}[stop]${NC} Shutting down server (sampler stops)..."
kill -INT "$SERVER_PID" 2>/dev/null || true
sleep 2
pkill -9 rmdb 2>/dev/null || true

# ---- Check we have samples -------------------------------------------------
SAMPLE_SIZE=$(stat -c%s "$SAMPLE_FILE" 2>/dev/null || echo "0")
echo -e "  Raw sample size: ${SAMPLE_SIZE} bytes"

if [ "$SAMPLE_SIZE" -lt 40 ]; then
    echo -e "${YELLOW}[warn]${NC} Too few samples captured (${SAMPLE_SIZE} bytes)."
    echo "  Make sure the benchmark ran long enough and the server didn't crash."
    exit 0
fi

# ---- Resolve symbols → folded format ---------------------------------------
echo -e "\n${CYAN}[resolve]${NC} Resolving addresses → function names (addr2line)..."
chmod +x "$SCRIPT_DIR/fold_stacks.py" 2>/dev/null || true
python3 "$SCRIPT_DIR/fold_stacks.py" "$SAMPLE_FILE" "$SERVER" > /tmp/rmdb_folded.txt 2>/tmp/rmdb_fold.log

FOLDED_LINES=$(wc -l < /tmp/rmdb_folded.txt 2>/dev/null || echo "0")
echo -e "  Folded stacks: ${FOLDED_LINES} unique"

# ---- Render SVG ------------------------------------------------------------
FLAMEGRAPH_DIR="/tmp/FlameGraph"
if [ ! -d "$FLAMEGRAPH_DIR" ]; then
    echo -e "${CYAN}[flamegraph]${NC} Cloning FlameGraph tools..."
    git clone --depth 1 https://github.com/brendangregg/FlameGraph.git "$FLAMEGRAPH_DIR" 2>/dev/null || true
fi

if [ -d "$FLAMEGRAPH_DIR" ] && [ "$FOLDED_LINES" -gt 0 ]; then
    echo -e "${CYAN}[flamegraph]${NC} Rendering SVG..."
    "$FLAMEGRAPH_DIR/flamegraph.pl" \
        --title "RuBase CPU Profile (sysbench 4-thread, ${SAMPLING_SEC}s)" \
        --countname "samples" \
        --width 1400 \
        < /tmp/rmdb_folded.txt \
        > "$OUTPUT_SVG" 2>/dev/null && \
    echo -e "${GREEN}${BOLD}[flamegraph]${NC} SVG written → ${BOLD}$OUTPUT_SVG${NC}" || \
    echo -e "${YELLOW}[flamegraph]${NC} flamegraph.pl failed."
else
    echo -e "${YELLOW}[flamegraph]${NC} Skipping SVG (FlameGraph tools not found or no samples)."
fi

# ---- Top-5 CPU functions from folded samples -------------------------------
echo -e "\n${BOLD}${YELLOW}═══ Top-5 CPU Functions (by sample count) ═══${NC}"
if [ -f /tmp/rmdb_folded.txt ]; then
    python3 << 'PYEOF' 2>/dev/null || true
import sys
funcs = {}
with open("/tmp/rmdb_folded.txt") as f:
    for line in f:
        if not line.strip(): continue
        parts = line.rsplit(" ", 1)
        if len(parts) != 2: continue
        stack, count = parts
        count = int(count)
        for func in stack.split(";"):
            func = func.strip()
            if not func or func == "(empty)" or "0x" in func: continue
            # Keep only the leaf-level meaningful functions
            short = func.split("(")[0].strip() if "(" in func else func
            funcs[short] = funcs.get(short, 0) + count

for i, (func, cnt) in enumerate(sorted(funcs.items(), key=lambda x: -x[1])[:5]):
    print(f"  {i+1}. {func:60s} {cnt:6d} samples")
PYEOF
fi

echo -e "\n${GREEN}${BOLD}Done.${NC}  FlameGraph → ${BOLD}$OUTPUT_SVG${NC}"
echo -e "  Raw samples:  $SAMPLE_FILE"
echo -e "  Folded stacks: /tmp/rmdb_folded.txt"
