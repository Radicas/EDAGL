set(PROJECT_TEST EDA_GL_TEST)

# 查找头文件、源文件
file(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" "*.h")

include_directories(${CMAKE_SOURCE_DIR}/geometry)

# 添加可执行文件
add_executable(${PROJECT_TEST} ${SOURCE_FILES})

# 链接 google test 库
target_link_libraries(${PROJECT_TEST} PRIVATE
        GTest::GTest
        GTest::Main
        geometry
)
set(enable_testing())

# 安装
install(TARGETS ${PROJECT_TEST} DESTINATION ${CMAKE_SOURCE_DIR}/install)