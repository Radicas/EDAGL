#include "rectangle.h"

#include "point.h"

#include <algorithm>
#include <cmath>
namespace edagl {
namespace core {

/* region Constructors / Destructor */
Rectangle::Rectangle() : x(0.0), y(0.0), h(0.0), w(0.0), angle(0.0) {}

Rectangle::Rectangle(double x, double y, double h, double w, double angle)
    : x(x), y(y), h(h), w(w), angle(angle) {}

Rectangle::Rectangle(const Rectangle& rhs) {
    x = rhs.x;
    y = rhs.y;
    h = rhs.h;
    w = rhs.w;
    angle = rhs.angle;
}

Rectangle& Rectangle::operator=(const Rectangle& rhs) {
    if (this == &rhs)  // 检查自我赋值
        return *this;
    // 执行赋值操作
    x = rhs.x;
    y = rhs.y;
    h = rhs.h;
    w = rhs.w;
    angle = rhs.angle;
    return *this;
}

bool Rectangle::operator==(const Rectangle& other) const {
    return (x == other.x && y == other.y && h == other.h && w == other.w);
}
/* endregion */

/* region General Methods */
Point Rectangle::topLeft() const {
    return {x, y};
}

Point Rectangle::topRight() const {
    double topRightX = x + w * std::cos(angle);
    double topRightY = y + w * sin(angle);
    return Point(topRightX, topRightY);
}

Point Rectangle::bottomLeft() const {
    double bottomLeftX = x - h * sin(angle);
    double bottomLeftY = y + h * cos(angle);
    return Point(bottomLeftX, bottomLeftY);
}

Point Rectangle::bottomRight() const {
    double bottomRightX = x + w * cos(angle) - h * sin(angle);
    double bottomRightY = y + w * sin(angle) + h * cos(angle);
    return Point(bottomRightX, bottomRightY);
}
/* endregion */
}  // namespace core
}  // namespace edagl
