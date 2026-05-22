#!/bin/bash
# ============================================================================
# RuBase Crash Diagnostic — ASAN + sysbench automated root-cause capture
# ============================================================================
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_DIR/build"
SERVER="$BUILD_DIR/bin/rmdb"
LUA_SCRIPT="$SCRIPT_DIR/sysbench_rmdb.lua"

DB_PATH="/tmp/rmdb_asan_diag"
PORT=18770
SERVER_LOG="$PROJECT_DIR/rmdb_asan.log"
ASAN_OPTIONS="${ASAN_OPTIONS:-halt_on_error=0:log_path=$PROJECT_DIR/rmdb_asan}"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

cleanup() {
    echo -e "${CYAN}[cleanup]${NC} Stopping server & cleaning..."
    pkill -9 rmdb 2>/dev/null || true
    sleep 0.5
}
trap cleanup EXIT

# ---- Rebuild with ASAN ---------------------------------------------------
echo -e "${CYAN}[build]${NC} Rebuilding with AddressSanitizer enabled..."
cleanup
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"

cd "$BUILD_DIR"
cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_ASAN=ON .. 2>&1 | tail -3
make -j"$(nproc)" 2>&1 | tail -5
cd "$PROJECT_DIR"

echo -e "${GREEN}[build]${NC} ASAN build complete."

# ---- Launch server under ASAN --------------------------------------------
echo -e "\n${CYAN}[launch]${NC} Starting RuBase under ASAN surveillance..."
rm -f "$SERVER_LOG" "$PROJECT_DIR"/rmdb_asan.*

export ASAN_OPTIONS
rm -rf "$DB_PATH"
"$SERVER" "$DB_PATH" "$PORT" > "$SERVER_LOG" 2>&1 &
SERVER_PID=$!
echo "  PID: $SERVER_PID  Log: $SERVER_LOG"

# Wait for server readiness
for i in $(seq 1 30); do
    if python3 -c "
import socket, sys
try:
    s = socket.socket(); s.settimeout(1)
    s.connect(('127.0.0.1', $PORT)); s.close()
    sys.exit(0)
except: sys.exit(1)
" 2>/dev/null; then
        echo -e "  ${GREEN}Server ready.${NC}"
        break
    fi
    if ! kill -0 "$SERVER_PID" 2>/dev/null; then
        echo -e "  ${RED}Server died during startup!${NC}"
        break
    fi
    sleep 0.3
done

# ---- Prepare sysbench table ----------------------------------------------
echo -e "\n${CYAN}[prepare]${NC} Creating sbtest table..."
export RMDB_HOST="127.0.0.1"
export RMDB_PORT="$PORT"

if kill -0 "$SERVER_PID" 2>/dev/null; then
    sysbench "$LUA_SCRIPT" --threads=1 prepare > /dev/null 2>&1 || true
    echo "  Done."
else
    echo -e "  ${RED}Server not running — checking ASAN log...${NC}"
fi

# ---- Run sysbench stress -------------------------------------------------
echo -e "\n${CYAN}[stress]${NC} Launching sysbench OLTP bombardment (8 threads, 20s)..."
echo ""

set +e
sysbench "$LUA_SCRIPT" \
    --threads=8 \
    --time=20 \
    --report-interval=5 \
    run 2>&1
SYSBENCH_RC=$?
set -e

sleep 1

# ---- Diagnose ------------------------------------------------------------
echo ""
echo "============================================================================"

ALIVE=$(kill -0 "$SERVER_PID" 2>/dev/null && echo "yes" || echo "no")

if [ "$ALIVE" = "no" ]; then
    echo -e "${RED}🚨  SERVER CRASH DETECTED  🚨${NC}"
    echo ""

    # ---- Parse ASAN log --------------------------------------------------
    ASAN_FILES=$(ls "$PROJECT_DIR"/rmdb_asan.* 2>/dev/null || true)
    if [ -n "$ASAN_FILES" ]; then
        echo -e "${YELLOW}--- ASAN Report ----------------------------------------------${NC}"
        for f in $ASAN_FILES; do
            echo -e "${CYAN}File: $f${NC}"
            if grep -q "ERROR: AddressSanitizer" "$f" 2>/dev/null; then
                echo -e "${RED}"
                grep -E "ERROR: AddressSanitizer|READ of size|WRITE of size|heap-use-after-free|heap-buffer-overflow|stack-buffer-overflow|double-free|use-after-poison|allocated by|freed by|SUMMARY:" "$f" | head -30
                echo -e "${NC}"
                echo ""
                echo -e "${YELLOW}--- Full stack trace -----------------------------------------${NC}"
                grep -A 40 "ERROR: AddressSanitizer" "$f" | head -50
            else
                head -20 "$f"
            fi
            echo ""
        done
    else
        echo -e "${YELLOW}No ASAN log file found — checking stderr log...${NC}"
        echo ""
    fi

    # ---- Check server stderr log -----------------------------------------
    if [ -f "$SERVER_LOG" ]; then
        echo -e "${YELLOW}--- Server stderr (last 40 lines) ----------------------------${NC}"
        tail -40 "$SERVER_LOG"
        echo ""

        # Extract key signals
        echo -e "${YELLOW}--- Signal / abort summary ----------------------------------${NC}"
        grep -iE "signal|segfault|abort|assert|SIGABRT|SIGSEGV|backtrace|AddressSanitizer|heap-use|double-free|buffer-overflow|stack-buffer" "$SERVER_LOG" | head -20 || echo "  (no diagnostic patterns found)"
    fi

    echo ""
    echo -e "${RED}============================================================================${NC}"
    echo -e "${RED}  DIAGNOSIS: Server crashed under concurrent OLTP load${NC}"
    echo -e "${RED}  Sysbench exit code: $SYSBENCH_RC${NC}"
    echo -e "${RED}============================================================================${NC}"
    exit 1

elif [ "$SYSBENCH_RC" -ne 0 ]; then
    echo -e "${YELLOW}⚠  Sysbench exited non-zero (rc=$SYSBENCH_RC) but server is still alive.${NC}"
    echo "  Check $SERVER_LOG for details."
    kill -9 "$SERVER_PID" 2>/dev/null || true
    exit 1

else
    echo -e "${GREEN}✓  No crash detected — server survived 8-thread OLTP bombardment.${NC}"
    echo "  Try increasing thread count for deeper stress."
    kill -9 "$SERVER_PID" 2>/dev/null || true
    exit 0
fi
