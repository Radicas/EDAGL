/**
 * @file intersection.h
 * @author Radica
 * @brief 
 * @version 0.1
 * @date 2024-02-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef EDA_GL_INTERSECTION_H
#define EDA_GL_INTERSECTION_H

#include <vector>
#include "core/point.h"
namespace edagl {
namespace core {
class Edge;
class BBox;
}  // namespace core
}  // namespace edagl

namespace edagl {
namespace geometry {

typedef edagl::core::Point Point;
typedef edagl::core::Edge Edge;
typedef edagl::core::BBox BBox;

/********************************** Segment **********************************/

/**
 * @brief 判断线段和线段是否相交(包括端点)
 * @details 排斥实验 + 跨立实验
 * @note 注意，重合的线段也认为是相交
 * @param aS1
 * @param aE1
 * @param aS2
 * @param aE2
 * @return
 */
bool isSegSegIntersect(const Point& aS1, const Point& aE1, const Point& aS2,
                       const Point& aE2);

/**
 * @brief 判断线段和圆是否相交(包括端点)
 *
 * @param aSegStart
 * @param aSegEnd
 * @param aCenter
 * @param aRadius
 * @return
 */
bool isSegCircleIntersect(const Point& aSegStart, const Point& aSegEnd,
                          const Point& aCenter, double aRadius);

/**
 * @brief 获取线段和线段交点(包含端点)
 * @param aSegStart1
 * @param aSegEnd1
 * @param aSegStart2
 * @param aSegEnd2
 * @param aResult
 * @return
 */
bool segSegIntersectPoint(const Point& aSegStart1, const Point& aSegEnd1,
                          const Point& aSegStart2, const Point& aSegEnd2,
                          Point& aResult);

/********************************** Arc **********************************/

/**
 * @brief 求线段和圆弧交点(包括端点)
 *
 * @param aSegStart
 * @param aSegEnd
 * @param aArcCenter
 * @param aRadius
 * @param aStartAngle
 * @param aSweepAngle
 * @param aIsCW
 * @param aResult
 * @return
 */
bool segArcIntersectPoints(const Point& aSegStart, const Point& aSegEnd,
                           const Point& aArcCenter, double aRadius,
                           double aStartAngle, double aSweepAngle, bool aIsCW,
                           std::vector<Point>& aResult);

/**
 * @brief 求圆弧和圆弧的交点(包括端点)
 *
 * @param aCenter1
 * @param aRadius1
 * @param aStartAngle1
 * @param aSweepAngle1
 * @param aIsCW1
 * @param aCenter2
 * @param aRadius2
 * @param aStartAngle2
 * @param aSweepAngle2
 * @param aIsCW2
 * @return
 */
bool arcArcIntersectPoints(const Point& aCenter1, double aRadius1,
                           double aStartAngle1, double aSweepAngle1,
                           bool aIsCW1, const Point& aCenter2, double aRadius2,
                           double aStartAngle2, double aSweepAngle2,
                           bool aIsCW2, std::vector<Point>& aResult);

/*********************************** Edge ***********************************/

/**
 * @brief 求边和边的交点(包括端点)
 *
 * @param aEdge1
 * @param aEdge2
 * @param aResult
 * @return
 */
bool edgeEdgeIntersectPoints(const Edge& aEdge1, const Edge& aEdge2,
                             std::vector<Point>& aResult);

/********************************** Circle **********************************/

/**
 * @brief 求线段和圆弧的交点
 *
 * @param aSegStart
 * @param aSegEnd
 * @param aCenter
 * @param aRadius
 * @param aResult
 * @return
 */
bool segCircleIntersectPoints(const Point& aSegStart, const Point& aSegEnd,
                              const Point& aCenter, double aRadius,
                              std::vector<Point>& aResult);

bool lineCircleIntersectPoints(double A, double B, double C,
                               const Point& aCenter, double aRadius,
                               std::vector<Point>& aResult);

/**
 * @brief 求圆和圆交点
 *
 * @param aCenter1
 * @param aRadius1
 * @param aCenter2
 * @param aRadius2
 * @param aResult
 * @return
 */
bool circleCircleIntersectPoints(const Point& aCenter1, double aRadius1,
                                 const Point& aCenter2, double aRadius2,
                                 std::vector<Point>& aResult);

/********************************** BBOx **********************************/

/**
 * @brief 求出两个包围盒相交部分的包围盒
 *
 * @param aBBox1
 * @param aBBox2
 * @param aResult
 * @return
 */
int intersectsBBoxes(const BBox& aBBox1, const BBox& aBBox2, BBox& aResult);

}  // namespace geometry
}  // namespace edagl

#endif  //EDA_GL_INTERSECTION_H
