//
// Created by Radica on 2024/1/9.
//

#ifndef EDA_GL_VECTOR_H
#define EDA_GL_VECTOR_H

namespace core {

    class Point;

    typedef Point Vector2D;

    double dotProduct(const Vector2D& v1, const Vector2D& v2);

    double crossProduct(const Vector2D& v1, const Vector2D& v2);
} // namespace core

#endif //EDA_GL_VECTOR_H
