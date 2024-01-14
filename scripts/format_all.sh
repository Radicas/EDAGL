#!/bin/bash

# 根目录路径
ROOT_DIR=$(dirname "$(pwd)")

# 递归格式化函数
format_files() {
    local dir=$1

    # 遍历目录下的文件和子目录
    for file in "$dir"/*; do
        if [ -d "$file" ]; then
            # 递归处理子目录
            format_files "$file"
        elif [ "${file##*.}" = "h" ] || [ "${file##*.}" = "cpp" ]; then
            # 格式化 .h 和 .cpp 文件
            clang-format -i "$file"
            echo "Formatted: $file"
        fi
    done
}

# 在根目录下递归格式化文件
format_files "$ROOT_DIR"
