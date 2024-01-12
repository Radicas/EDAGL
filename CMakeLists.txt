cmake_minimum_required(VERSION 3.5)

project(EDA_GL)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

# 查找 OpenGL 库
find_package(OpenGL REQUIRED)

# 查找 GLUT 库
find_package(GLUT REQUIRED)

# 查找 Benchmark
find_package(benchmark REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(test_benchmark)