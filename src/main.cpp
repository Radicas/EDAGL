#include "shaperender/shaperender.h"

#ifdef WIN32
#include <GL/glut.h>
#elif __linux__
#elif __APPLE__

#include <GLUT/glut.h>

#endif

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <iostream>

#include "core/rectangle.h"

int DISPLAY_STATE = -1;

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 设置清除颜色为黑色
    glClear(GL_COLOR_BUFFER_BIT);         // 清除颜色缓冲区
    glLoadIdentity();                     // 重置当前矩阵为单位矩阵
    glColor3f(1.0f, 0.0f, 0.0f);          // 设置绘制颜色为红色

    switch (DISPLAY_STATE) {
        case 0: {
            // 绘制矩形
            core::Rectangle rect(-0.3, -0.3, 0.6, 0.6, 0.0);
            ShapeRender::drawRectangle(rect);
            break;
        }
        case 1: {
            // 绘制圆弧
            ShapeRender::drawArc(0, 0, 0.5, 0, 3.0 * M_PI / 2.0, 100);
            break;
        }
        case 2: {
            // 绘制测试
            ShapeRender::drawTest();
            break;
        }
        case 3: {
            // TODO: 求交集
            break;
        }
        case 4: {
            // TODO: 求并集
            break;
        }
        case 5: {
            // TODO: 求差集
            break;
        }
        default:
            break;
    }
    glFlush(); // 刷新缓冲区，将绘制命令发送到OpenGL进行处理
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);  // 设置视口大小，与窗口大小一致
    glMatrixMode(GL_PROJECTION);      // 设置矩阵模式为投影矩阵
    glLoadIdentity();                 // 重置当前矩阵为单位矩阵
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // 设置正交投影矩阵，定义世界坐标系到视口坐标系的映射关系
    glMatrixMode(GL_MODELVIEW);       // 设置矩阵模式为模型视图矩阵
}

// 按钮回调函数
void buttonCallback(int buttonId) {
    DISPLAY_STATE = buttonId;
    glutPostRedisplay(); // 标记窗口需要重新绘制
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);                       // 初始化GLUT库
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // 设置显示模式为单缓冲和RGB颜色模式
    glutInitWindowSize(800, 800);                // 设置窗口大小
    glutCreateWindow("EDA Geometry Library Test");              // 创建窗口并设置窗口标题
    glutDisplayFunc(display);                    // 设置绘制回调函数
    glutReshapeFunc(reshape);                    // 设置窗口大小改变回调函数

    // 创建菜单
    glutCreateMenu(buttonCallback);
    glutAddMenuEntry("Draw Rect Demo", 0);
    glutAddMenuEntry("Draw Arc Demo", 1);
    glutAddMenuEntry("Draw PolyArc Demo", 2);
    glutAddMenuEntry("Intersection", 3);
    glutAddMenuEntry("Union", 4);
    glutAddMenuEntry("Difference", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON); // 将菜单绑定到鼠标右键
    glutMainLoop();                    // 进入GLUT主循环，等待事件发生

    return 0;
}
