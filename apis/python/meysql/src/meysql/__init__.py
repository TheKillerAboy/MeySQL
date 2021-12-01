import os

from meysql.allcommands import check_active
from meysql.allcommands import server_config

def setup(host='localhost', port=5332):
    os.environ["MEYSQL_HOST"] = host
    os.environ["MEYSQL_PORT"] = str(port)

setup()