#!/bin/bash
# ============================================================
# RuBase 服务端全自动测试 + 结果回传脚本
# 用法:  bash tools/server_test.sh
# ============================================================
cd "$(dirname "$0")/.."
RESULT_FILE="tools/server_results.txt"

section() { echo ""; echo "━━━ $1 ━━━"; }

# ===================================================================
# 0. 检查依赖
# ===================================================================
section "Check Dependencies"
MISSING=""
for cmd in cmake g++ make git sysbench python3; do
    if ! command -v $cmd &>/dev/null; then
        echo "  MISSING: $cmd"
        MISSING="$MISSING $cmd"
    fi
done
if [ -n "$MISSING" ]; then
    echo ""
    echo "Run: sudo apt update && sudo apt install -y build-essential cmake g++ git sysbench luajit libluajit-5.1-dev python3 libreadline-dev"
    exit 1
fi
echo "  All dependencies OK"

# ===================================================================
# 1. 拉取最新代码
# ===================================================================
section "Git Pull"
git pull origin main 2>&1

# ===================================================================
# 2. 系统信息
# ===================================================================
section "System Info"
{
echo "=== System Info ==="
echo "Date: $(date '+%Y-%m-%d %H:%M:%S')"
echo "Host: $(hostname)"
echo "Commit: $(git log --oneline -1)"
uname -a
echo "CPU cores: $(nproc)"
free -h | grep Mem
df -h / | tail -1
echo ""
} > $RESULT_FILE

# ===================================================================
# 3. 编译
# ===================================================================
section "Build Release"
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. 2>&1 | tail -1
make -j$(nproc) 2>&1 | tail -5
cd ..
echo "Release build done"

section "Build ASAN"
mkdir -p build_asan && cd build_asan
cmake -DENABLE_ASAN=ON .. 2>&1 | tail -1
make -j$(nproc) 2>&1 | tail -5
cd ..
echo "ASAN build done"

# ===================================================================
# 4. 单元测试
# ===================================================================
section "Unit Tests"
{
echo "=== Unit Tests ==="
./build/bin/unit_test 2>&1 | grep -E "PASSED|FAILED|test from" | head -10
echo ""
} >> $RESULT_FILE

# ===================================================================
# 5. ASAN 烟雾测试
# ===================================================================
section "ASAN Smoke"
pkill -9 rmdb sysbench 2>/dev/null || true; sleep 0.5
rm -rf /tmp/rmdb_asan
ASAN_OPTIONS=detect_leaks=0 ./build_asan/bin/rmdb /tmp/rmdb_asan 18790 &>/tmp/asan_smoke.log &
sleep 2
python3 tools/differential_fuzzer.py --seed 42 --queries 100 --port 18790 2>&1 | tail -5 || echo "  fuzzer skipped"
pkill -9 rmdb 2>/dev/null || true
ASAN_ERRS=$(grep -c 'ERROR\|heap-use\|data.race' /tmp/asan_smoke.log 2>/dev/null || echo 0)
{
echo "=== ASAN Smoke ==="
echo "ASAN errors: $ASAN_ERRS"
echo ""
} >> $RESULT_FILE

# ===================================================================
# 6. Sysbench 基准
# ===================================================================
for TH in 4 8; do
    section "Sysbench ${TH} threads"
    pkill -9 rmdb sysbench 2>/dev/null || true; sleep 0.5
    rm -rf /tmp/rmdb_sb${TH}
    PORT=$((18790 + TH))
    ./build/bin/rmdb /tmp/rmdb_sb${TH} $PORT &>/tmp/sb${TH}.log &
    sleep 2
    export RMDB_HOST="127.0.0.1" RMDB_PORT="$PORT"
    sysbench tools/sysbench_rmdb.lua --threads=1 prepare 2>&1 | tail -1
    {
    echo "=== Sysbench ${TH} threads ==="
    timeout 30 sysbench tools/sysbench_rmdb.lua \
        --threads=$TH --time=15 --report-interval=5 \
        --rand-type=special run 2>&1
    ERR=$(grep -c 'Error\|Segmentation' /tmp/sb${TH}.log 2>/dev/null || echo 0)
    echo "Errors: $ERR"
    echo ""
    } >> $RESULT_FILE
done
pkill -9 rmdb sysbench 2>/dev/null || true

# ===================================================================
# 7. 差分模糊器
# ===================================================================
section "Differential Fuzzer"
pkill -9 rmdb 2>/dev/null || true; sleep 0.5
rm -rf /tmp/rmdb_fuzz
./build/bin/rmdb /tmp/rmdb_fuzz 18793 &>/tmp/rmdb_fuzz.log &
sleep 2
{
echo "=== Differential Fuzzer (500 queries) ==="
python3 tools/differential_fuzzer.py --seed 789 --queries 500 --port 18793 2>&1 | tail -5
echo ""
} >> $RESULT_FILE
pkill -9 rmdb 2>/dev/null || true

# ===================================================================
# 8. 火焰图
# ===================================================================
section "FlameGraph"
if command -v perf &>/dev/null; then
    pkill -9 rmdb sysbench 2>/dev/null || true; sleep 0.5
    rm -rf /tmp/rmdb_perf
    ./build/bin/rmdb /tmp/rmdb_perf 18794 &>/tmp/perf_srv.log &
    sleep 2; export RMDB_HOST="127.0.0.1" RMDB_PORT="18794"
    sysbench tools/sysbench_rmdb.lua --threads=1 prepare 2>&1 | tail -1
    sysbench tools/sysbench_rmdb.lua --threads=4 --time=15 --rand-type=special run > /dev/null 2>&1 &
    sleep 2
    perf record -F 99 -g -p $(pgrep rmdb) -o /tmp/perf.data -- sleep 10 2>/dev/null
    mkdir -p /tmp/FlameGraph
    if [ ! -f /tmp/FlameGraph/flamegraph.pl ]; then
        git clone --depth 1 https://github.com/brendangregg/FlameGraph.git /tmp/FlameGraph 2>/dev/null || true
    fi
    perf script -i /tmp/perf.data 2>/dev/null | \
        /tmp/FlameGraph/stackcollapse-perf.pl 2>/dev/null | \
        /tmp/FlameGraph/flamegraph.pl --title "RuBase CPU" > tools/database_perf.svg 2>/dev/null
    echo "FlameGraph: tools/database_perf.svg" >> $RESULT_FILE
else
    echo "FlameGraph: perf not available" >> $RESULT_FILE
fi
pkill -9 rmdb sysbench 2>/dev/null || true

# ===================================================================
# 9. 推送结果
# ===================================================================
section "Push Results"
git add tools/server_results.txt tools/database_perf.svg 2>/dev/null || true
git commit -m "test: server results $(date '+%Y-%m-%d %H:%M')" 2>/dev/null || true
git push origin main 2>&1

echo ""
echo "Done. Results pushed to GitHub."
echo ""
cat $RESULT_FILE
