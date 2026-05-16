#!/usr/bin/env python3
"""RMDB 交互式命令行客户端"""

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

    print("RMDB 客户端已连接。输入 SQL (以 ; 结尾)，输入 exit 退出。\n")

    while True:
        try:
            sql = input("rmdb> ").strip()
        except (EOFError, KeyboardInterrupt):
            print("\nbye")
            break

        if not sql:
            continue
        if sql.lower() == "exit":
            sock.sendall(b"exit\0")
            break

        if not sql.endswith(";"):
            sql += ";"

        sock.sendall(sql.encode() + b"\0")

        text = ""
        sock.settimeout(3.0)
        try:
            response = sock.recv(65536)
            text = response.decode(errors="replace")
            if text.strip():
                print(text)
        except socket.timeout:
            pass

        # 根据响应判断成功/失败
        if "error" in text.lower() or "failure" in text.lower():
            print("  FAIL")
        else:
            print("  OK")

    sock.close()

if __name__ == "__main__":
    main()
