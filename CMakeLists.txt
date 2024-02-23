# 最小版本
cmake_minimum_required(VERSION 3.5)

# 项目名称
project(EDA_GL)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

# 设置安装目录
set(INSTALL_DIR ${CMAKE_SOURCE_DIR}/install)

# 查找 OpenGL 库
find_package(OpenGL REQUIRED)

# 查找 GLUT 库
find_package(GLUT REQUIRED)

# 查找 Benchmark
find_package(benchmark REQUIRED)

# 查找 Gtest库
find_package(GTest REQUIRED)

find_package(CGAL REQUIRED)
# 关掉 DEBUG 下CGAL的警告
set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE TRUE)

# 添加子目录
add_subdirectory(edagl) # 几何库
add_subdirectory(src) # 源文件
add_subdirectory(test) # google test 单元测试

# add_subdirectory(bench_mark)
