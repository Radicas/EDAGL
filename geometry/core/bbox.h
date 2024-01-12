/**
 * @file bbox.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef EDA_GL_BBOX_H
#define EDA_GL_BBOX_H

namespace geometry {
    struct BBox {
        double x;      // 左上角 x 坐标
        double y;      // 左上角 y 坐标
        double width;  // 宽度
        double height; // 高度

        // 默认构造函数
        BBox() : x(0.0f), y(0.0f), width(0.0f), height(0.0f) {}

        // 带参数的构造函数
        BBox(float _x, float _y, float _width, float _height)
                : x(_x), y(_y), width(_width), height(_height) {}

        // 操作符重载：比较相等
        bool operator==(const BBox &other) const {
            return x == other.x && y == other.y && width == other.width && height == other.height;
        }

        // 操作符重载：比较不相等
        bool operator!=(const BBox &other) const {
            return !(*this == other);
        }
    };
} // namespace geometry

#endif // EDA_GL_BBOX_H
