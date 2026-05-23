#!/usr/bin/env sysbench
-- ============================================================================
-- sysbench_tpcc_mini.lua — TPC-C-inspired hot-row contention micro-benchmark
-- ============================================================================
-- Model:  single table "warehouse" with 100 baseline rows.
--         Hot rows (id 1–5) receive 50 % of UPDATE traffic, forcing extreme
--         lock and B+tree latch contention on the PK leaf page(s).
--
-- Workload mix:
--   50%  UPDATE  — hot-row quantity change  (X-lock on PK + row)
--   30%  SELECT  — range scan via PK         (shared index traversal)
--   20%  INSERT  — new random row            (appends to table)
-- ============================================================================

local ffi = require("ffi")

ffi.cdef[[
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  size_t;
typedef long           time_t;
typedef long           suseconds_t;

struct sockaddr_in {
    uint16_t sin_family;
    uint16_t sin_port;
    uint32_t sin_addr;
    char     sin_zero[8];
};

struct timeval {
    time_t      tv_sec;
    suseconds_t tv_usec;
};

int socket(int domain, int type, int protocol);
int connect(int sockfd, const struct sockaddr_in *addr, size_t addrlen);
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
int close(int fd);
int select(int nfds, void *readfds, void *writefds, void *exceptfds, struct timeval *timeout);
void *memset(void *s, int c, size_t n);
char *strerror(int errnum);
]]

local C = ffi.C

local host    = os.getenv("RMDB_HOST") or "127.0.0.1"
local port    = tonumber(os.getenv("RMDB_PORT") or "18765")
local table_name = "warehouse"
local HOT_ROWS = 5           -- rows 1..5 are hot
local BASELINE_ROWS = 100    -- initial data set

-- ---- TCP helpers -----------------------------------------------------------
local function make_addr(host_str, port_num)
    local addr = ffi.new("struct sockaddr_in")
    C.memset(addr, 0, ffi.sizeof(addr))
    addr.sin_family = 2
    addr.sin_port   = ffi.cast("uint16_t",
        ((port_num % 256) * 256) + math.floor(port_num / 256))
    local a,b,c,d = host_str:match("(%d+)%.(%d+)%.(%d+)%.(%d+)")
    if a then
        addr.sin_addr = tonumber(a) + tonumber(b)*256
                      + tonumber(c)*65536 + tonumber(d)*16777216
    else
        addr.sin_addr = 0x0100007f
    end
    return addr
end

local function connect_socket()
    local addr = make_addr(host, port)
    for attempt = 1, 30 do
        local fd = C.socket(2, 1, 0)
        if fd < 0 then
            error("socket() failed: " .. ffi.string(C.strerror(ffi.errno())))
        end
        local rc = C.connect(fd, addr, ffi.sizeof(addr))
        if rc == 0 then return fd end
        C.close(fd)
        local tv = ffi.new("struct timeval"); tv.tv_sec=0; tv.tv_usec=100000
        ffi.C.select(0, nil, nil, nil, tv)
    end
    error("connect() failed after 30 attempts")
end

