#!/bin/bash
# ============================================================================
# RuBase sysbench OLTP benchmark launcher
# ============================================================================
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_DIR/build"
SERVER="$BUILD_DIR/bin/rmdb"
DB_PATH="/tmp/rmdb_sysbench"
PORT=18770

RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
NC='\033[0m'

cleanup_procs() {
    echo -e "${CYAN}[cleanup]${NC} Killing all rmdb processes..."
    pkill -9 rmdb 2>/dev/null || true
    sleep 0.5
}

# ---- Build if needed -------------------------------------------------------
if [ ! -x "$SERVER" ]; then
    echo -e "${CYAN}[build]${NC} Building RuBase (Release)..."
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    cmake -DCMAKE_BUILD_TYPE=Release .. > /dev/null
    make -j"$(nproc)" > /dev/null
    cd "$PROJECT_DIR"
    echo -e "${GREEN}[build]${NC} Done."
fi

# ---- Pre-flight cleanup ----------------------------------------------------
cleanup_procs
rm -rf "$DB_PATH"

# ---- Launch server ---------------------------------------------------------
echo -e "${CYAN}[launch]${NC} Starting RuBase on port $PORT ..."
"$SERVER" "$DB_PATH" "$PORT" > /dev/null 2>&1 &
SERVER_PID=$!
echo "  PID: $SERVER_PID"

# Wait for server to be ready
for i in $(seq 1 20); do
    if python3 -c "
import socket, sys
try:
    s = socket.socket(); s.settimeout(1); s.connect(('127.0.0.1', $PORT)); s.close()
    sys.exit(0)
except: sys.exit(1)
" 2>/dev/null; then
        echo -e "${GREEN}[launch]${NC} Server ready."
        break
    fi
    sleep 0.5
done

# ---- Prepare ---------------------------------------------------------------
echo -e "\n${CYAN}[prepare]${NC} Creating sbtest table + 10,000 baseline rows..."
export RMDB_HOST="127.0.0.1"
export RMDB_PORT="$PORT"

sysbench "$SCRIPT_DIR/sysbench_rmdb.lua" \
    --threads=1 \
    prepare

# ---- Run -------------------------------------------------------------------
echo -e "\n${CYAN}[run]${NC} OLTP benchmark: 64 threads, 180 seconds..."
echo "  host=${RMDB_HOST}  port=${RMDB_PORT}"
echo ""

sysbench "$SCRIPT_DIR/sysbench_rmdb.lua" \
    --threads=64 \
    --time=180 \
    --report-interval=5 \
    --rand-type=special \
    run

# ---- Cleanup ---------------------------------------------------------------
echo ""
echo -e "${CYAN}[cleanup]${NC} Dropping ${RED}sbtest${NC} table..."
sysbench "$SCRIPT_DIR/sysbench_rmdb.lua" \
    --threads=1 \
    cleanup

# ---- Teardown --------------------------------------------------------------
echo -e "\n${CYAN}[teardown]${NC} Shutting down server..."
kill -9 "$SERVER_PID" 2>/dev/null || true
wait "$SERVER_PID" 2>/dev/null || true
cleanup_procs

echo -e "${GREEN}Done.${NC}"
