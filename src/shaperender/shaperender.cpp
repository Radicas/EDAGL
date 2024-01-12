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
ShapeRender::ShapeRender() {}

ShapeRender::~ShapeRender() {}

/* endregion */

/* region General Methods */
void ShapeRender::drawRectangle()
{
    std::cout << "drawRectangle" << std::endl;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 设置绘制模式为线框模式
    glBegin(GL_QUADS);
    glVertex2f(-0.3f, -0.3f); // 左下角顶点
    glVertex2f(-0.3f, 0.3f);  // 左上角顶点
    glVertex2f(0.3f, 0.3f);   // 右上角顶点
    glVertex2f(0.3f, -0.3f);  // 右下角顶点
    glEnd();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 恢复绘制模式为填充模式
}

void ShapeRender::drawCircle()
{
    std::cout << "drawCircle" << std::endl;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 设置绘制模式为线框模式
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // 圆心
    int numSegments = 100;  // 圆形细分的线段数
    float radius = 0.3f;    // 半径
    for (int i = 0; i <= numSegments; i++)
    {
        float theta = 2.0f * 3.14159f * static_cast<float>(i) /
                      static_cast<float>(numSegments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}
/* endregion */
