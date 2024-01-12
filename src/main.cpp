#include "shaperender/shaperender.h"

#ifdef WIN32
#include <GL/glut.h>
#elif __linux__
#elif __APPLE__

#include <GLUT//glut.h>

#endif

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <iostream>

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 设置清除颜色为黑色
    glClear(GL_COLOR_BUFFER_BIT);         // 清除颜色缓冲区

    glLoadIdentity(); // 重置当前矩阵为单位矩阵

    // 将对话框平移到窗口中心
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    glTranslatef(static_cast<float>(windowWidth) / 2, static_cast<float>(windowHeight) / 2, 0.0f);

    // 绘制一个简单的对话框
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5f, -0.5f); // 左下角顶点
    glVertex2f(-0.5f, 0.5f);  // 左上角顶点
    glVertex2f(0.5f, 0.5f);   // 右上角顶点
    glVertex2f(0.5f, -0.5f);  // 右下角顶点
    glEnd();

    glLoadIdentity(); // 重置当前矩阵为单位矩阵

    glColor3f(1.0f, 0.0f, 0.0f); // 设置绘制颜色为红色
    // 绘制一个红色矩形
//    ShapeRender::drawRectangle();
    // 绘制一个红色圆形
    ShapeRender::drawArc(0, 0, 0.5, 0, 3.0 * M_PI / 2.0, 100);

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
    switch (buttonId) {
        case 0:
            // 按钮一被点击
            color[0] = 1.0; // 设置颜色为红色
            color[1] = 0.0;
            color[2] = 0.0;
            break;
            // 添加更多按钮的处理逻辑
    }

    glutPostRedisplay(); // 标记窗口需要重新绘制
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);                       // 初始化GLUT库
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // 设置显示模式为单缓冲和RGB颜色模式

    glutInitWindowSize(750, 750);         // 设置窗口大小
    glutCreateWindow("OpenGL示例"); // 创建窗口并设置窗口标题

    glutDisplayFunc(display); // 设置绘制回调函数
    glutReshapeFunc(reshape); // 设置窗口大小改变回调函数

    // 创建菜单
    glutCreateMenu(buttonCallback);
    glutAddMenuEntry("Test Button 1", 0);
    glutAddMenuEntry("Test Button 2", 0);
    glutAddMenuEntry("Test Button 3", 0);

    glutMainLoop(); // 进入GLUT主循环，等待事件发生

    return 0;
}
