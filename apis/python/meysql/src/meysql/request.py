import json
import logging
import os
import socket

request_logger = logging.getLogger('request')

def request(req):
    host = os.environ["MEYSQL_HOST"]
    port = int(os.environ["MEYSQL_PORT"])

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        request_logger.info(f"###\nRequesting: {json.dumps(req, indent=4)}\n###")
        s.sendall(json.dumps(req).encode())
        res = json.loads(s.recv(32767).decode())
        return res