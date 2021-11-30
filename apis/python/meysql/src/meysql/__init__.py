import os

from meysql.allcommands import check_active

def setup(host='localhost', port=5332):
    os.environ["MEYSQL_HOST"] = host
    os.environ["MEYSQL_PORT"] = str(port)

setup()