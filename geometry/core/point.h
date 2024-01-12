/**
 * @file point.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef EDA_GL_POINT_H
#define EDA_GL_POINT_H

#include <iostream>

namespace core {
    class Point {
    public:
        double x{};
        double y{};

        Point() = default;

        Point(double x, double y);

        Point(const Point &rhs);

        Point &operator=(const Point &rhs) = default;

        Point &operator+(const Point &rhs);

        Point &operator+=(const Point &rhs);

        Point &operator*(double val);

        Point &operator*=(double val);

        bool operator==(const Point &rhs) const;

        bool operator!=(const Point &rhs) const;

        // 声明为友元，可以访问私有属性
        friend std::ostream &operator<<(std::ostream &os, const Point &point) {
            os << point.x << "," << point.y;
            return os;
        }

        inline void Negate();
    };
} // namespace geometry

#endif // EDA_GL_POINT_H
