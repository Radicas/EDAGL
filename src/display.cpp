#include "display.h"

#include "cgal/cgal_boolean_op.h"
#include "cgal/cgal_edagl.h"
#include "core/arcpolygon.h"
#include "core/rectangle.h"
#include "shaperender/shaperender.h"

#ifdef WIN32
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#elif __linux__
#endif

#include <cmath>

int DISPLAY_STATE = -1;

// 按钮回调函数
void buttonCallback(int buttonId) {
    DISPLAY_STATE = buttonId;
    glutPostRedisplay();  // 标记窗口需要重新绘制
}

void display() {

    using namespace edagl::core;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 设置清除颜色为黑色
    glClear(GL_COLOR_BUFFER_BIT);          // 清除颜色缓冲区
    glLoadIdentity();                      // 重置当前矩阵为单位矩阵
    glColor3f(0.0f, 1.0f, 1.0f);           // 设置绘制颜色为红色

    switch (DISPLAY_STATE) {
        case 0: {
            // 绘制矩形
            Rectangle rect(-0.3, -0.3, 0.6, 0.6, 0.0);
            shaperender::drawRectangle(rect);
            break;
        }
        case 1: {
            // 绘制圆弧
            shaperender::drawArc(0, 0, 0.5, 0, 3.0 * M_PI / 2.0, 100);
            break;
        }
        case 2: {
            // 绘制简单多边形
            shaperender::drawSimpleArcPolygon();
            break;
        }
        case 3: {
            // 绘制复杂多边形
            shaperender::drawComplexArcPolygon();
            break;
        }
        case 4: {
            // TODO: 求交集
            ArcPolygon ap1({{0.0, 0.0}, {0.5, 0.0}, {0.5, 0.5}, {0.0, 0.5}});
            ArcPolygon ap2(
                {{0.25, 0.25}, {0.25, -0.25}, {0.75, -0.4}, {0.75, 0.4}});
            auto result =
                cgal::computeIntersection(cgal::arcPolygon2CgalPolygon(ap1),
                                          cgal::arcPolygon2CgalPolygon(ap2));
            auto arcPolygons = cgal::cgalPolygonsWithHoles2ArcPolygons(result);
            shaperender::drawArcPolygons(arcPolygons);
            break;
        }
        case 5: {
            // TODO: 求并集
            ArcPolygon ap1({{0.0, 0.0}, {0.5, 0.0}, {0.5, 0.5}, {0.0, 0.5}});
            ArcPolygon ap2(
                {{0.25, 0.25}, {0.25, -0.25}, {0.75, -0.4}, {0.75, 0.4}});
            auto result = cgal::computeUnion(cgal::arcPolygon2CgalPolygon(ap1),
                                             cgal::arcPolygon2CgalPolygon(ap2));
            auto arcPolygons = cgal::cgalPolygonsWithHoles2ArcPolygons(result);
            shaperender::drawArcPolygons(arcPolygons);
            break;
        }
        case 6: {
            // TODO: 求差集
            ArcPolygon ap1({{0.0, 0.0}, {0.5, 0.0}, {0.5, 0.5}, {0.0, 0.5}});
            ArcPolygon ap2(
                {{0.25, 0.25}, {0.25, -0.25}, {0.75, -0.4}, {0.75, 0.4}});
            auto result =
                cgal::computeDifference(cgal::arcPolygon2CgalPolygon(ap1),
                                        cgal::arcPolygon2CgalPolygon(ap2));
            auto arcPolygons = cgal::cgalPolygonsWithHoles2ArcPolygons(result);
            shaperender::drawArcPolygons(arcPolygons);
            break;
        }
        default: {
            // 绘制简单多边形
            shaperender::drawSimpleArcPolygon();
            break;
        }
    }
    glFlush();  // 刷新缓冲区，将绘制命令发送到OpenGL进行处理
}