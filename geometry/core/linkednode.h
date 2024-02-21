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

#include <vector>
#include "point.h"

namespace edagl {
namespace core {
class LinkedNode {
   public:
    Point mData;        ///< 坐标
    bool mIsAppendix;   ///< 是否附加点
    bool mIsCrossing;   ///< 是否交点
    bool mEE;           ///< 是否进入点
    LinkedNode* mPrev;  ///< 前一个节点
    LinkedNode* mNext;  ///< 后一个节点

    /* region Constructors / Destructor */
    LinkedNode();

    explicit LinkedNode(const Point& data);

    LinkedNode(const Point& aData, bool aIsAppendix, bool aIsCrossing, bool aEE,
               LinkedNode* aPrev, LinkedNode* aNext);

    LinkedNode(const LinkedNode& rhs);

    LinkedNode& operator=(const LinkedNode& rhs) = default;

    LinkedNode(LinkedNode&& rhs) noexcept;

    LinkedNode& operator=(LinkedNode&& rhs) noexcept;

    ~LinkedNode() = default;
    /* endregion */

    /* region General Methods */
    bool operator==(const LinkedNode& rhs) const;

    /**
     * @brief 根据路径创建链表
     *
     * @details
     *      如果传入的路径首尾是同一个，则会构建成环形双向链
     *      如果传入的路径首尾不是同一个，则会构建成普通双向链
     * @param aPath
     * @return LinkedNode* 环形链表头指针
     */
    static LinkedNode* constructLinkedNodes(const std::vector<Point>& aPath);

    friend std::ostream& operator<<(std::ostream& os, const LinkedNode* node) {
        os << "data: (" << node->mData.x << "," << node->mData.y << ")\n"
           << "appendix: " << node->mIsAppendix << "\n"
           << "crossing: " << node->mIsCrossing << "\n"
           << "ee: " << node->mEE;
        return os;
    }
    /* endregion */
};
}  // namespace core
}  // namespace edagl

#endif  // EDA_GL_LINKEDNODE_H
