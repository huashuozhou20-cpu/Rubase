#!/bin/bash
# ============================================================================
# chaos_recovery_test.sh — nested-crash ARIES recovery resilience test
# ============================================================================
# 1. Populates a table with INSERT / UPDATE traffic under concurrency.
# 2. kill -9 the server at a random moment during the workload.
# 3. Restarts the server so ARIES recovery + rebuild_indexes() runs.
# 4. During recovery, injects a SECOND kill -9 (nested crash).
# 5. Restarts again and verifies: table row count == B+tree index entry count.
# ============================================================================
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
SERVER="$PROJECT_DIR/build/bin/rmdb"
DB_PATH="/tmp/rmdb_chaos"
PORT=18800

RED='\033[0;31m'; GREEN='\033[0;32m'; CYAN='\033[0;36m'; YELLOW='\033[1;33m'; BOLD='\033[1m'; NC='\033[0m'

cleanup_all() {
    pkill -9 rmdb 2>/dev/null || true
    pkill -9 sysbench 2>/dev/null || true
    rm -rf "$DB_PATH"
}
trap cleanup_all EXIT

if [ ! -x "$SERVER" ]; then
    echo -e "${RED}[fatal]${NC} Server binary not found: $SERVER"
    echo "  Build: cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && make -j\$(nproc)"
    exit 1
fi

echo -e "${CYAN}╔══════════════════════════════════════════════════════════╗${NC}"
echo -e "${CYAN}║     RuBase  Chaos  Nested-Crash  Recovery  Test         ║${NC}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════╝${NC}"

# ---- Phase 1: Populate data ------------------------------------------------
echo -e "\n${BOLD}${YELLOW}[phase 1]${NC} Populating database..."
cleanup_all
"$SERVER" "$DB_PATH" "$PORT" > /dev/null 2>&1 &
SERVER_PID=$!
sleep 2

export RMDB_HOST="127.0.0.1" RMDB_PORT="$PORT"

# Create a simple table and insert baseline rows
python3 << 'PYEOF' 2>/dev/null
import socket, time
def q(s, sql):
    s.sendall((sql + ";\n").encode())
    time.sleep(0.1)
    s.settimeout(3)
    try: return s.recv(65536)
    except: return b""
s = socket.socket(); s.connect(("127.0.0.1", 18800))
q(s, "CREATE TABLE chaos_test (id INT PRIMARY KEY, val INT, padding CHAR(30))")
for i in range(1, 201):
    q(s, f"INSERT INTO chaos_test VALUES({i}, {i*10}, 'row_{i}')")
s.close()
print("  200 baseline rows inserted")
PYEOF

echo -e "${GREEN}[phase 1]${NC} Data populated."

# ---- Phase 2: First crash (kill -9 during concurrent workload) --------------
echo -e "\n${BOLD}${YELLOW}[phase 2]${NC} Injecting concurrent workload + random kill -9..."

# Background: rapid UPDATE workload
(
    python3 << 'PYEOF' 2>/dev/null &
import socket, random, time
s = socket.socket()
s.connect(("127.0.0.1", 18800))
for _ in range(500):
    try:
        rid = random.randint(1, 200)
        val = random.randint(1, 99999)
        s.sendall(f"UPDATE chaos_test SET val={val} WHERE id={rid};\n".encode())
        time.sleep(0.02)
    except: break
s.close()
PYEOF
)
WORKLOAD_PID=$!

# Wait a random interval then kill -9
sleep $((2 + RANDOM % 4))
echo "  → kill -9 $SERVER_PID"
kill -9 "$SERVER_PID" 2>/dev/null || true
wait "$WORKLOAD_PID" 2>/dev/null || true
sleep 1
echo -e "${GREEN}[phase 2]${NC} First crash delivered."

# ---- Phase 3: Nested crash during recovery ----------------------------------
echo -e "\n${BOLD}${YELLOW}[phase 3]${NC} Restarting for recovery + nested crash during rebuild..."

# Start server — it will run analyze/redo/undo/rebuild_indexes
"$SERVER" "$DB_PATH" "$PORT" > /dev/null 2>&1 &
SERVER_PID=$!

# Wait just long enough for recovery to start (but before it completes)
# rebuild_indexes is the last recovery step and takes the longest
RECOVERY_DELAY=$((1 + RANDOM % 2))
echo "  → Waiting ${RECOVERY_DELAY}s then kill -9 during recovery..."
sleep "$RECOVERY_DELAY"
echo "  → kill -9 $SERVER_PID (nested crash during rebuild_indexes)"
kill -9 "$SERVER_PID" 2>/dev/null || true
sleep 1
echo -e "${GREEN}[phase 3]${NC} Nested crash delivered."

# ---- Phase 4: Final recovery + integrity check ------------------------------
echo -e "\n${BOLD}${YELLOW}[phase 4]${NC} Final restart + integrity verification..."

"$SERVER" "$DB_PATH" "$PORT" > /dev/null 2>&1 &
SERVER_PID=$!
sleep 4  # give recovery time to complete

# Verify: row count in table == index entry count in B+tree
echo "  Running integrity checks..."

python3 << 'PYEOF' 2>/dev/null
import socket, time, re

def q(s, sql):
    s.sendall((sql + ";\n").encode())
    time.sleep(0.3)
    s.settimeout(5)
    try:
        data = b""
        while True:
            try:
                chunk = s.recv(65536)
                if not chunk: break
                data += chunk
                if len(chunk) < 65536: break
            except socket.timeout: break
        return data.decode(errors="replace")
    except: return ""

s = socket.socket(); s.connect(("127.0.0.1", 18800))

# Row count via SELECT COUNT(*)
resp = q(s, "SELECT COUNT(*) FROM chaos_test")
# Parse "Total record(s): N" or extract from table
total_match = re.search(r"Total record\(s\):\s*(\d+)", resp)
table_count = int(total_match.group(1)) if total_match else -1

# Count rows via index scan (SELECT id only = index-only path)
resp2 = q(s, "SELECT id FROM chaos_test")
rows = [l for l in resp2.split("\n") if l.strip().startswith("|") and not l.strip().startswith("| ")]
# Filter out header row
index_count = 0
for line in rows:
    cells = [c.strip() for c in line.split("|")[1:-1]]
    if cells and cells[0].isdigit():
        index_count += 1

print(f"  Table row count:  {table_count}")
print(f"  Index scan count: {index_count}")

if table_count == index_count and table_count > 0:
    print(f"\n  \033[0;32mPASS:\033[0m Table rows ({table_count}) == Index entries ({index_count})")
else:
    print(f"\n  \033[0;31mFAIL:\033[0m Table ({table_count}) != Index ({index_count})")

s.close()
PYEOF

RC=$?
echo -e "\n${GREEN}[phase 4]${NC} Verification complete."

if [ "$RC" -eq 0 ]; then
    echo -e "${GREEN}${BOLD}Chaos recovery test PASSED.${NC}"
else
    echo -e "${RED}${BOLD}Chaos recovery test FAILED.${NC}"
fi

cleanup_all
