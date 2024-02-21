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

#include "core/edgenode.h"

namespace edagl {
namespace core {
class Point;

/**
 * @brief 节点基于线段或弧线的位置
 */
enum class NodePosition { LEFT = 0x0, RIGHT = 0x2, INTERSECT = 0x4 };

/**
 * @brief 
 * 
 */
struct EventNode {
    Point mPoint;            ///< 坐标点
    NodePosition mPosition;  ///< 事件节点的位置
    EdgeNode* mEdgeNode;     ///< 属于的边
    EdgeNode* mAnotherNode;  ///< 属于的另一个边(可能为空)

    EventNode();

    /**
     * @brief 比较重载
     * @param rhs
     * @return true
     * @return false
     */
    bool operator<(const EventNode& rhs) const;
};
}  // namespace core
}  // namespace edagl

#endif  //EDA_GL_EVENTNODE_H
