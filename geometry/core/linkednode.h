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
#include <vector>

namespace core
{
    class LinkedNode
    {
    public:
        Point mData;       ///< 坐标
        bool mIsAppendix;  ///< 是否附加点
        bool mIsCrossing;  ///< 是否交点
        bool mEE;          ///< 是否进入点
        LinkedNode* mPrev; ///< 前一个点
        LinkedNode* mNext; ///< 后一点

        /* region Constructors / Destructor */
        LinkedNode();

        explicit LinkedNode(const Point& data);

        LinkedNode(const Point& data, bool tag, bool crossing, bool ee,
                   LinkedNode* pp, LinkedNode* np);

        LinkedNode(const LinkedNode& rhs);

        LinkedNode& operator=(const LinkedNode& rhs) = default;

        LinkedNode(LinkedNode&& rhs) noexcept;

        LinkedNode& operator=(LinkedNode&& rhs) noexcept;
        /* endregion */

        /* region General Methods */
        bool operator==(const LinkedNode& rhs) const;

        static LinkedNode*
        constructLinkedNodes(const std::vector<Point>& points);
        /* endregion */
    };
} // namespace core

#endif // EDA_GL_LINKEDNODE_H
