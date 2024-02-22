/**
 * @file boolean_kernel.h
 * @author Radica
 * @brief 布尔运算内核
 * @version 0.1
 * @date 2024-02-21
 * 
 * @copyright Copyright (c) 2024 
 * 
 */
#ifndef EDA_GL_BOOLEAN_KERNEL_H
#define EDA_GL_BOOLEAN_KERNEL_H

#include <queue>
#include <set>
#include <vector>

namespace edagl {
namespace core {
class LinkedNode;
class Point;
class Edge;
class EdgeNode;
class ArcPolygon;
class EventNode;
}  // namespace core
namespace algorithm {

/**
 * @brief 运算策略
 */
enum class Traits { INTERSECTION = 0x2, UNION = 0x4, DIFFERENCE = 0x8 };

/**
 * @brief 根据有效轴获取圆弧多边形的相关边
 *
 * @details
 * @param aArcPolygon 圆弧多边形
 * @param aAxisSmall 有效轴较小的值
 * @param aAxisBig 有效轴较大的值
 * @param aXAxis 有效轴是否X轴
 * @param aRelatedEdge 相关边结果
 * @return 0 执行正常
 */
int relatedEdgesBetweenAxis(const edagl::core::ArcPolygon& aArcPolygon,
                            double aAxisSmall, double aAxisBig, bool aXAxis,
                            std::vector<edagl::core::Edge>& aRelatedEdge);

/**
 * @brief 圆弧多边形预处理
 *
 * @param aArcPoly1 圆弧多边形链表1
 * @param aArcPoly2 圆弧多边形链表2
 * @param aSequencedEdge1 序列边1
 * @param aSequencedEdge2 序列边2
 * @param aRelatedEdge1 相关边1
 * @param aRelatedEdge2 相关边2
 * @return 0
 */
int pretreatment(const edagl::core::ArcPolygon& aArcPoly1,
                 const edagl::core::ArcPolygon& aArcPoly2,
                 std::vector<edagl::core::EdgeNode>& aSequencedEdge1,
                 std::vector<edagl::core::EdgeNode>& aSequencedEdge2,
                 std::vector<edagl::core::Edge>& aRelatedEdge1,
                 std::vector<edagl::core::Edge>& aRelatedEdge2);

/**
 * @brief 初始化边域
 *
 * @param aSequencedEdge 边域引用
 * @param aRelatedEdge 相关边
 * @return 0 正常
 */
int initSequencedEdge(std::vector<edagl::core::EdgeNode>& aSequencedEdge,
                      const std::vector<edagl::core::Edge>& aRelatedEdge);

/**
 * @brief 利用扫描线算法重建序列边，将交点信息插入
 *
 * @param aSequencedEdge1
 * @param aSequencedEdge2
 */
void rebuildSequencedEdge(std::vector<edagl::core::EdgeNode>& aSequencedEdge1,
                          std::vector<edagl::core::EdgeNode>& aSequencedEdge2);

/**
 * @brief 将x单调圆弧分解为2-3个非x单调圆弧
 *
 * @param aEdge 圆弧边
 * @return 分解后的圆弧边
 */
std::vector<edagl::core::Edge> decomposeArc(const edagl::core::Edge& aEdge);

/**
 * @brief 将x单调圆弧分解为3个非x单调圆弧
 *
 * @param aEdge
 * @param aEast
 * @param aWest
 * @return
 */
std::vector<edagl::core::Edge> decomposeArcToThree(
    const edagl::core::Edge& aEdge, const edagl::core::Point& aEast,
    const edagl::core::Point& aWest);

/**
 * @brief 将x单调圆弧分解为2个非x单调圆弧
 *
 * @param aEdge
 * @param aBreakPoint
 * @return
 */
std::vector<edagl::core::Edge> decomposeArcToTwo(
    const edagl::core::Edge& aEdge, const edagl::core::Point& aBreakPoint);

/**
 * @brief 处理左节点
 *
 * @param aRbTree
 * @param aEventNode
 */
void handleLeftNode(std::set<edagl::core::EdgeNode*>& aRbTree,
                    std::priority_queue<edagl::core::EventNode>& aPQueue,
                    edagl::core::EventNode& aEventNode);

/**
 * @brief 处理右节点
 *
 * @param aRbTree
 * @param aEventNode
 */
void handleRightNode(std::set<edagl::core::EdgeNode*>& aRbTree,
                     std::priority_queue<edagl::core::EventNode>& aPQueue,
                     edagl::core::EventNode& aEventNode);

/**
 * @brief 处理交点节点
 *
 * @param aRbTree
 * @param aEventNode
 */
void handleIntersectNode(std::set<edagl::core::EdgeNode*>& aRbTree,
                         std::priority_queue<edagl::core::EventNode>& aPQueue,
                         edagl::core::EventNode& aEventNode);

/**
 * @brief 构建处理过的圆弧多边形
 *
 * @return
 */
int constructProcessedArcPolygon();

/**
 *
 * @param ap1
 * @param ap2
 * @param traits
 * @return
 */
std::vector<core::ArcPolygon> booleanOperation(const core::ArcPolygon& ap1,
                                               const core::ArcPolygon& ap2,
                                               Traits traits);

}  // namespace algorithm
}  // namespace edagl

#endif  // EDA_GL_BOOLEAN_KERNEL_H
