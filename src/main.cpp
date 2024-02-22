/**
 * @file main.cpp
 * @author Radica
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "display.h"
#include "reshape.h"

#ifdef WIN32
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#elif __linux__
#endif

// 创建菜单
void createActions() {
    glutCreateMenu(buttonCallback);
    glutAddMenuEntry("Draw Rect Demo", 0);
    glutAddMenuEntry("Draw Arc Demo", 1);
    glutAddMenuEntry("Draw Simple ArcPolygon Demo", 2);
    glutAddMenuEntry("Draw Complex ArcPolygon Demo", 3);
    glutAddMenuEntry("Intersection", 4);
    glutAddMenuEntry("Union", 5);
    glutAddMenuEntry("Difference", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);  // 将菜单绑定到鼠标右键
}

int main(int argc, char** argv) {
    // 初始化GLUT库
    glutInit(&argc, argv);
    // 设置显示模式为单缓冲和RGB颜色模式
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // 设置窗口大小
    glutInitWindowSize(800, 800);
    // 创建窗口并设置窗口标题
    glutCreateWindow("EDA Geometry Library Test");
    // 设置绘制回调函数
    glutDisplayFunc(display);
    // 窗口大小变化回调函数
    glutReshapeFunc(reshape);
    // 创建右键菜单
    createActions();
    // 进入GLUT主循环
    glutMainLoop();

    return 0;
}
