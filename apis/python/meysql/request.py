import json
import os
import socket

def request(req):
    HOST = os.environ.get('MEYSQL_HOST', 'localhost')
    PORT = os.environ.get('MEYSQL_PORT', 8080)

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(json.dumps(req).encode())
        res = s.recv(32767)
        return json.loads(res.decode())