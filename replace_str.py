import chardet
import os
import re
import sys

def detect_encoding(filepath):
    with open(filepath, 'rb') as f:  # 以二进制模式读取文件
        raw_data = f.read()
        result = chardet.detect(raw_data)  # 检测编码
        return result['encoding']  # 返回检测出的编码

def process_file(filepath):
    encoding = detect_encoding(filepath)
    if encoding is None:
        print(f"无法检测文件编码: {filepath}")
        return
    
    with open(filepath, 'r', encoding=encoding) as f:
        content = f.read()

    pattern = r'MKSTR\("([^"]+)"\)'
    matches = re.findall(pattern, content)

    for match in matches:
        if '.' in match:
            var_name = match.split('.')[0]
        else:
            var_name = match

        expanded = f"char p{var_name}[] = {{'" + "', '".join(match) + "', '\\0'}"
        content = content.replace(f'MKSTR("{match}")', expanded)

    with open(filepath, 'w', encoding=encoding) as f:
        f.write(content)

def process_directory(directory):
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".c"):  # 只处理 .c 文件
                process_file(os.path.join(root, file))

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("请提供要处理的项目目录路径")
        sys.exit(1)

    project_directory = sys.argv[1]

    if not os.path.exists(project_directory):
        print(f"提供的路径不存在: {project_directory}")
        sys.exit(1)

    print(f"正在处理目录: {project_directory}")
    process_directory(project_directory)
    print("处理完成！")
