# 设置库名称
set(LIB_NAME geometry)

# 查找库文件
FILE(GLOB_RECURSE LIB_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" "*.h")

# 源文件添加到库
add_library(${LIB_NAME}
        SHARED ${LIB_SOURCES})

# 目标查找头文件
target_include_directories(${LIB_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 安装库
install(TARGETS ${LIB_NAME}
        DESTINATION ${INSTALL_DIR}
)