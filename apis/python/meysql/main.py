import json
import socket

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 3333        # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.send(json.dumps({"process":"system-info","data":{}}).encode()+b'\n')
    data = s.recv(1024)

print('Received', repr(data))