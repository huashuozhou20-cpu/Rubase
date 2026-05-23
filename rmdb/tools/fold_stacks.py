#!/usr/bin/env python3
"""
Convert raw backtrace samples (written by Sampler) into FlameGraph folded format.

Usage:
  python3 fold_stacks.py /tmp/rmdb_samples.bin ./build/bin/rmdb
    → writes folded stack lines to stdout, suitable for flamegraph.pl

Format of the binary sample file (produced by sampler.h):
  [uint16_t sample_id][uint16_t depth][depth × void* frame_addrs] ... repeated
"""

import struct
import subprocess
import sys
from collections import Counter

def resolve_addrs(addrs, binary_path):
    """Resolve a list of hex addresses to symbol names using addr2line."""
    if not addrs:
        return ["(empty)"]
    hex_addrs = " ".join("0x{:x}".format(a if isinstance(a, int) else int(a))
                         for a in addrs)
    try:
        out = subprocess.check_output(
            ["addr2line", "-e", binary_path, "-f", "-p", "-C", "-a"]
            + hex_addrs.split(),
            stderr=subprocess.DEVNULL,
            timeout=5,
        ).decode("utf-8", errors="replace")
    except (subprocess.TimeoutExpired, FileNotFoundError, OSError):
        return ["{:x}".format(a) for a in addrs]

    lines = out.strip().split("\n")
    symbols = []
    for idx, line in enumerate(lines):
        # addr2line -p output: "0xADDR: func at file:line"
        # Extract just the function name part
        if ":" in line:
            # Format: "0xADDR: symbol at file:line" or "0xADDR: ?? ??:0"
            parts = line.split(":", 1)
            if len(parts) >= 2:
                sym = parts[1].strip()
                # Drop " at file:line" suffix
                if " at " in sym:
                    sym = sym.split(" at ")[0]
            else:
                sym = line
        else:
            sym = line
        # Clean up
        if sym.startswith("??") or sym == "":
            if idx < len(addrs):
                sym = "0x{:x}".format(addrs[idx])
            else:
                sym = "??"
        symbols.append(sym)
    return symbols


def main():
    if len(sys.argv) < 3:
        print("Usage: fold_stacks.py <samples.bin> <path/to/binary>", file=sys.stderr)
        sys.exit(1)

    bin_path = sys.argv[1]
    elf_path = sys.argv[2]

    counter = Counter()

    with open(bin_path, "rb") as f:
        while True:
            hdr = f.read(4)  # [u16 sample_id][u16 depth]
            if not hdr:
                break
            if len(hdr) < 4:
                break
            sid, depth = struct.unpack("<HH", hdr)
            frame_data = f.read(depth * 8)  # 64-bit void*
            if len(frame_data) < depth * 8:
                break
            addrs = struct.unpack("<" + "Q" * depth, frame_data)

            # Resolve addresses → function names
            symbols = resolve_addrs(addrs, elf_path)

            # FlameGraph folded format: "func1;func2;...;funcN  count"
            # Reverse so root is first (caller → callee order)
            stack_str = ";".join(reversed(symbols))
            counter[stack_str] += 1

    for stack, count in counter.most_common():
        print("{} {}".format(stack, count))

    print("// Processed {} unique stacks ({} total samples)".format(
        len(counter), sum(counter.values())), file=sys.stderr)


if __name__ == "__main__":
    main()
