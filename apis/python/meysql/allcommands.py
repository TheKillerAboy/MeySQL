from command import command

@command('check-active')
def check_active(res):
    try:
        if res['status'] == 'OK':
            return True
    except:
        pass
    finally:
        return False