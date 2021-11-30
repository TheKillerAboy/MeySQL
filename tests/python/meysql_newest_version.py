import re
from pathlib import Path

def main():
    meysql_dist = Path("{__file__}/../../../apis/python/meysql/dist/")
    meysql_dist = meysql_dist.resolve()
    searcher = re.compile("meysql-(\d+)\.(\d+)\.(\d+)\.tar\.gz")
    best = ((0,0,0), None)
    for file in meysql_dist.iterdir():
        search = searcher.search(file.name)
        if search:
            best = max(best, (tuple(map(int,search.groups())),file))
    print(best[1])

if __name__ == "__main__":
    main()
