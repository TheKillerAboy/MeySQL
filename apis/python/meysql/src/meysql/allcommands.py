from meysql.command import command

@command('check-active')
def check_active(res):
    return res['status'] == 'OK'

@command('server-config')
def server_config(res):
    return res['data']