#!/usr/bin/env python3
"""
Shared test harness for RMDB chaos scripts.
Provides uniform port management, server lifecycle, and socket helpers.
"""

import socket
import os
import time
import subprocess
import signal

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)
BUILD_DIR = os.path.join(PROJECT_DIR, "build")
SERVER = os.path.join(BUILD_DIR, "bin", "rmdb")

# Each test script gets a unique default port to avoid cross-test collision.
_DEFAULT_PORTS = {
    "lock_starvation": 18765,
    "log_wrap":       18766,
    "soak_leak":      18767,
}

# ---------------------------------------------------------------------------
# Port management
# ---------------------------------------------------------------------------

def default_port_for(test_name):
    """Return the default port for a named test."""
    return _DEFAULT_PORTS.get(test_name, 18765)


# ---------------------------------------------------------------------------
# Process lifecycle
# ---------------------------------------------------------------------------

def kill_all_servers():
    """Kill every rmdb process owned by this user and let the TCP stack drain."""
    try:
        subprocess.run(["pkill", "-9", "rmdb"],
                       capture_output=True, timeout=5)
    except Exception:
        pass
    time.sleep(0.5)  # let kernel release TIME_WAIT / TCP buffers


def start_server(db_path, port, stdout=subprocess.DEVNULL,
                 stderr=subprocess.DEVNULL):
    """Launch rmdb on the given DB path and port."""
    return subprocess.Popen([SERVER, db_path, str(port)],
                            cwd=BUILD_DIR,
                            stdout=stdout, stderr=stderr)


def start_fresh_server(db_path, port):
    """Delete DB directory, then launch a fresh server."""
    subprocess.run(["rm", "-rf", db_path], capture_output=True)
    return start_server(db_path, port)


def wait_for_server(host="127.0.0.1", port=18765, timeout=5):
    """Poll until a TCP connection succeeds or timeout expires."""
    deadline = time.time() + timeout
    while time.time() < deadline:
        try:
            s = socket.socket()
            s.settimeout(1)
            s.connect((host, port))
            s.close()
            return True
        except Exception:
            time.sleep(0.3)
    return False


# ---------------------------------------------------------------------------
# Socket I/O
# ---------------------------------------------------------------------------

def sql(sock, stmt, timeout=10):
    """Send a semicolon-terminated statement and return the response."""
    if not stmt.endswith(";"):
        stmt += ";"
    sock.sendall(stmt.encode())
    sock.settimeout(timeout)
    try:
        return sock.recv(65536).decode(errors="replace")
    except socket.timeout:
        return "<TIMEOUT>"


def count_rows(resp):
    """Count data rows in a formatted table response."""
    n = 0
    for line in resp.split('\n'):
        if line.startswith('|') and '+---' not in line and 'Total' not in line:
            n += 1
    return max(0, n - 1)


def connect(host="127.0.0.1", port=18765, timeout=30):
    """Return a connected socket."""
    s = socket.socket()
    s.settimeout(timeout)
    s.connect((host, port))
    return s


# ---------------------------------------------------------------------------
# Resource monitoring
# ---------------------------------------------------------------------------

def get_vmrss(pid):
    """Read VmRSS (kB) from /proc/<pid>/status."""
    try:
        with open(f"/proc/{pid}/status", "r") as f:
            for line in f:
                if line.startswith("VmRSS:"):
                    return int(line.split()[1])
    except Exception:
        pass
    return -1


def get_file_size(path):
    """Return file size in bytes, or -1."""
    try:
        return os.path.getsize(path)
    except Exception:
        return -1
