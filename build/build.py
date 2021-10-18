import sys
from pathlib import Path
import subprocess
from termcolor import colored
import glob

def run_cmd(cmd):
    result = subprocess.run(cmd, shell=True, capture_output=True)
    if result.stderr:
        print(colored(cmd, 'red'))
        print(result.stderr.decode('utf-8'))
    else:
        print(colored(cmd, 'green'))

if __name__ == '__main__':
    file = sys.argv[1]
    file = Path(file)
    src = Path(sys.argv[2])
    files = glob.glob(str(src/'*.cpp'), recursive=True)
    run_cmd(f'g++ -o {file.stem} {file} {" ".join(files)}')
