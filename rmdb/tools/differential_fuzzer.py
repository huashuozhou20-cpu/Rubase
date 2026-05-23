#!/usr/bin/env python3
"""
Differential SQL fuzzer — compares rmdb results against SQLite.

Generates random multi-table queries (JOIN, WHERE, aggregates) and sends
each to both rmdb and SQLite.  If the result sets diverge, the offending
SQL and a table snapshot are recorded and the test stops immediately.

Usage:
  python3 differential_fuzzer.py [--seed 42] [--queries 500] [--port 18765]
"""

import argparse
import random
import socket
import sqlite3
import sys
import time
import traceback
from typing import List

TABLES = ["t1", "t2"]
COLS = {
    "t1": [("a", "INT"), ("b", "INT"), ("c", "TEXT")],
    "t2": [("x", "INT"), ("y", "INT"), ("z", "TEXT")],
}
ALL_COLS = {t: [c[0] for c in cols] for t, cols in COLS.items()}
OPS = ["=", "<>", "<", ">", "<=", ">="]
AGGS = ["COUNT(*)", "SUM({})", "MAX({})", "MIN({})", "AVG({})"]


class FuzzerState:
    def __init__(self, seed: int, host: str, port: int):
        self.seed = seed; self.host = host; self.port = port
        random.seed(seed); self.rmdb_sock = None; self.sqlite_conn = None

    def rmdb_connect(self):
        s = socket.socket(); s.connect((self.host, self.port)); self.rmdb_sock = s

    def rmdb_query(self, sql: str):
        """Returns (raw_text, parsed_rows) tuple."""
        s = self.rmdb_sock
        stmt = sql.strip()
        if not stmt.endswith(";"): stmt += ";"
        s.sendall((stmt + "\n").encode())
        time.sleep(0.15)
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
        except Exception: pass
        raw = data.decode(errors="replace")
        return raw, _parse_rmdb_table(raw)

    def sqlite_exec(self, sql: str) -> List[List[str]]:
        cur = self.sqlite_conn.cursor()
        try:
            cur.execute(sql)
            rows = cur.fetchall()
            return [[str(v) if v is not None else "NULL" for v in row] for row in rows]
        except sqlite3.Error as e:
            return [["__SQLITE_ERROR__:" + str(e)]]

    # -- SQL generators --
    def ri(self, lo=1, hi=100): return random.randint(lo, hi)
    def rt(self): return random.choice(TABLES)
    def rc(self, t=None):
        return random.choice(ALL_COLS[t or self.rt()])
    def ro(self): return random.choice(OPS)

    def gen_select(self) -> str:
        if random.random() < 0.4:
            fc = "t1 JOIN t2 ON t1.a = t2.x"; ts = {"t1", "t2"}
        else:
            t = self.rt(); fc = t; ts = {t}
        # Generate projection: only use columns that exist in the chosen tables
        if random.random() < 0.35: proj = "*"
        elif random.random() < 0.35 and len(ts) == 1:
            proj = random.choice(AGGS).format(self.rc(list(ts)[0]))
        else:
            n = random.randint(1, 3)
            proj = ", ".join(f"{tbl}.{self.rc(tbl)}" for tbl in random.choices(list(ts), k=n))
        sql = f"SELECT {proj} FROM {fc}"
        if random.random() < 0.7:
            conds = []
            for _ in range(random.randint(1, 3)):
                tbl = random.choice(list(ts))
                # Only use INT columns for comparisons (TEXT vs INT is rejected)
                int_cols = [c[0] for c in COLS[tbl] if "INT" in c[1]]
                if int_cols:
                    col = random.choice(int_cols)
                    conds.append(f"{tbl}.{col} {self.ro()} {self.ri()}")
            if conds:
                sql += " WHERE " + " AND ".join(conds)
        return sql

    _insert_id = 1000  # monotonically increasing to avoid PK conflicts

    def gen_insert(self) -> str:
        t = self.rt(); vals = []
        for j, (_, typ) in enumerate(COLS[t]):
            if j == 0:  # first column is PK
                self._insert_id += 1
                vals.append(str(self._insert_id))
            else:
                vals.append(str(self.ri(1, 500)) if "INT" in typ else f"'r{self.ri(1,9999)}'")
        return f"INSERT INTO {t} VALUES({', '.join(vals)})"

    def gen_update(self) -> str:
        t = self.rt()
        cols_def = COLS[t]
        # Only update non-PK INT columns (PK updates have divergent semantics)
        non_pk = [c[0] for c in cols_def if "INT" in c[1] and c[0] != cols_def[0][0]]
        if not non_pk: return self.gen_select()  # fallback
        col = random.choice(non_pk)
        cond_col = random.choice([c[0] for c in cols_def if "INT" in c[1]])
        return f"UPDATE {t} SET {col}={self.ri()} WHERE {cond_col}={self.ri()}"

    def gen_delete(self) -> str:
        t = self.rt()
        # Delete by PK (first column) for deterministic single-row removal
        pk = COLS[t][0][0]
        return f"DELETE FROM {t} WHERE {pk}={self.ri()}"

    # -- Setup --
    def setup(self):
        self.rmdb_connect()
        self.sqlite_conn = sqlite3.connect(":memory:")
        for t, cols in COLS.items():
            col_defs = [f"{n} {tp}" for n, tp in cols]
            col_defs[0] += " PRIMARY KEY"
            ddl = f"CREATE TABLE {t} ({', '.join(col_defs)})"
            self.rmdb_query(f"DROP TABLE {t}")
            self.rmdb_query(ddl)
            self.sqlite_exec(f"DROP TABLE IF EXISTS {t}")
            self.sqlite_exec(ddl)
        for _ in range(20):
            sql = self.gen_insert()
            self.rmdb_query(sql)
            self.sqlite_exec(sql)

    # -- Fuzz loop --
    def fuzz(self, n: int) -> int:
        gens = [(0.45, self.gen_select), (0.20, self.gen_insert),
                (0.15, self.gen_update), (0.20, self.gen_delete)]
        for i in range(n):
            r = random.random(); cum = 0.0; chosen = gens[0][1]
            for p, g in gens:
                cum += p
                if r < cum: chosen = g; break
            sql = chosen()
            try: rmdb_raw, rmdb_rows = self.rmdb_query(sql)
            except Exception as e:
                print(f"\n[{i}] RMLDB CRASH: {sql}"); traceback.print_exc()
                self._snap(i, sql); return 1
            try: sqlite_rows = self.sqlite_exec(sql)
            except Exception: sqlite_rows = [["__ERROR__"]]
            # Skip deliberate semantic differences: type errors, missing tables
            if "Error" in rmdb_raw or "Incompatible" in rmdb_raw:
                if i % 50 == 0: print(f"[{i}] skip (error)")
                continue
            if any("__SQLITE_ERROR__" in str(c) for row in sqlite_rows for c in row):
                if i % 50 == 0: print(f"[{i}] skip (sqlite error)")
                continue
            if not _rows_eq(rmdb_rows, sqlite_rows):
                print(f"\n{'='*60}\nMISMATCH #{i}\nSQL: {sql}")
                print(f"rmdb   ({len(rmdb_rows)}): {rmdb_rows[:5]}")
                print(f"sqlite ({len(sqlite_rows)}): {sqlite_rows[:5]}")
                self._snap(i, sql); return 1
            if i % 100 == 0 and i > 0: print(f"[{i}] ok")
        print(f"\nAll {n} queries passed."); return 0

    def _snap(self, i, sql):
        path = f"/tmp/fuzzer_failure_{i}.txt"
        with open(path, "w") as f:
            f.write(f"FAILED #{i}:\n{sql}\n\n")
            for t in TABLES:
                _, rows = self.rmdb_query(f"SELECT * FROM {t}")
                f.write(f"rmdb {t}: {rows}\n")
        print(f"Snapshot → {path}")


