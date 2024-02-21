# 查找本地头文件、源文件
file(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" "*.h")

# 查找库头文件
include_directories(${CMAKE_SOURCE_DIR}/edagl)

# 添加可执行文件
add_executable(${PROJECT_NAME}
        ${SOURCE_FILES}
)

# 链接 OpenGL 和 GLUT 库
target_link_libraries(${PROJECT_NAME} PRIVATE
        OpenGL::GL
        GLUT::GLUT
        CGAL::CGAL
        edagl
)

# 安装
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${INSTALL_DIR}
)