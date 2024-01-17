#include "shaperender/shaperender.h"

#include "algorithm/boolean.h"
#include "core/arcpolygon.h"
#include "core/edge.h"
#include "core/edgedomain.h"
#include "core/linkednode.h"
#include "core/rectangle.h"

#ifdef WIN32
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#elif __linux__
#endif

#include <cmath>
#include <iostream>

int DISPLAY_STATE = -1;

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 设置清除颜色为黑色
    glClear(GL_COLOR_BUFFER_BIT);          // 清除颜色缓冲区
    glLoadIdentity();                      // 重置当前矩阵为单位矩阵
    glColor3f(1.0f, 0.0f, 0.0f);           // 设置绘制颜色为红色

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

// 按钮回调函数
void buttonCallback(int buttonId) {
    DISPLAY_STATE = buttonId;
    glutPostRedisplay();  // 标记窗口需要重新绘制
}

void geometryTest() {
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

    // 初始化附加点
    int count = 0;
    auto lnTail1 = linkedNode1;
    auto lnTail2 = linkedNode2;
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

    // 声明相关边域
    std::vector<core::EdgeDomain> edgeDomain1;
    std::vector<core::EdgeDomain> edgeDomain2;

    // 声明相关边
    std::vector<Edge> edge1;
    std::vector<Edge> edge2;

    algorithm::arcPolyPretreatment(poly1, poly2, edgeDomain1, edgeDomain2,
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
    geometryTest();
    // 初始化GLUT库
    glutInit(&argc, argv);
    // 设置显示模式为单缓冲和RGB颜色模式
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // 设置窗口大小
    glutInitWindowSize(600, 600);
    // 创建窗口并设置窗口标题
    glutCreateWindow("EDA Geometry Library Test");
    // 设置绘制回调函数
    glutDisplayFunc(display);
    // 创建右键菜单
    createActions();
    // 进入GLUT主循环
    glutMainLoop();

    return 0;
}
