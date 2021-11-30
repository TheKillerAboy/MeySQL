#!/usr/bin/env python3

import socket

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 8080        # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b'{"command":"check-active"}')
    data = s.recv(32767)
    s.sendall(b'{"command":"exit"}')

print('Received', repr(data))