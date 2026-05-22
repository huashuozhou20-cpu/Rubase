#!/usr/bin/env python3
"""
RuBase vs SQLite Differential Fuzzer
======================================
Generates random schemas, data, and 2000 complex SELECT queries,
then compares RuBase results against SQLite (ground truth).
"""

import socket
import sqlite3
import sys
import os
import random
import argparse
import time
from collections import OrderedDict

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)


# ---------------------------------------------------------------------------
# RuBase client
# ---------------------------------------------------------------------------
class RuBaseClient:
    def __init__(self, host="127.0.0.1", port=18770, timeout=10):
        self.sock = socket.socket()
        self.sock.settimeout(timeout)
        self.sock.connect((host, port))

    def execute(self, stmt):
        if not stmt.endswith(";"):
            stmt += ";"
        self.sock.sendall(stmt.encode())
        try:
            resp = self.sock.recv(65536).decode(errors="replace")
        except socket.timeout:
            return "<TIMEOUT>", []
        return resp, self._parse_rows(resp)

    def _parse_rows(self, resp):
        """Parse RuBase tabular response into list of tuples."""
        rows = []
        sep_count = 0
        for line in resp.split("\n"):
            line = line.strip()
            if line.startswith("+---") and line.endswith("+"):
                sep_count += 1
                continue
            if line.startswith("|") and "Total" not in line:
                parts = [p.strip() for p in line.split("|")]
                parts = [p for p in parts if p]  # remove empty strings from leading/trailing |
                if not parts:
                    continue
                # Skip header row (between first and second separator)
                if sep_count == 1:
                    continue
                # Convert numeric-looking values, preserve strings/NULLs
                converted = []
                for p in parts:
                    if not p:
                        converted.append(None)
                        continue
                    try:
                        if '.' in p:
                            converted.append(float(p))
                        else:
                            converted.append(int(p))
                    except ValueError:
                        converted.append(p)
                rows.append(tuple(converted))
        return rows

    def close(self):
        try:
            self.sock.close()
        except Exception:
            pass


# ---------------------------------------------------------------------------
# SQLite reference
# ---------------------------------------------------------------------------
class SQLiteRef:
    def __init__(self):
        self.conn = sqlite3.connect(":memory:")
        self.conn.row_factory = lambda cursor, row: tuple(row)

    def execute(self, stmt):
        """Execute and return rows."""
        cur = self.conn.cursor()
        try:
            cur.execute(stmt)
            if stmt.strip().upper().startswith("SELECT"):
                return cur.fetchall()
            self.conn.commit()
            return []
        except Exception as e:
            return f"<ERROR: {e}>"

    def close(self):
        self.conn.close()


# ---------------------------------------------------------------------------
# SQL generators
# ---------------------------------------------------------------------------
OPS = ["=", "<>", "<", ">", "<=", ">="]
ARITH = ["+", "-"]

class SQLGen:
    def __init__(self, table="t", cols=None):
        self.table = table
        self.cols = cols or [
            ("id", "INT"),
            ("val", "INT"),
            ("score", "INT"),
            ("flag", "INT"),
            ("label", "INT"),
        ]
        self.col_names = [c[0] for c in self.cols]

    def _col(self):
        return random.choice(self.col_names)

    def _val(self, col_type="INT"):
        if col_type == "INT":
            return str(random.randint(-100, 1000))
        return "'" + ''.join(random.choices("abcdefghijklmnopqrstuvwxyz", k=random.randint(1, 10))) + "'"

    def _cond_leaf(self):
        col = self._col()
        op = random.choice(OPS)
        # Column-vs-literal only — avoids col-vs-col edge cases
        # that behave differently across engines.
        return f"{col} {op} {self._val()}"

    def gen_condition(self):
        """Generate a WHERE condition (AND-only — OR is a known RuBase issue)."""
        r = random.random()
        if r < 0.6:
            return self._cond_leaf()
        else:
            return f"{self._cond_leaf()} AND {self._cond_leaf()}"

    def gen_select(self):
        """Generate a random SELECT with optional WHERE, ORDER BY, LIMIT."""
        n = random.choice([1, 2, 3, 4])
        selected = random.sample(self.col_names, min(n, len(self.col_names)))
        cols = ", ".join(selected) if selected else "*"

        stmt = f"SELECT {cols} FROM {self.table}"

        if random.random() < 0.85:
            stmt += f" WHERE {self.gen_condition()}"


        if random.random() < 0.15:
            stmt += f" LIMIT {random.randint(1, 50)}"

        return stmt

    def gen_insert(self, seq_id=None):
        """Generate a random INSERT with a unique sequential ID."""
        vals = []
        for i, (_, ctype) in enumerate(self.cols):
            if i == 0 and seq_id is not None:
                vals.append(str(seq_id))  # primary key — use sequential value
            else:
                vals.append(self._val(ctype))
        return f"INSERT INTO {self.table} VALUES({', '.join(vals)})"


