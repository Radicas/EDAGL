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

/**
 * @brief 
 * 
 */
class LinkedNode {
   public:
    Point mData;        ///< 坐标
    bool mIsAppendix;   ///< 是否附加点
    bool mIsCrossing;   ///< 是否交点
    bool mEE;           ///< 是否进入点
    LinkedNode* mPrev;  ///< 前一个节点
    LinkedNode* mNext;  ///< 后一个节点

    /* region Constructors / Destructor */

    /**
     * @brief Construct a new Linked Node object
     * 
     */
    LinkedNode();

    /**
     * @brief Construct a new Linked Node object
     * 
     * @param data 
     */
    explicit LinkedNode(const Point& data);

    /**
     * @brief Construct a new Linked Node object
     * 
     * @param aData 
     * @param aIsAppendix 
     * @param aIsCrossing 
     * @param aEE 
     * @param aPrev 
     * @param aNext 
     */
    LinkedNode(const Point& aData, bool aIsAppendix, bool aIsCrossing, bool aEE,
               LinkedNode* aPrev, LinkedNode* aNext);

    /**
     * @brief Construct a new Linked Node object
     * 
     * @param rhs 
     */
    LinkedNode(const LinkedNode& rhs);

    /**
     * @brief 
     * 
     * @param rhs 
     * @return LinkedNode& 
     */
    LinkedNode& operator=(const LinkedNode& rhs) = default;

    /**
     * @brief Construct a new Linked Node object
     * 
     * @param rhs 
     */
    LinkedNode(LinkedNode&& rhs) noexcept;

    /**
     * @brief 
     * 
     * @param rhs 
     * @return LinkedNode& 
     */
    LinkedNode& operator=(LinkedNode&& rhs) noexcept;

    /**
     * @brief Destroy the Linked Node object
     * 
     */
    ~LinkedNode() = default;
    /* endregion */

    /* region General Methods */
    /**
     * @brief 
     * 
     * @param rhs 
     * @return true 
     * @return false 
     */
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

    /**
     * @brief 
     * 
     * @param os 
     * @param node 
     * @return std::ostream& 
     */
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
