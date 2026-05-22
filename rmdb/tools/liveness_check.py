#!/usr/bin/env python3
"""Post-recovery liveness check: INSERT / SELECT / DELETE on a unique row."""
import socket, sys, time

port = int(sys.argv[1]) if len(sys.argv) > 1 else 18780

# Wait for server (may be slow after index rebuild)
deadline = time.time() + 10
while time.time() < deadline:
    try:
        s = socket.socket()
        s.settimeout(2)
        s.connect(("127.0.0.1", port))
        break
    except Exception:
        time.sleep(0.5)
else:
    print("liveness: server not reachable")
    sys.exit(1)

LID = 999999

s.sendall(f"INSERT INTO sbtest VALUES({LID}, {LID}, 'live_test');".encode())
time.sleep(0.1)
s.recv(4096)  # ignore Duplicate key error

s.sendall(f"SELECT * FROM sbtest WHERE id={LID};".encode())
time.sleep(0.1)
r = s.recv(4096).decode()
assert str(LID) in r, "liveness SELECT failed"

s.sendall(f"DELETE FROM sbtest WHERE id={LID};".encode())
time.sleep(0.1)
s.recv(4096)

s.sendall(f"SELECT * FROM sbtest WHERE id={LID};".encode())
time.sleep(0.1)
r = s.recv(4096).decode()
assert "Total record(s): 0" in r, "liveness DELETE failed"

s.close()
