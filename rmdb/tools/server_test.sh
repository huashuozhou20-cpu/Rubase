#!/bin/bash
# RuBase Server Auto-Test
# Usage: bash tools/server_test.sh
cd "$(dirname "$0")/.."
R=~/rmdb_report.txt
echo "=== $(date) ===" > $R

# ---- git pull ----
echo ">>> git pull" | tee -a $R
git pull origin main 2>&1 | tee -a $R

# ---- system info ----
echo ">>> system info" | tee -a $R
echo "host=$(hostname) cpu=$(nproc) commit=$(git log -1 --oneline)" | tee -a $R
uname -a | tee -a $R
free -h | grep Mem | tee -a $R

# ---- build ----
echo ">>> build release" | tee -a $R
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release .. 2>&1 | tail -3 | tee -a $R
make -j$(nproc) 2>&1 | tail -5 | tee -a $R
cd ..

# ---- unit test ----
echo ">>> unit test" | tee -a $R
./build/bin/unit_test 2>&1 | grep -E "PASSED|FAILED" | tee -a $R

# ---- sysbench 4 threads ----
echo ">>> sysbench 4 threads" | tee -a $R
pkill -9 rmdb sysbench 2>/dev/null; sleep 1
rm -rf /tmp/rmdb_test
./build/bin/rmdb /tmp/rmdb_test 18790 &>/tmp/rmdb.log &
sleep 2
sysbench tools/sysbench_rmdb.lua --threads=1 prepare 2>&1 | tail -1 | tee -a $R
timeout 30 sysbench tools/sysbench_rmdb.lua --threads=4 --time=15 \
    --report-interval=5 --rand-type=special run 2>&1 | tee -a $R
echo "server-errors: $(grep -c 'Error\|Segfault' /tmp/rmdb.log 2>/dev/null || echo 0)" | tee -a $R

# ---- sysbench 8 threads ----
echo ">>> sysbench 8 threads" | tee -a $R
pkill -9 rmdb sysbench 2>/dev/null; sleep 1
rm -rf /tmp/rmdb_test8
./build/bin/rmdb /tmp/rmdb_test8 18791 &>/tmp/rmdb8.log &
sleep 2
sysbench tools/sysbench_rmdb.lua --threads=1 prepare 2>&1 | tail -1 | tee -a $R
timeout 30 sysbench tools/sysbench_rmdb.lua --threads=8 --time=15 \
    --report-interval=5 --rand-type=special run 2>&1 | tee -a $R
echo "server-errors: $(grep -c 'Error\|Segfault' /tmp/rmdb8.log 2>/dev/null || echo 0)" | tee -a $R

# ---- push ----
echo ">>> push results" | tee -a $R
pkill -9 rmdb sysbench 2>/dev/null
git add $R tools/server_results.txt 2>/dev/null
cp $R tools/server_results.txt
git add tools/server_results.txt
git commit -m "test: server $(date '+%m-%d %H:%M')" 2>/dev/null
git push origin main 2>&1 | tee -a $R

echo "=== DONE ===" | tee -a $R
