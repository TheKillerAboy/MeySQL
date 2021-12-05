#!/usr/bin/env python

import subprocess
import sys
import yaml
import re

CONFIG_PATH = "config.yaml"
MEYSQL_TOML = "meysql/Cargo.toml"

def load_config():
    with open(CONFIG_PATH, "r") as f:
        return yaml.safe_load(f)

def save_config(data):
    with open(CONFIG_PATH, "w") as f:
        yaml.safe_dump(data, f)

def load_toml():
    with open(MEYSQL_TOML, "r") as f:
        return f.read()

def save_toml(data):
    with open(MEYSQL_TOML, "w") as f:
        f.write(data)

def bump_version(config):
    version_searcher = re.compile("(\d+).(\d+).(\d+)")
    version = list(map(int,version_searcher.search(config['version']).groups()))
    version[2] += 1
    config['version'] = '{}.{}.{}'.format(*version)
    save_config(config)
    return config

def set_toml_version(version, toml):
    version_searcher = re.compile("version = \"(\d+).(\d+).(\d+)\"")
    re_version = version_searcher.search(toml)
    span = re_version.span()
    toml = toml[:span[0]] + "version = \"{}\"".format(version) + toml[span[1]:]
    return toml

def build(config, toml):
    proc = subprocess.Popen(['cargo','build','--quiet'], stderr=subprocess.PIPE)
    proc.wait()
    out = proc.stderr.read().decode()
    if "error" not in out:
        config = bump_version(config)
    toml = set_toml_version(config["version"], toml)
    return config, toml

def run():
    try:
        subprocess.Popen(['cargo','run','--quiet']).wait()
    except KeyboardInterrupt:
        pass

def get_optcodes():
    return set(sys.argv[1:])

def main():
    optcodes = get_optcodes()
    
    config = load_config()
    toml = load_toml()
    config, toml = build(config, toml)

    if '-r' in optcodes:
        run()

    save_config(config)
    save_toml(toml)

if __name__ == '__main__':
    main()