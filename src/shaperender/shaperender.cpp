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
    glVertex2d(-0.3f, -0.3f); // 左下角顶点
    glVertex2d(-0.3f, 0.3f);  // 左上角顶点
    glVertex2d(0.3f, 0.3f);   // 右上角顶点
    glVertex2d(0.3f, -0.3f);  // 右下角顶点
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 恢复绘制模式为填充模式
}

void ShapeRender::drawArc(double cx, double cy,
                          double radius,
                          double startAngle, double endAngle,
                          int numSegments) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 设置绘制模式为线框模式
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
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 恢复绘制模式为填充模式
}

void ShapeRender::drawTest() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 设置绘制模式为线框模式
    // 图形1
    glBegin(GL_LINE_STRIP); // 线段区
    glVertex2d(0.2f, 0.0f);
    glVertex2d(0.2f, 0.2f);
    glVertex2d(-0.2f, 0.2f);
    glVertex2d(-0.2f, -0.2f);
    glVertex2d(0.0f, -0.2f);
    glEnd();
    drawArc(0.2f, -0.2f, 0.2f, M_PI, 2.5f * M_PI, 16); // 圆弧区

    // 图形2
    glBegin(GL_LINE_STRIP);// 线段区
    glVertex2d(1.0f, -0.4f);
    glVertex2d(0.8f, 0.4f);
    glVertex2d(-0.2f, 0.3f);
    glVertex2d(0.5f, 0.1f);
    glEnd();
    drawArc(0.7f, -0.2f, 0.3605551275464f, 123.6900675259798f * M_PI / 180.0f, 326.3099324740202f * M_PI / 180.0f,
            16); // 圆弧区
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 恢复绘制模式为填充模式
}
/* endregion */
