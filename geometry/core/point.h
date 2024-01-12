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

namespace core
{
    struct Point
    {
        double x{};
        double y{};

        Point() = default;

        Point(double x, double y) : x(x), y(y)
        {
        }

        Point(const Point &rhs)
        {
            x = rhs.x;
            y = rhs.y;
        }

        Point &operator=(const Point &rhs) = default;

        Point &operator+(const Point &rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Point &operator+=(const Point &rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Point &operator*(double val)
        {
            x *= val;
            y *= val;
            return *this;
        }

        Point &operator*=(double val)
        {
            x *= val;
            y *= val;
            return *this;
        }

        bool operator==(const Point &rhs) const
        {
            return x == rhs.x && y == rhs.y;
        }

        bool operator!=(const Point &rhs) const
        {
            return !(*this == rhs);
        }

        friend std::ostream &operator<<(std::ostream &os, const Point &point)
        {
            os << point.x << "," << point.y;
            return os;
        }

        inline void Negate()
        {
            x = -x;
            y = -y;
        }
    };
} // namespace geometry

#endif // EDA_GL_POINT_H
