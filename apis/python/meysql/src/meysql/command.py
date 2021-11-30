import logging

from meysql.request import request

def request_command(command, kwargs):
    if 'res' in kwargs:
        del kwargs['res']
    return request(
        {
            'command': command,
            'args': kwargs
        }
    )

command_logger = logging.getLogger('command')

def command(command):
    def wrapper(func):
        def wrapper_inner(**kwargs):
            try:
                return func(**kwargs, res=request_command(command, kwargs))
            except Exception as e:
                command_logger.error(e)
        return wrapper_inner
    return wrapper