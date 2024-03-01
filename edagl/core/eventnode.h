/**
 * @file eventnode.h
 * @author Radica
 * @brief 
 * @version 0.1
 * @date 2024-02-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef EDA_GL_EVENTNODE_H
#define EDA_GL_EVENTNODE_H

#include "point.h"

namespace edagl {
namespace core {
class Edge;
class Point;

/**
 * @brief 
 * 
 */
class EventNode {
   public:
    /**
    * @brief 事件基于线段或弧线的位置
    */
    enum class EventPosition { LEFT = 0x1, RIGHT = 0x2, INTERSECT = 0x4 };

    EventPosition mPosition;  ///< 事件位置
    Point mPoint;             ///< 坐标点指针
    Edge* mEdge;              ///< 属于的边
    Edge* mAnotherEdge;       ///< 属于的另一个边(可能为空)
    bool mIsVertical;         ///< 是否来自垂直边

    /**
     * @brief
     *
     * @param rhs
     */
    EventNode(const EventNode& rhs);

    /**
     *
     * @param edge
     * @return
     */
    static EventNode createLeft(Edge* edge);

    /**
     *
     * @param edge
     * @return
     */
    static EventNode createRight(Edge* edge);

    static EventNode createIntersect(Edge* edge, Edge* another, const Point& point);

    /**
     * @brief 比较重载
     * @param rhs
     * @return true
     * @return false
     */
    bool operator<(const EventNode& rhs) const;

   private:
    /**
     *
     * @param edge
     */
    explicit EventNode(Edge* edge);
};
}  // namespace core
}  // namespace edagl

#endif  //EDA_GL_EVENTNODE_H
