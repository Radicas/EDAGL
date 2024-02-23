#include "point.h"
#include <cmath>

namespace edagl {
namespace core {

Point::Point(double x, double y) : x(x), y(y) {}

Point::Point(const Point& rhs) {
    x = rhs.x;
    y = rhs.y;
}

Point Point::operator+(const Point& rhs) const {
    return {x + rhs.x, y + rhs.y};
}

Point& Point::operator+=(const Point& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Point& Point::operator-() {
    x = -x;
    y = -y;
    return *this;
}

Point Point::operator-(const Point& rhs) const {
    return {x - rhs.x, y - rhs.y};
}

Point& Point::operator-=(const Point& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Point Point::operator*(double val) const {
    return {x * val, y * val};
}

Point& Point::operator*=(double val) {
    x *= val;
    y *= val;
    return *this;
}

bool Point::operator==(const Point& rhs) const {
    return x == rhs.x && y == rhs.y;
}

bool Point::operator!=(const Point& rhs) const {
    return !(*this == rhs);
}

inline void Point::Negate() {
    x = -x;
    y = -y;
}

double Point::length() const {
    return std::sqrt(x * x + y * y);
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.x << "," << point.y << ")";
    return os;
}

}  // namespace core
}  // namespace edagl
