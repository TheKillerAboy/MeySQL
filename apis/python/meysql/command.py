from request import request

def request_command(command, kwargs):
<<<<<<< HEAD
=======
    if 'res' in kwargs:
        del kwargs['res']
>>>>>>> 80ff862 (Init api)
    return request(
        {
            'command': command,
            'args': kwargs
        }
<<<<<<< HEAD
    )
=======
    )

def command(command):
    def wrapper(func):
        def wrapper_inner(**kwargs):
            return func(**kwargs, res=request_command(command, kwargs))
        return wrapper_inner
    return wrapper
>>>>>>> 80ff862 (Init api)
