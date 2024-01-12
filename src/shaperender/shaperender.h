//
// Created by Radica on 2024/1/3.
//

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
    void drawRectangle();
    void drawCircle();
    /* endregion */

private:
    /* region Data Members */

    /* endregion */
};

#endif // EDA_GL_SHAPERENDER_H