local function send_sql(fd, stmt)
    if not stmt:match(";$") then stmt = stmt .. ";" end
    local buf = ffi.new("char[?]", #stmt + 1)
    ffi.copy(buf, stmt)
    local sent = C.send(fd, buf, #stmt, 0)
    if sent < 0 then return nil, ffi.string(C.strerror(ffi.errno())) end
    return sent
end

local function recv_response(fd, maxbytes)
    maxbytes = maxbytes or 65536
    local buf = ffi.new("char[?]", maxbytes)
    local n = C.recv(fd, buf, maxbytes, 0)
    if n <= 0 then return "" end
    return ffi.string(buf, n)
end

local function close_socket(fd)
    if fd and fd >= 0 then C.close(fd) end
end

local function query(fd, stmt)
    send_sql(fd, stmt)
    return recv_response(fd)
end

-- ---- Random helpers --------------------------------------------------------
local function rand_int(lo, hi)
    return lo + math.floor(sysbench.rand.uniform(0, hi - lo + 0.999999))
end

local function rand_str(len)
    local chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    local t = {}
    for i = 1, len do
        t[i] = chars:sub(rand_int(1, #chars), rand_int(1, #chars))
    end
    return table.concat(t)
end

-- ---- Per-thread state ------------------------------------------------------
local thread_fd

function thread_init()
    thread_fd = connect_socket()
end

function thread_done()
    close_socket(thread_fd)
    thread_fd = nil
end

-- ---- OLTP event: TPC-C-inspired hot-row contention mix --------------------
function event()
    local fd = thread_fd
    if not fd then
        fd = connect_socket()
        thread_fd = fd
    end

    local r = sysbench.rand.uniform(0, 1)
    local stmt

    if r < 0.50 then
        -- 50%: Hot-row UPDATE — concentrate on rows 1..HOT_ROWS (80% of the
        --      time) and scatter to cold rows otherwise.  This creates a
        --      pronounced hotspot on a small set of B+tree leaf pages.
        local id
        if sysbench.rand.uniform(0, 1) < 0.80 then
            id = rand_int(1, HOT_ROWS)
        else
            id = rand_int(HOT_ROWS + 1, BASELINE_ROWS)
        end
        local qty = rand_int(1, 99999)
        stmt = string.format("UPDATE %s SET quantity=%d WHERE id=%d",
                             table_name, qty, id)

    elseif r < 0.80 then
        -- 30%: SELECT range scan via PK — exercises shared index traversal
        --       concurrently with the hot-row updaters.
        local lo = rand_int(1, BASELINE_ROWS - 5)
        local hi = lo + rand_int(1, 10)
        stmt = string.format("SELECT * FROM %s WHERE id BETWEEN %d AND %d",
                             table_name, lo, hi)

    else
        -- 20%: INSERT a new row — appends to the table, exercises auto-increment
        --       and index-insertion under concurrent latch pressure.
        local qty = rand_int(1, 99999)
        local pad  = rand_str(rand_int(5, 15))
        stmt = string.format("INSERT INTO %s VALUES(%d, %d, '%s')",
                             table_name, BASELINE_ROWS + rand_int(1, 100000),
                             qty, pad)
    end

    local ok, resp = pcall(query, fd, stmt)
    if not ok then
        close_socket(thread_fd)
        thread_fd = connect_socket()
        pcall(query, thread_fd, stmt)
    elseif resp and resp:match("Error") then
        -- Acceptable (e.g. DELETE on missing id — N/A here)
    end
end

-- ---- Prepare ---------------------------------------------------------------
function prepare()
    local fd = connect_socket()
    print(string.format("  [tpcc-mini] Creating table %s ...", table_name))

    query(fd, string.format("DROP TABLE %s", table_name))

    query(fd, string.format(
        "CREATE TABLE %s (id INT PRIMARY KEY, quantity INT, data CHAR(20))",
        table_name))

    print(string.format("  [tpcc-mini] Inserting %d baseline rows ...", BASELINE_ROWS))
    for i = 1, BASELINE_ROWS do
        local qty = rand_int(1, 99999)
        local pad = rand_str(rand_int(5, 15))
        query(fd, string.format(
            "INSERT INTO %s VALUES(%d, %d, '%s')",
            table_name, i, qty, pad))
        if i % 20 == 0 then
            print(string.format("    %d / %d", i, BASELINE_ROWS))
        end
    end

    local resp = query(fd, string.format("SELECT COUNT(*) FROM %s", table_name))
    print(string.format("  [tpcc-mini] Done: table %s created.", table_name))

    C.close(fd)
end

-- ---- Cleanup ---------------------------------------------------------------
function cleanup()
    local fd = connect_socket()
    print(string.format("  [tpcc-mini] Dropping table %s ...", table_name))
    query(fd, string.format("DROP TABLE %s", table_name))
    C.close(fd)
end
