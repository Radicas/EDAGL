# 设置库名称
set(LIB_NAME geometry)

# 查找库文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/algorithm LIB_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/core LIB_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/math LIB_SOURCES)

# 源文件添加到库
add_library(${LIB_NAME}
        SHARED ${LIB_SOURCES})

# 安装库
install(TARGETS ${LIB_NAME}
        LIBRARY DESTINATION ${INSTALL_DIR})