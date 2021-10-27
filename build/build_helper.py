from pathlib import Path
import glob
import fire

def replace_block(lines, prefix, new_lines):
    b = lines.index(f"#{prefix} begin\n")
    e = lines.index(f"#{prefix} end\n")
    pre = lines[:b+1]
    aft = lines[e:]
    lines = pre+new_lines+aft
    
    return lines


def set_header_files(lines, src_dir):
    PREFIX = "header_files_block"
    search_dir = src_dir/"headers"/"include"
    files = glob.glob(f'{search_dir}/*.h')
    files = list(map(lambda f: Path(f).relative_to(search_dir), files))
    new_lines="set(\n\tHEADER_FILES\n"
    new_lines+='\n'.join(map(lambda f:f"\t${{MY_INCLUDES_DIR}}/{f}", files))
    new_lines+="\n)"
    new_lines = list(map(lambda f:f+'\n',new_lines.split('\n')))
    return replace_block(lines, PREFIX, new_lines)

def set_source_files(lines, src_dir):
    PREFIX = "src_files_block"
    search_dir = src_dir/"src"
    files = glob.glob(f'{search_dir}/*.cpp')
    files = list(map(lambda f: Path(f).relative_to(search_dir), files))
    new_lines="set(\n\tSOURCE_FILES\n"
    new_lines+='\n'.join(map(lambda f:f"\t${{MY_SRC_DIR}}/{f}", files))
    new_lines+="\n)"
    new_lines = list(map(lambda f:f+'\n',new_lines.split('\n')))
    return replace_block(lines, PREFIX, new_lines)

def main(src_dir="../MeySQL"):
    src_dir = Path(src_dir)
    with open(src_dir/'CMakeLists.txt','r') as f:
        lines = f.readlines()
    lines = set_header_files(lines, src_dir)
    lines = set_source_files(lines, src_dir)
    with open(src_dir/'CMakeLists.txt','w') as f:
        f.writelines(lines)

if __name__ == '__main__':
    fire.Fire(main)
