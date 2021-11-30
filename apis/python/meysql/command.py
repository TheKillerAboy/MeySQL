from request import request

def request_command(command, kwargs):
    return request(
        {
            'command': command,
            'args': kwargs
        }
    )