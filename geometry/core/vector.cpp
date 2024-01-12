#include "vector.h"

#include "point.h"

namespace core {

    double dotProduct(const Vector2D &v1, const Vector2D &v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    double crossProduct(const Vector2D &v1, const Vector2D &v2) {
        return v1.x * v2.y - v1.y * v2.x;
    }

}