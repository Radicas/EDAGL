/**
 * @file shaperender.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef EDA_GL_SHAPERENDER_H
#define EDA_GL_SHAPERENDER_H

class ShapeRender
{

public:
    /* region Constructors */
    ShapeRender();

    ShapeRender(const ShapeRender &other) = delete;

    ShapeRender &operator=(const ShapeRender &rhs) = delete;

    ~ShapeRender();
    /* endregion */

    /* region General Methods */
    static void drawRectangle();

    static void drawArc(double cx, double cy,
                        double radius,
                        double startAngle, double endAngle,
                        int numSegments);

    static void drawTest();
    /* endregion */

private:
    /* region Data Members */

    /* endregion */
};

#endif // EDA_GL_SHAPERENDER_H
