set(PROJECT_BENCHMARK EDA_GL_BENCHMARK)

# 查找头文件、源文件
file(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" "*.h")
file(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_SOURCE_DIR}/geometry "*.cpp" "*.h")

include_directories(${CMAKE_SOURCE_DIR}/geometry)
# 添加可执行文件
add_executable(${PROJECT_BENCHMARK} ${SOURCE_FILES})

# 链接 benchmark 库
target_link_libraries(${PROJECT_BENCHMARK} PRIVATE
        benchmark::benchmark
        )

# 安装
install(TARGETS ${PROJECT_BENCHMARK} DESTINATION ${CMAKE_SOURCE_DIR}/install)