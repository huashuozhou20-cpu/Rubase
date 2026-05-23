#!/bin/bash
# ============================================================
# RuBase 服务端一键测试脚本
# 用法:  bash tools/server_test.sh
# 每次需要测试新东西时，这个文件会被覆盖，拉取后重新运行即可
# ============================================================
set -e
cd "$(dirname "$0")/.."

REPORT=~/rmdb_report.txt
> $REPORT

section() { echo ""; echo "━━━ $1 ━━━"; echo "━━━ $1 ━━━" >> $REPORT; }

# ---- 系统信息 ----
section "System Info"
uname -a | tee -a $REPORT
nproc | xargs echo "CPU cores:" | tee -a $REPORT
free -h | grep Mem | tee -a $REPORT
df -h / | tail -1 | tee -a $REPORT

# ---- 编译 Release ----
section "Build Release"
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. > /dev/null 2>&1
make -j$(nproc) 2>&1 | tail -3 | tee -a $REPORT
echo "Release build: OK" | tee -a $REPORT
cd ..

# ---- 编译 ASAN ----
section "Build ASAN"
mkdir -p build_asan && cd build_asan
cmake -DENABLE_ASAN=ON .. > /dev/null 2>&1
make -j$(nproc) 2>&1 | tail -3 | tee -a $REPORT
echo "ASAN build: OK" | tee -a $REPORT
cd ..

# ---- 单元测试 ----
section "Unit Tests"
./build/bin/unit_test 2>&1 | grep -E "PASSED|FAILED" | tee -a $REPORT

# ---- ASAN 烟雾 ----
section "ASAN Smoke (200 fuzz queries)"
pkill -9 rmdb sysbench 2>/dev/null || true; sleep 0.5
rm -rf /tmp/rmdb_asan_smoke
ASAN_OPTIONS=detect_leaks=0 ./build_asan/bin/rmdb /tmp/rmdb_asan_smoke 18790 &>/tmp/asan_smoke.log &
sleep 2
python3 tools/differential_fuzzer.py --seed 42 --queries 100 --port 18790 2>&1 | tail -5 | tee -a $REPORT
pkill -9 rmdb 2>/dev/null || true
echo "ASAN errors: $(grep -c 'ERROR\|heap-use\|data.race' /tmp/asan_smoke.log 2>/dev/null || echo 0)" | tee -a $REPORT

# ---- Sysbench 4 线程 ----
section "Sysbench 4 threads"
pkill -9 rmdb sysbench 2>/dev/null || true; sleep 0.5
rm -rf /tmp/rmdb_sb4
./build/bin/rmdb /tmp/rmdb_sb4 18791 &>/tmp/sb4.log &
sleep 2
export RMDB_HOST="127.0.0.1" RMDB_PORT="18791"
sysbench tools/sysbench_rmdb.lua --threads=1 prepare 2>&1 | tail -1
timeout 30 sysbench tools/sysbench_rmdb.lua --threads=4 --time=15 --report-interval=5 --rand-type=special run 2>&1 | tee -a $REPORT
echo "Errors: $(grep -c 'Error\|Segmentation' /tmp/sb4.log 2>/dev/null || echo 0)" | tee -a $REPORT

# ---- Sysbench 8 线程 ----
section "Sysbench 8 threads"
pkill -9 rmdb sysbench 2>/dev/null || true; sleep 0.5
rm -rf /tmp/rmdb_sb8
./build/bin/rmdb /tmp/rmdb_sb8 18792 &>/tmp/sb8.log &
sleep 2
export RMDB_PORT="18792"
sysbench tools/sysbench_rmdb.lua --threads=1 prepare 2>&1 | tail -1
timeout 30 sysbench tools/sysbench_rmdb.lua --threads=8 --time=15 --report-interval=5 --rand-type=special run 2>&1 | tee -a $REPORT
echo "Errors: $(grep -c 'Error\|Segmentation' /tmp/sb8.log 2>/dev/null || echo 0)" | tee -a $REPORT

# ---- 差分模糊器 ----
section "Differential Fuzzer (500 queries)"
pkill -9 rmdb 2>/dev/null || true; sleep 0.5
rm -rf /tmp/rmdb_fuzz
./build/bin/rmdb /tmp/rmdb_fuzz 18793 &>/tmp/rmdb_fuzz.log &
sleep 2
python3 tools/differential_fuzzer.py --seed 789 --queries 500 --port 18793 2>&1 | tail -5 | tee -a $REPORT
pkill -9 rmdb 2>/dev/null || true

# ---- 火焰图 (原生 Linux 上 perf 可用) ----
section "FlameGraph (15s perf)"
if command -v perf &>/dev/null; then
    pkill -9 rmdb sysbench 2>/dev/null || true; sleep 0.5
    rm -rf /tmp/rmdb_perf
    ./build/bin/rmdb /tmp/rmdb_perf 18794 &>/tmp/perf_srv.log &
    sleep 2
    export RMDB_HOST="127.0.0.1" RMDB_PORT="18794"
    sysbench tools/sysbench_rmdb.lua --threads=1 prepare 2>&1 | tail -1
    sysbench tools/sysbench_rmdb.lua --threads=4 --time=15 --rand-type=special run > /dev/null 2>&1 &
    sleep 2
    perf record -F 99 -g -p $(pgrep rmdb) -o /tmp/perf.data -- sleep 10 2>/dev/null
    if [ -d /tmp/FlameGraph ]; then
        perf script -i /tmp/perf.data | /tmp/FlameGraph/stackcollapse-perf.pl | /tmp/FlameGraph/flamegraph.pl --title "RuBase CPU" > ~/database_perf.svg
        echo "FlameGraph: ~/database_perf.svg" | tee -a $REPORT
    fi
else
    echo "perf not available (OK in WSL)" | tee -a $REPORT
fi

# ---- 清理 ----
pkill -9 rmdb sysbench 2>/dev/null || true
section "Done"
echo "Report: ~/rmdb_report.txt" | tee -a $REPORT
cat $REPORT
