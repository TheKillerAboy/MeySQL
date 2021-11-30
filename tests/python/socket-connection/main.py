#!/usr/bin/env python3

import meysql
import logging

logging.getLogger().setLevel(logging.DEBUG)

print(meysql.server_config())