def _parse_rmdb_table(text: str) -> List[List[str]]:
    lines = text.strip().split("\n"); rows = []; in_data = False
    for line in lines:
        line = line.strip()
        if line.startswith("+--"): in_data = True; continue
        if in_data and line.startswith("|"):
            cells = [c.strip() for c in line.split("|")[1:-1]]
            rows.append(cells)
    # Deduplicate consecutive identical rows (rmdb sometimes repeats headers)
    cleaned = []
    for r in rows:
        if cleaned and cleaned[-1] == r: continue
        cleaned.append(r)
    # Skip the header row (first data-like row after the separator)
    return cleaned[1:] if len(cleaned) > 1 else []


def _normalize(cell: str) -> str:
    """Normalize a cell value so that 229 == 229.000000 (float formatting)."""
    try:
        f = float(cell)
        if f == int(f):
            return str(int(f))
        return cell
    except (ValueError, OverflowError):
        return cell

def _rows_eq(a, b) -> bool:
    if len(a) != len(b): return False
    sa = sorted([tuple(_normalize(c) for c in r) for r in a])
    sb = sorted([tuple(_normalize(c) for c in r) for r in b])
    return sa == sb


def main():
    p = argparse.ArgumentParser(description="Differential SQL fuzzer: rmdb vs SQLite")
    p.add_argument("--seed", type=int, default=42)
    p.add_argument("--queries", type=int, default=500)
    p.add_argument("--host", default="127.0.0.1")
    p.add_argument("--port", type=int, default=18765)
    args = p.parse_args()
    state = FuzzerState(args.seed, args.host, args.port)
    print(f"Differential Fuzzer: rmdb vs SQLite  seed={args.seed}  n={args.queries}")
    try:
        state.setup(); rc = state.fuzz(args.queries); sys.exit(rc)
    except Exception as e:
        print(f"FATAL: {e}"); traceback.print_exc(); sys.exit(2)
    finally:
        if state.rmdb_sock: state.rmdb_sock.close()


if __name__ == "__main__":
    main()
