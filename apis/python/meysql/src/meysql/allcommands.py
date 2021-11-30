from meysql.command import command

@command('check-active')
def check_active(res):
    return res['status'] == 'OK'