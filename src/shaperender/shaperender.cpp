#include "shaperender.h"

#ifdef WIN32
#include <GL/gl.h>
#elif __APPLE__
#include <OpenGL/gl.h>
#elif __linux__
#endif

#include "core/arcpolygon.h"
#include "core/linkednode.h"
#include "core/polygon_with_holes.h"
#include "core/rectangle.h"

#include <cmath>

namespace shaperender {
using namespace edagl::core;

void drawRectangle(const edagl::core::Rectangle& rect) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // 设置绘制模式为线框模式
    glBegin(GL_QUADS);
    glVertex2d(rect.topLeft().x, rect.topLeft().y);
    glVertex2d(rect.bottomLeft().x, rect.bottomLeft().y);
    glVertex2d(rect.bottomRight().x, rect.bottomRight().y);
    glVertex2d(rect.topRight().x, rect.topRight().y);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // 恢复绘制模式为填充模式
}

void drawArc(double cx, double cy, double radius, double startAngle,
             double endAngle, int numSegments) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // 设置绘制模式为线框模式
    glBegin(GL_LINE_STRIP);
    // 画圆心
    //    glVertex2d(cx, cy);
    for (int i = 0; i <= numSegments; i++) {
        double angle = startAngle + i * (endAngle - startAngle) / numSegments;
        // 计算弧上每个点的坐标
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        glVertex2d(x + cx, y + cy);
    }
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // 恢复绘制模式为填充模式
}

void drawSimpleArcPolygon() {
    ArcPolygon ap1({{0.0, 0.0}, {0.5, 0.0}, {0.5, 0.5}, {0.0, 0.5}});
    ArcPolygon ap2({{0.25, 0.25}, {0.25, -0.25}, {0.75, -0.4}, {0.75, 0.4}});
    shaperender::drawArcPolygons({ap1, ap2});
}

void drawComplexArcPolygon() {
    // 设置绘制模式为线框模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 图形1
    glBegin(GL_LINE_STRIP);
    glVertex2d(0.2f, 0.0f);
    glVertex2d(0.2f, 0.2f);
    glVertex2d(-0.2f, 0.2f);
    glVertex2d(-0.2f, -0.2f);
    glVertex2d(0.0f, -0.2f);
    glEnd();
    drawArc(0.2f, -0.2f, 0.2f, M_PI, 2.5f * M_PI, 16);

    // 图形2
    glBegin(GL_LINE_STRIP);
    glVertex2d(1.0f, -0.4f);
    glVertex2d(0.8f, 0.4f);
    glVertex2d(-0.2f, 0.3f);
    glVertex2d(0.5f, 0.1f);
    glEnd();
    drawArc(0.7f, -0.2f, 0.3605551275464f, 123.6900675259798f * M_PI / 180.0f,
            326.3099324740202f * M_PI / 180.0f, 16);
    // 恢复绘制模式为填充模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawArcPolygons(const std::vector<edagl::core::ArcPolygon>& polygons) {
    // 设置绘制模式为线框模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for (const auto& polygon : polygons) {
        LinkedNode* currentNode = polygon.getHeadNode();  // 获取多边形的头节点
        if (currentNode == nullptr)
            continue;  // 如果头节点为空，则跳过这个多边形
        glBegin(GL_LINE_STRIP);  // 开始绘制线段
        do {
            glVertex2f((float)currentNode->mData.x,
                       (float)currentNode->mData.y);  // 使用节点的数据绘制顶点
            currentNode = currentNode->mNext;  // 移动到下一个节点
        } while (currentNode !=
                 polygon.getHeadNode());  // 继绀遍历直到回到头节点
        glVertex2f((float)currentNode->mData.x,
                   (float)currentNode->mData.y);  // 确保闭合多边形
        glEnd();                                  // 结束绘制
    }
    // 恢复绘制模式为填充模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawPolygonsWithHoles(
    const std::vector<edagl::core::PolygonWithHoles>& polygonsWithHoles) {
    for (const auto& polygonWithHoles : polygonsWithHoles) {
        drawArcPolygons(polygonWithHoles.mData);
    }
}
}  // namespace shaperender
