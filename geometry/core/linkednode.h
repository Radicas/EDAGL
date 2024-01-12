/**
 * @file linkednode.h
 * @author your name (you@domain.com)
 * @brief 圆弧多边形节点
 * @version 0.1
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef EDA_GL_LINKEDNODE_H
#define EDA_GL_LINKEDNODE_H

#include "point.h"

namespace core {
    class LinkedNode {
    public:
        Point data;      ///< 坐标
        bool tag;        ///< 是否附加点
        bool crossing;   ///< 是否交点
        bool ee;         ///< 是否进入点
        LinkedNode *pp;  ///< 前一个点
        LinkedNode *np;  ///< 后一点

        /* region Constructors / Destructor */
        LinkedNode();

        LinkedNode(const Point &data, bool tag, bool crossing, bool ee, LinkedNode *pp, LinkedNode *np);

        LinkedNode(const LinkedNode &rhs);

        LinkedNode &operator=(const LinkedNode &rhs) = default;

        LinkedNode(LinkedNode &&rhs) noexcept;

        LinkedNode &operator=(LinkedNode &&rhs) noexcept;
        /* endregion */

        /* region General Methods */
        bool operator==(const LinkedNode &rhs) const;
        /* endregion */
    };
} // namespace geometry

#endif // EDA_GL_LINKEDNODE_H
