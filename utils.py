#!/usr/bin/env python

import yaml
import os
import re
import shutil
import subprocess
from pathlib import Path

import typer
from typer import Argument, Option

CONFIG_FILE = Path("./config.yaml")
TOML_FILE = Path("./meysql/Cargo.toml")

def abort(code=1):
    print("Aborted!")
    exit(code)

def __live_read_then_output(stream):
    output = ""
    while True:
        line = stream.readline()
        if not line:
            break
        line = line.decode("utf-8")
        print(line)
        output += line
    return output

def __logging(debug=False, level=None):
    if level is None:
        level = 'Debug' if debug else 'Info'
    os.environ["RUST_LOG"] = level
    print(f"Logging set to level: {level}")

def __delete():
    if not typer.confirm("Are you sure you want to delete the old build?"):
        abort()
    shutil.rmtree('target')
    print("Deleted build: `target`")
    
def __build():
    proc = subprocess.Popen(["cargo","build"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output = __live_read_then_output(proc.stderr)
    if 'error' in output:
        print("Error occured:")
        print(output)
        abort()

def __run():
    subprocess.Popen(["cargo","run","--quiet"]).wait()

def __test():
    proc = subprocess.Popen(["cargo","test"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output = __live_read_then_output(proc.stdout)
    if 'FAILED' in output or 'error' in output:
        print("Tests failed:")
        print(output)
        abort()
    print('Tests Passed')

def __get_config():
    with open(CONFIG_FILE,'r') as f:
        return yaml.safe_load(f)

def __set_config(config):
    with open(CONFIG_FILE,'w') as f:
        yaml.safe_dump(config, f)

def __get_toml():
    with open(TOML_FILE,'r') as f:
        return f.read()

def __set_toml(toml):
    with open(TOML_FILE,'w') as f:
        f.write(toml)

def __convert_version_string(version):
    return list(map(int,re.search("(\d+).(\d+).(\d+)", version).groups()))

def __get_version_remote():
    proc = subprocess.Popen(['git', 'show', f'origin/main:{CONFIG_FILE}'], stdout=subprocess.PIPE)
    proc.wait()
    output = proc.stdout.read().decode('utf-8')
    remote_config = yaml.safe_load(output)
    print(f"Remote Version: {remote_config['version']}")
    return __convert_version_string(remote_config['version'])
    
def __get_version_local():
    config = __get_config()
    print(f"Local Version: {config['version']}")
    return __convert_version_string(config['version'])

def __set_version(new_version):
    config = __get_config()
    toml = __get_toml()

    config["version"] = new_version
    search = re.search("version = \"(.+)\"", toml)
    toml = toml[:search.span()[0]] + f"version = \"{new_version}\"" + toml[search.span()[1]:]

    __set_toml(toml)
    __set_config(config)

    print(f'Bumped to version: {new_version}')

def __get_new_version(major=False, sub_major=False):
    version_rmt = __get_version_remote()
    version_lcl = __get_version_local()
    new_version = max(version_rmt, version_lcl)
    if major:
        new_version = [new_version[0]+1,0,0]
    elif sub_major:
        new_version = [new_version[0], new_version[1]+1, 0]
    else:
        new_version = [*new_version[:2], new_version[2]+1]
    return "{}.{}.{}".format(*new_version)

def __bump_version(major=False, sub_major=False):
    new_version = __get_new_version(major, sub_major)
    __set_version(new_version)
    

app = typer.Typer()

@app.command()
def build(
    test_build:bool=
        Option(
            True, 
            "--test",
            "-t",
            help="Test build before building"
        ), 
    run_build:bool=
        Option(
            False, 
            "--run",
            "-r",
            help="Run test after building"
        ),
    delete_old_build:bool=
        Option(
            False,
            "--delete",
            "-d",
            help="Delete old build, before building"
        ),
    debug_on:bool=
        Option(
            False,
            '--debug',
            '-db',
            help="Enable debuging for logging"
        )   
):
    __logging(debug=debug_on)
    if delete_old_build:
        __delete()
    if test_build:
        __test()
    __build()
    if run_build:
        __run()

@app.command()
def delete():
    __delete()

@app.command()
def run():
    __run()

@app.command()
def test():
    __test()

@app.command()
def bump_version(
    major:bool=Option(
        False,
        '-m',
        '--major',
        help='Bump major version'
    ),
    sub_major:bool=Option(
        False,
        '-sm',
        '--sub_major',
        help='Bump sub major version'
    )
):
    __bump_version(major,sub_major)

@app.command()
def logging(
    level:str=Argument(
        "Info",
        help="Level to setting logging: [Error|Warning|Info|Debug]"
    )
):
    print("WARNING: Command not currently working")
    __logging(level=level)

if __name__ == "__main__":
    app()
