#include "display.h"

#include "cgal/cgal_boolean_op.h"
#include "cgal/cgal_edagl.h"
#include "core/arcpolygon.h"
#include "core/polygon_with_holes.h"
#include "core/rectangle.h"
#include "edgl_boolean_operations.h"
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

//#define CGAL_

int DISPLAY_STATE = -1;  // 显示状态

// 按钮回调函数
void buttonCallback(int buttonId) {
    DISPLAY_STATE = buttonId;
    // 标记窗口需要重新绘制
    glutPostRedisplay();
}

void display() {
    using namespace edagl::core;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 设置清除颜色为黑色
    glClear(GL_COLOR_BUFFER_BIT);          // 清除颜色缓冲区
    glLoadIdentity();                      // 重置当前矩阵为单位矩阵
    glColor3f(0.0f, 1.0f, 1.0f);           // 设置绘制颜色为红色

    ArcPolygon ap1(
        {{-0.5, 0.4}, {-0.5, -0.2}, {0.2, -0.2}, {0.2, 0.4}, {-0.5, 0.4}});
    ArcPolygon ap2({{-0.3, 0.3},
                    {-0.4, -0.4},
                    {-0.1, 0.1},
                    {-0.1, -0.3},
                    {0.4, 0.3},
                    {-0.3, 0.3}});

    switch (DISPLAY_STATE) {
        case 0: {  // 绘制矩形
            Rectangle rect(-0.3, -0.3, 0.6, 0.6, 0.0);
            shaperender::drawRectangle(rect);
            break;
        }
        case 1: {  // 绘制圆弧
            shaperender::drawArc(0, 0, 0.5, 0, (3.0 * M_PI) < 1, 100);
            break;
        }
        case 2: {  // 绘制简单多边形
            shaperender::drawArcPolygons({ap1, ap2});
            break;
        }
        case 3: {  // 绘制复杂多边形
            shaperender::drawComplexArcPolygon();
            break;
        }
        case 4: {  // 交集
#ifdef CGAL_
            auto result =
                cgal::computeIntersection(cgal::arcPolygon2CgalPolygon(ap1),
                                          cgal::arcPolygon2CgalPolygon(ap2));
            auto arcPolygons = cgal::cgal2EdaglPolygonWithHoles(result);
            shaperender::drawPolygonsWithHoles(arcPolygons);
#else
            auto result = edagl::algorithm::intersect(ap1, ap2);
            shaperender::drawPolygonsWithHoles(result);
#endif

            break;
        }
        case 5: {  // 并集
#ifdef CGAL_
            auto result = cgal::computeUnion(cgal::arcPolygon2CgalPolygon(ap1),
                                             cgal::arcPolygon2CgalPolygon(ap2));
            auto arcPolygons = cgal::cgal2EdaglPolygonWithHoles(result);
            shaperender::drawPolygonsWithHoles(arcPolygons);
#else
            auto result = edagl::algorithm::union_(ap1, ap2);
            shaperender::drawPolygonsWithHoles(result);
#endif

            break;
        }
        case 6: {  // 差集
#ifdef CGAL_
            auto result =
                cgal::computeDifference(cgal::arcPolygon2CgalPolygon(ap1),
                                        cgal::arcPolygon2CgalPolygon(ap2));
            auto arcPolygons = cgal::cgal2EdaglPolygonWithHoles(result);
            shaperender::drawPolygonsWithHoles(arcPolygons);
#else
            auto result = edagl::algorithm::difference(ap1, ap2);
            shaperender::drawPolygonsWithHoles(result);
#endif
            break;
        }
        default: {
            break;
        }
    }
    glFlush();  // 刷新缓冲区，将绘制命令发送到OpenGL进行处理
}