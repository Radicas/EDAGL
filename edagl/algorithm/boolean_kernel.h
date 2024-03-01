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
class PolygonWithHoles;
class EventNode;
}  // namespace core
namespace algorithm {

typedef edagl::core::Point Point;
typedef edagl::core::ArcPolygon ArcPolygon;
typedef edagl::core::Edge Edge;
typedef edagl::core::EdgeNode EdgeNode;
typedef edagl::core::EventNode EventNode;
typedef edagl::core::PolygonWithHoles PolygonWithHoles;
typedef std::vector<PolygonWithHoles> PolygonsWithHoles;

struct CompareEdgePtr;

/**
 * @brief 运算策略
 */
enum class Traits { INTERSECTION = 0x1, UNION = 0x2, DIFFERENCE = 0x4 };

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
int relatedEdgesBetweenAxis(const ArcPolygon& aArcPolygon, double aAxisSmall,
                            double aAxisBig, bool aXAxis,
                            std::vector<Edge>& aRelatedEdge);

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
int pretreatment(const ArcPolygon& aArcPoly1, const ArcPolygon& aArcPoly2,
                 std::vector<EdgeNode>& aSequencedEdge1,
                 std::vector<EdgeNode>& aSequencedEdge2,
                 std::vector<Edge>& aRelatedEdge1,
                 std::vector<Edge>& aRelatedEdge2);

/**
 * @brief 初始化边域
 *
 * @param aSequencedEdge 边域引用
 * @param aRelatedEdge 相关边
 * @return 0 正常
 */
int initSequencedEdge(std::vector<EdgeNode>& aSequencedEdge,
                      const std::vector<Edge>& aRelatedEdge);

/**
 * @brief 利用扫描线算法重建序列边，将交点信息插入
 *
 * @param aSequencedEdge1
 * @param aSequencedEdge2
 */
void rebuildSequencedEdge(std::vector<EdgeNode>& aSequencedEdge1,
                          std::vector<EdgeNode>& aSequencedEdge2);

/**
 * @brief 将x单调圆弧分解为2-3个非x单调圆弧
 *
 * @param aEdge 圆弧边
 * @return 分解后的圆弧边
 */
std::vector<Edge> decomposeArc(const Edge& aEdge);

/**
 * @brief 将x单调圆弧分解为3个非x单调圆弧
 *
 * @param aEdge
 * @param aEast
 * @param aWest
 * @return
 */
std::vector<Edge> decomposeArcToThree(const Edge& aEdge, const Point& aEast,
                                      const Point& aWest);

/**
 * @brief 将x单调圆弧分解为2个非x单调圆弧
 *
 * @param aEdge
 * @param aBreakPoint
 * @return
 */
std::vector<Edge> decomposeArcToTwo(const Edge& aEdge,
                                    const Point& aBreakPoint);


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
PolygonsWithHoles booleanOperation(const ArcPolygon& ap1, const ArcPolygon& ap2,
                                   Traits traits);

}  // namespace algorithm
}  // namespace edagl

#endif  // EDA_GL_BOOLEAN_KERNEL_H
