/**
 * @file point.h
 * @author Radica
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

namespace edagl {
namespace core {

/**
 * @brief 
 * 
 */
class Point {
   public:
    double x{};
    double y{};

    Point() = default;

    Point(double x, double y);

    Point(const Point& rhs);

    Point& operator=(const Point& rhs) = default;

    Point operator+(const Point& rhs) const;

    Point& operator+=(const Point& rhs);

    Point& operator-();

    Point operator-(const Point& rhs) const;

    Point& operator-=(const Point& rhs);

    Point operator*(double val) const;

    Point& operator*=(double val);

    bool operator==(const Point& rhs) const;

    bool operator!=(const Point& rhs) const;

    // 声明为友元，可以访问私有属性
    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << point.x << "," << point.y;
        return os;
    }

    /**
     * @brief 
     * 
     */
    inline void Negate();

    /**
     * @brief 
     * 
     * @return double 
     */
    double length() const;
};
typedef Point Vector2D;
}  // namespace core
}  // namespace edagl

#endif  // EDA_GL_POINT_H
