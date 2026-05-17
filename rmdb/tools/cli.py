#!/usr/bin/env python3
"""RMDB 交互式命令行客户端 — 支持多行输入、复制粘贴"""

import socket
import sys

HOST = "127.0.0.1"
PORT = 8765


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.connect((HOST, PORT))
    except ConnectionRefusedError:
        print(f"无法连接到 {HOST}:{PORT}，请先启动服务端: ./build/bin/rmdb <数据库路径>")
        sys.exit(1)

    print("RMDB 客户端已连接。输入 SQL (以 ; 结尾)，输入 exit 退出。")
    print("支持多行输入和直接复制粘贴。\n")

    while True:
        # 累积多行输入，直到遇到分号
        lines = []
        first_line = True
        while True:
            if first_line:
                sys.stdout.write("rmdb> ")
                sys.stdout.flush()

            try:
                line = sys.stdin.readline()
            except (EOFError, KeyboardInterrupt):
                print("\nbye")
                sock.close()
                return

            if not line:
                # EOF
                print("\nbye")
                sock.close()
                return

            line = line.rstrip("\r\n")

            # exit 可以直接退出（不带分号也行）
            if first_line and line.strip().lower() in ("exit", "exit;"):
                sock.sendall(b"exit\0")
                sock.close()
                print("bye")
                return

            first_line = False
            lines.append(line)

            # 如果这一行包含分号，输入结束
            if ";" in line:
                break

        sql = " ".join(lines).strip()
        sql = sql.replace("\r", "")
        if not sql:
            continue

        if not sql.endswith(";"):
            sql += ";"

        sock.sendall(sql.encode() + b"\0")

        # 接收响应
        text = ""
        sock.settimeout(3.0)
        try:
            response = sock.recv(65536)
            text = response.decode(errors="replace")
        except socket.timeout:
            pass

        # 只在有内容时才显示
        if text.strip():
            print(text.rstrip())

        # 只有失败时才显示 FAIL
        if "error" in text.lower() or "failure" in text.lower():
            print("  FAIL")

    sock.close()


if __name__ == "__main__":
    main()
