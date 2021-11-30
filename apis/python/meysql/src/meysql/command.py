import json
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
                res = request_command(command, kwargs)
                command_logger.info(f"###\nResponse:\n{json.dumps(res, indent=4)}\n###")
                if res['status'] == "ERROR":
                    raise res['status-reason']
                return func(**kwargs, res=res)
            except Exception as e:
                command_logger.error(e)
        return wrapper_inner
    return wrapper