/**
 * @file rectangle.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef EDA_GL_RECTANGLE_H
#define EDA_GL_RECTANGLE_H

namespace core {

    class Point;

    class Rectangle {
    public:
        /* region Constructors / Destructor */
        Rectangle();

        Rectangle(double x, double y, double h, double w, double angle);

        Rectangle(const Rectangle &other);

        Rectangle &operator=(const Rectangle &other);

        bool operator==(const Rectangle &other) const;
        /* endregion */

        /* region General Methods */
        Point topLeft() const;

        Point topRight() const;

        Point bottomLeft() const;

        Point bottomRight() const;
        /* endregion */

    private:
        double x;     // 左上角x
        double y;     // 左上角y
        double h;     // 高度
        double w;     // 宽度
        double angle; // 旋转角度 [0,2PI)
    };

} // namespace geometry

#endif // EDA_GL_RECTANGLE_H
