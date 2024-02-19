#include "shaperender/shaperender.h"

#include "algorithm/boolean.h"
#include "core/arcpolygon.h"
#include "core/edge.h"
#include "core/edgenode.h"
#include "core/linkednode.h"
#include "core/rectangle.h"
#include "utils/timer.h"

#ifdef WIN32
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#elif __linux__
#endif

#include <chrono>
#include <cmath>
#include <iostream>

#define GUI_  // 界面开关
//#define LOG_  // 辅助打印信息

int DISPLAY_STATE = -1;

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 设置清除颜色为黑色
    glClear(GL_COLOR_BUFFER_BIT);          // 清除颜色缓冲区
    glLoadIdentity();                      // 重置当前矩阵为单位矩阵
    glColor3f(0.0f, 1.0f, 1.0f);           // 设置绘制颜色为红色

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
            // 绘制简单多边形
            ShapeRender::drawSimpleArcPolygon();
            break;
        }
        case 3: {
            // 绘制复杂多边形
            ShapeRender::drawComplexArcPolygon();
            break;
        }
        case 4: {
            // TODO: 求交集
            break;
        }
        case 5: {
            // TODO: 求并集
            break;
        }
        case 6: {
            // TODO: 求差集
            break;
        }
        default: {
            // 绘制简单多边形
            ShapeRender::drawSimpleArcPolygon();
            break;
        }
    }
    glFlush();  // 刷新缓冲区，将绘制命令发送到OpenGL进行处理
}

// 定义窗口大小变化回调函数
void reshape(int width, int height) {
    //    std::cout << "call reshape" << std::endl;
    //    // 设置视口大小为窗口大小
    //    glViewport(0, 0, width, height);
    //
    //    // 使用投影矩阵来处理图形的投影变换等
    //    glMatrixMode(GL_PROJECTION);
    //    glLoadIdentity();
    //    // 设置投影方式，这里使用正交投影，可以根据需求选择其他投影方式
    //    // 这里设置的是以窗口的左下角为原点，窗口大小为单位长度
    //    glOrtho(0, width, 0, height, -1, 1);
    //
    //    // 切换回模型视图矩阵
    //    glMatrixMode(GL_MODELVIEW);
}

// 按钮回调函数
void buttonCallback(int buttonId) {
    DISPLAY_STATE = buttonId;
    glutPostRedisplay();  // 标记窗口需要重新绘制
}

void geometryTest() {
    Timer t("geometry test", true);
    using namespace core;
    // 初始图形坐标点
    std::vector<Point> poly1Points = {{0.0, 0.2},  {0.0, 0.4},  {-0.4, 0.4},
                                      {-0.4, 0.0}, {-0.2, 0.0}, {0.0, -0.2},
                                      {0.0, 0.2}};
    std::vector<Point> poly2Points = {{0.5, 0.0}, {0.7, 0.0}, {0.7, 0.4},
                                      {0.3, 0.4}, {0.3, 0.2}, {0.3, -0.2},
                                      {0.5, 0.0}};

    // 构建环形双向链表
    auto* linkedNode1 = LinkedNode::constructLinkedNodes(poly1Points);
    auto* linkedNode2 = LinkedNode::constructLinkedNodes(poly2Points);

    // 初始化附加点，即产生圆弧
    int count = 0;
    auto lnTail1 = linkedNode1;
    auto lnTail2 = linkedNode2;
    // 手动赋上附加点
    while (true) {
        count++;
        if (count == 6) {
            lnTail1->mIsAppendix = true;
            lnTail2->mIsAppendix = true;
        }
        lnTail1 = lnTail1->mNext;
        lnTail2 = lnTail2->mNext;
        if (lnTail1 == linkedNode1 || lnTail2 == linkedNode2) {
            break;
        }
    }
    // 构造圆弧多边形
    auto poly1 = new ArcPolygon(linkedNode1);
    auto poly2 = new ArcPolygon(linkedNode2);
#ifdef LOG_
    std::cout << "******** input vertices ********" << std::endl;
    std::cout << "arc polygon 1: " << std::endl;
    std::cout << *poly1 << std::endl;
    std::cout << "arc polygon 2: " << std::endl;
    std::cout << *poly2 << std::endl;
    std::cout << "*******input vertices end *******" << std::endl;
#endif
    // 声明序列的边节点
    std::vector<core::EdgeNode> sequencedEdge1;
    std::vector<core::EdgeNode> sequencedEdge2;

    // 声明相关边
    std::vector<Edge> edge1;
    std::vector<Edge> edge2;

    algorithm::arcPolyPretreatment(poly1, poly2, sequencedEdge1, sequencedEdge2,
                                   edge1, edge2);
}

void createActions() {
    // 创建菜单
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
    // 用于几何库快速验证
//    geometryTest();
#ifdef GUI_
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
#endif

    return 0;
}
