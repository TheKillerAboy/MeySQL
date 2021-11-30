import json
import os
import socket

def request(req):
    host = os.environ["MEYSQL_HOST"]
    port = int(os.environ["MEYSQL_PORT"])

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        s.sendall(json.dumps(req).encode())
        return json.loads(s.recv(32767).decode())