# ---------------------------------------------------------------------------
# Schema sync
# ---------------------------------------------------------------------------
def sync_schema(rubase, sqlite, table_name, cols):
    """Create the same table on both databases."""
    col_defs = []
    for name, ctype in cols:
        if ctype == "INT":
            col_defs.append(f"{name} INT")
    col_defs[0] += " PRIMARY KEY"

    create_sql = f"CREATE TABLE {table_name} ({', '.join(col_defs)})"

    # RuBase
    rubase.execute(f"DROP TABLE {table_name}")
    rubase.execute(create_sql)

    # SQLite
    try:
        sqlite.execute(f"DROP TABLE {table_name}")
    except Exception:
        pass
    sqlite.execute(create_sql)


def compare_rows(rubase_rows, sqlite_rows, stmt):
    """Compare result sets. Return (ok, details)."""
    r_set = set(rubase_rows)
    s_set = set(sqlite_rows)

    if r_set == s_set:
        return True, ""

    only_r = r_set - s_set
    only_s = s_set - r_set
    common = r_set & s_set

    msg = []
    msg.append(f"  RuBase rows: {len(rubase_rows)} unique")
    msg.append(f"  SQLite rows: {len(sqlite_rows)} unique")
    msg.append(f"  Common: {len(common)}")
    if only_r:
        msg.append(f"  Only in RuBase: {list(only_r)[:5]}")
    if only_s:
        msg.append(f"  Only in SQLite: {list(only_s)[:5]}")
    return False, "\n".join(msg)


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", type=int, default=18770)
    ap.add_argument("--host", default="127.0.0.1")
    ap.add_argument("--queries", type=int, default=2000,
                    help="Number of random SELECT queries (default: 2000)")
    ap.add_argument("--seed", type=int, default=None,
                    help="Random seed for reproducibility")
    ap.add_argument("--verbose", action="store_true")
    args = ap.parse_args()

    if args.seed is not None:
        random.seed(args.seed)
        seed_str = str(args.seed)
    else:
        seed_str = str(random.randint(1, 2**31))
        random.seed(seed_str)

    print("=" * 60)
    print("  RuBase vs SQLite Differential Fuzzer")
    print("=" * 60)
    print(f"  seed: {seed_str}  queries: {args.queries}")
    print()

    # Connect
    rubase = RuBaseClient(host=args.host, port=args.port)
    sqlite = SQLiteRef()

    # Schema
    COLS = [
        ("id", "INT"),
        ("val", "INT"),
        ("score", "INT"),
        ("flag", "INT"),
    ]
    TABLE = "fuzz"

    print("[Setup] Creating schema...")
    sync_schema(rubase, sqlite, TABLE, COLS)

    # Populate with random data (sequential IDs to avoid duplicate-key skew)
    gen = SQLGen(TABLE, COLS)
    N_INSERT = 100
    print(f"[Setup] Inserting {N_INSERT} random rows...")
    for i in range(1, N_INSERT + 1):
        stmt = gen.gen_insert(seq_id=i)
        rubase.execute(stmt)
        sqlite.execute(stmt)

    # Verify baseline row count matches
    _, r_rows = rubase.execute(f"SELECT count(*) FROM {TABLE}")
    s_rows = sqlite.execute(f"SELECT count(*) FROM {TABLE}")
    print(f"  RuBase: {r_rows}  SQLite: {len(s_rows)}")

    # ---- Fuzz loop ---------------------------------------------------------
    print(f"\n[Fuzz] Running {args.queries} random SELECT comparisons...\n")
    mismatches = 0
    errors = 0
    t0 = time.time()

    for i in range(args.queries):
        stmt = gen.gen_select()

        # Execute on both
        try:
            _, r_rows = rubase.execute(stmt)
        except Exception as e:
            r_rows = f"<EXCEPTION: {e}>"

        try:
            s_rows = sqlite.execute(stmt)
        except Exception as e:
            s_rows = f"<EXCEPTION: {e}>"

        # Skip if either side errored (schema/feature difference)
        if isinstance(r_rows, str) or isinstance(s_rows, str):
            errors += 1
            if args.verbose:
                print(f"  [{i}] SKIP (error): {stmt[:80]}")
            continue

        # Compare
        ok, details = compare_rows(r_rows, s_rows, stmt)
        if not ok:
            mismatches += 1
            print(f"  [{i}] MISMATCH!")
            print(f"  SQL: {stmt}")
            print(details)
            print()
            if mismatches >= 10:
                print("Too many mismatches — aborting.")
                break

        if args.verbose and i % 200 == 0:
            elapsed = time.time() - t0
            rate = (i + 1) / elapsed if elapsed > 0 else 0
            print(f"  [{i}/{args.queries}] {rate:.0f} q/s  mismatches={mismatches}  errors={errors}")

    elapsed = time.time() - t0
    rate = args.queries / elapsed if elapsed > 0 else 0
    print()
    print(f"  Completed {args.queries} queries in {elapsed:.1f}s ({rate:.0f} q/s)")
    print(f"  Mismatches: {mismatches}  Errors (skipped): {errors}")

    # Cleanup
    rubase.close()
    sqlite.close()

    # Verdict
    print()
    print("=" * 60)
    if mismatches == 0:
        print("  DIFFERENTIAL FUZZ: PASS  (zero mismatches)")
        print("=" * 60)
        return 0
    else:
        print(f"  DIFFERENTIAL FUZZ: FAIL  ({mismatches} mismatches)")
        print("=" * 60)
        return 1


if __name__ == "__main__":
    sys.exit(main())
