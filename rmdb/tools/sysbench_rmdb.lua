#!/usr/bin/env sysbench
-- ============================================================================
-- sysbench driver for RuBase — uses LuaJIT FFI for raw TCP socket I/O.
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

-- ---------------------------------------------------------------------------
-- Config from sysbench CLI
-- ---------------------------------------------------------------------------
local host    = os.getenv("RMDB_HOST") or "127.0.0.1"
local port    = tonumber(os.getenv("RMDB_PORT") or "18765")
local timeout = tonumber(os.getenv("RMDB_TIMEOUT") or "10")

-- Table schema for OLTP workload
local table_name = "sbtest"

-- ---------------------------------------------------------------------------
-- Helpers
-- ---------------------------------------------------------------------------
local function make_addr(host_str, port_num)
    local addr = ffi.new("struct sockaddr_in")
    C.memset(addr, 0, ffi.sizeof(addr))
    addr.sin_family = 2  -- AF_INET
    addr.sin_port   = ffi.cast("uint16_t",
        ((port_num % 256) * 256) + math.floor(port_num / 256))
    -- Parse dotted-quad IPv4
    local a,b,c,d = host_str:match("(%d+)%.(%d+)%.(%d+)%.(%d+)")
    if a then
        addr.sin_addr = tonumber(a) + tonumber(b)*256
                      + tonumber(c)*65536 + tonumber(d)*16777216
    else
        addr.sin_addr = 0x0100007f  -- 127.0.0.1
    end
    return addr
end

local function connect_socket()
    local addr = make_addr(host, port)
    for attempt = 1, 30 do
        local fd = C.socket(2, 1, 0)  -- AF_INET, SOCK_STREAM
        if fd < 0 then
            error("socket() failed: " .. ffi.string(C.strerror(ffi.errno())))
        end
        local rc = C.connect(fd, addr, ffi.sizeof(addr))
        if rc == 0 then
            return fd
        end
        C.close(fd)
        -- Back off and retry (server may be accepting connections slowly)
        if attempt % 5 == 0 then
            print(string.format("  [connect] retry %d/%d (port %d)", attempt, 30, port))
        end
        local tv = ffi.new("struct timeval")
        tv.tv_sec = 0
        tv.tv_usec = 100000  -- 100 ms
        ffi.C.select(0, nil, nil, nil, tv)
    end
    error("connect() failed after 30 attempts")
end

local function send_sql(fd, stmt)
    if not stmt:match(";$") then stmt = stmt .. ";" end
    local n = #stmt
    local buf = ffi.new("char[?]", n + 1)
    ffi.copy(buf, stmt)
    local sent = C.send(fd, buf, n, 0)
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
    if fd and fd >= 0 then
        C.close(fd)
    end
end

local function query(fd, stmt)
    send_sql(fd, stmt)
    return recv_response(fd)
end

-- Random helpers
local function rand_int(lo, hi)
    return lo + math.floor(sysbench.rand.uniform(0, hi - lo + 0.999999))
end

local function rand_str(len)
    local chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    local nchars = #chars
    local t = {}
    for i = 1, len do
        local idx = rand_int(1, nchars)
        t[i] = chars:sub(idx, idx)
    end
    return table.concat(t)
end

-- ---------------------------------------------------------------------------
-- Sysbench lifecycle
-- ---------------------------------------------------------------------------

-- Per-thread state
local thread_fd

function thread_init()
    -- Ensure table exists (done via prepare, but keep as guard)
    local fd = connect_socket()
    thread_fd = fd
end

function thread_done()
    close_socket(thread_fd)
    thread_fd = nil
end

-- ---------------------------------------------------------------------------
-- OLTP event: random mix of SELECT / INSERT / UPDATE / DELETE
-- ---------------------------------------------------------------------------
function event()
    local fd = thread_fd
    if not fd then
        fd = connect_socket()
        thread_fd = fd
    end

    local r = sysbench.rand.uniform(0, 1)
    local id = rand_int(1, 1000)
    local stmt

    if r < 0.45 then
        -- SELECT: range scan via index + predicate
        local lo = rand_int(1, 900)
        local hi = lo + rand_int(1, 100)
        stmt = string.format(
            "SELECT * FROM %s WHERE id BETWEEN %d AND %d AND val + 1 > 0",
            table_name, lo, hi)

    elseif r < 0.75 then
        -- INSERT: new row with random payload
        local new_id = 1001 + rand_int(1, 100000)
        local val = rand_int(1, 99999)
        local pad = rand_str(rand_int(20, 80))
        stmt = string.format(
            "INSERT INTO %s VALUES(%d, %d, '%s')",
            table_name, new_id, val, pad)

    elseif r < 0.92 then
        -- UPDATE: point update on existing row
        local val = rand_int(1, 99999)
        stmt = string.format(
            "UPDATE %s SET val=%d WHERE id=%d",
            table_name, val, id)

    else
        -- DELETE: remove a row (rotates with INSERTs)
        stmt = string.format("DELETE FROM %s WHERE id=%d", table_name, id)
    end

    local ok, resp = pcall(query, fd, stmt)
    if not ok then
        close_socket(thread_fd)
        thread_fd = connect_socket()
        pcall(query, thread_fd, stmt)
    elseif resp and resp:match("Error") then
        -- SQL error: acceptable for non-critical ops (e.g. DELETE on missing id)
    end
end

-- ---------------------------------------------------------------------------
-- Prepare: create table + insert baseline rows
-- ---------------------------------------------------------------------------
function prepare()
    local fd = connect_socket()
    print(string.format("  [prepare] Creating table %s ...", table_name))

    -- Drop if exists (ignore error)
    query(fd, string.format("DROP TABLE %s", table_name))

    -- Create OLTP table: id PK, val INT, padding TEXT
    query(fd, string.format(
        "CREATE TABLE %s (id INT PRIMARY KEY, val INT, padding TEXT)",
        table_name))

    -- Bulk insert baseline rows
    local nrows = 1000
    print(string.format("  [prepare] Inserting %d baseline rows ...", nrows))
    for i = 1, nrows do
        local val = rand_int(1, 99999)
        local pad = rand_str(rand_int(20, 60))
        query(fd, string.format(
            "INSERT INTO %s VALUES(%d, %d, '%s')",
            table_name, i, val, pad))
        if i % 200 == 0 then
            print(string.format("    %d / %d", i, nrows))
        end
    end

    -- Verify
    local resp = query(fd, string.format("SELECT * FROM %s", table_name))
    local count = 0
    for _ in resp:gmatch("|%s+%d+%s+|") do count = count + 1 end
    count = math.max(0, count - 1)  -- subtract header
    print(string.format("  [prepare] Done: %d rows in %s", count, table_name))

    C.close(fd)
end

-- ---------------------------------------------------------------------------
-- Cleanup: drop the benchmark table
-- ---------------------------------------------------------------------------
function cleanup()
    local fd = connect_socket()
    print(string.format("  [cleanup] Dropping table %s ...", table_name))
    query(fd, string.format("DROP TABLE %s", table_name))
    C.close(fd)
end
