from pathlib import Path
import re

my_util_c = './release/myutil.c'
my_util_h = './release/myutil.h'

head_path = Path("./head/")

head_list = list(head_path.glob("*.h"))

head_files = [str(file) for file in head_list]
head_files.sort()

common_file = 'head/common.h'
i = head_files.index(common_file)
head_files[0], head_files[i] = head_files[i], head_files[0]

with open(my_util_h, 'w') as fh:
    fh.write('#ifndef __MYUTIL_H__\n#define __MYUTIL_H__\n')

for head_file in head_files:
    file_lines = []

    with open(head_file) as f:
        file_lines = f.readlines()
        del file_lines[0]
        del file_lines[0]
        # print(file_lines)
        for i in range(0, len(file_lines)):
            j = len(file_lines) - i - 1
            line = file_lines[j]
            if re.match('#endif.*', line):
                del file_lines[j]
                break
    f.close()

    file_lines = [line for line in file_lines if not re.match(
        '#include\\s?".*"', line)]
    file_lines.append('\n')

    with open(my_util_h, 'a') as f2:
        for line in file_lines:
            f2.write(line)
    f2.close()

with open(my_util_h, 'a') as fh:
    fh.write('#endif\n')


# SOURCE
#
#
#
src_path = Path("./source/")

src_list = list(src_path.glob("*.c"))

src_files = [str(file) for file in src_list]


with open(my_util_c, 'w') as fh:
    fh.write('#include "myutil.h"\n')

for src_file in src_files:
    file_lines = []

    with open(src_file) as f:
        file_lines = f.readlines()
        del file_lines[0]
    f.close()

    file_lines.append('\n')

    with open(my_util_c, 'a') as f2:
        for line in file_lines:
            f2.write(line)
    f2.close()
