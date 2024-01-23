/**
 * @file boolean.h
 * @author your name (you@domain.com)
 * @brief 多边形(带圆弧)布尔运算
 * @version 0.1
 * @date 2024-01-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef EDA_GL_BOOLEAN_H
#define EDA_GL_BOOLEAN_H

#include <vector>

namespace core {
class LinkedNode;
class Point;
class Edge;
class EdgeNode;

class ArcPolygon;
}  // namespace core
namespace algorithm {

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
int relatedEdgesBetweenAxis(core::ArcPolygon* aArcPolygon, double aAxisSmall,
                            double aAxisBig, bool aXAxis,
                            std::vector<core::Edge>& aRelatedEdge);

/**
 * @brief 圆弧多边形链表前处理
 *
 * @note 此接口只处理圆弧多边形相交的情况
 * @param aArcPoly1 圆弧多边形1
 * @param aArcPoly2 圆弧多边形2
 * @param aEdgeDomain1 相关边域1
 * @param aEdgeDomain2 相关边域2
 * @param aRelatedEdge1 相关边1
 * @param aRelatedEdge2 相关边1
 * @return 0 处理正常
 */
int arcPolyPretreatment(core::ArcPolygon* aArcPoly1,
                        core::ArcPolygon* aArcPoly2,
                        std::vector<core::EdgeNode>& aEdgeDomain1,
                        std::vector<core::EdgeNode>& aEdgeDomain2,
                        std::vector<core::Edge>& aRelatedEdge1,
                        std::vector<core::Edge>& aRelatedEdge2);

/**
 * @brief 初始化边域
 *
 * @param aSequencedEdge 边域引用
 * @param aRelatedEdge 相关边
 * @return 0 正常
 */
int initSequencedEdge(std::vector<core::EdgeNode>& aSequencedEdge,
                      const std::vector<core::Edge>& aRelatedEdge);

/**
 * @brief 将x单调圆弧分解为2-3个非x单调圆弧
 *
 * @param aEdge 圆弧边
 * @return 分解后的圆弧边
 */
std::vector<core::Edge> decomposeArc(const core::Edge& aEdge);

/**
 * @brief 将x单调圆弧分解为3个非x单调圆弧
 *
 * @param aEdge
 * @param aEast
 * @param aWest
 * @return
 */
std::vector<core::Edge> decomposeArcToThree(const core::Edge& aEdge,
                                            const core::Point& aEast,
                                            const core::Point& aWest);

/**
 * @brief 将x单调圆弧分解为2个非x单调圆弧
 *
 * @param aEdge
 * @param aBreakPoint
 * @return
 */
std::vector<core::Edge> decomposeArcToTwo(const core::Edge& aEdge,
                                          const core::Point& aBreakPoint);

/**
 * @brief 构建处理过的圆弧多边形
 *
 * @return
 */
int constructProcessedArcPolygon();

}  // namespace algorithm

#endif  // EDA_GL_BOOLEAN_H
