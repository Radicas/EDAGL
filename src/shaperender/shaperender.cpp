//
// Created by Radica on 2024/1/3.
//

#include "shaperender.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <cmath>
#include <iostream>

/* region Constructors / Destructor */
ShapeRender::ShapeRender() = default;

ShapeRender::~ShapeRender() = default;

/* endregion */

/* region General Methods */
void ShapeRender::drawRectangle()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 设置绘制模式为线框模式
    glBegin(GL_QUADS);
    glVertex2f(-0.3f, -0.3f); // 左下角顶点
    glVertex2f(-0.3f, 0.3f);  // 左上角顶点
    glVertex2f(0.3f, 0.3f);   // 右上角顶点
    glVertex2f(0.3f, -0.3f);  // 右下角顶点
    glEnd();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 恢复绘制模式为填充模式
}

void ShapeRender::drawArc(double cx, double cy,
                          double radius,
                          double startAngle, double endAngle,
                          int numSegments) {

    glBegin(GL_TRIANGLE_FAN);

    // 画圆心
    glVertex2d(cx, cy);

    for (int i = 0; i <= numSegments; i++) {
        double angle = startAngle + i * (endAngle - startAngle) / numSegments;

        // 计算弧上每个点的坐标
        double x = radius * cos(angle);
        double y = radius * sin(angle);

        glVertex2d(x + cx, y + cy);
    }

    glEnd();
}
/* endregion */
