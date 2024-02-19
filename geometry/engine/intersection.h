#ifndef EDA_GL_INTERSECTION_H
#define EDA_GL_INTERSECTION_H

#include "core/point.h"
#include <vector>
namespace core {
class Edge;
class BBox;
}  // namespace core

namespace geometry {

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
bool isSegSegIntersect(const core::Point& aS1, const core::Point& aE1,
                       const core::Point& aS2, const core::Point& aE2);

/**
 * @brief 判断线段和圆是否相交(包括端点)
 *
 * @param aSegStart
 * @param aSegEnd
 * @param aCenter
 * @param aRadius
 * @return
 */
bool isSegCircleIntersect(const core::Point& aSegStart,
                          const core::Point& aSegEnd,
                          const core::Point& aCenter, double aRadius);

/**
 * @brief 获取线段和线段交点(包含端点)
 * @param aSegStart1
 * @param aSegEnd1
 * @param aSegStart2
 * @param aSegEnd2
 * @param aResult
 * @return
 */
bool segSegIntersectPoint(const core::Point& aSegStart1,
                          const core::Point& aSegEnd1,
                          const core::Point& aSegStart2,
                          const core::Point& aSegEnd2, core::Point& aResult);

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
bool segArcIntersectPoints(const core::Point& aSegStart,
                           const core::Point& aSegEnd,
                           const core::Point& aArcCenter, double aRadius,
                           double aStartAngle, double aSweepAngle, bool aIsCW,
                           std::vector<core::Point>& aResult);

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
bool arcArcIntersectPoints(const core::Point& aCenter1, double aRadius1,
                           double aStartAngle1, double aSweepAngle1,
                           bool aIsCW1, const core::Point& aCenter2,
                           double aRadius2, double aStartAngle2,
                           double aSweepAngle2, bool aIsCW2,
                           std::vector<core::Point>& aResult);

/*********************************** Edge ***********************************/

/**
 * @brief 求边和边的交点(包括端点)
 *
 * @param aEdge1
 * @param aEdge2
 * @param aResult
 * @return
 */
bool edgeEdgeIntersectPoints(const core::Edge& aEdge1, const core::Edge& aEdge2,
                             std::vector<core::Point>& aResult);

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
bool segCircleIntersectPoints(const core::Point& aSegStart,
                              const core::Point& aSegEnd,
                              const core::Point& aCenter, double aRadius,
                              std::vector<core::Point>& aResult);

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
bool circleCircleIntersectPoints(const core::Point& aCenter1, double aRadius1,
                                 const core::Point& aCenter2, double aRadius2,
                                 std::vector<core::Point>& aResult);

/********************************** BBOx **********************************/

/**
 * @brief 求出两个包围盒相交部分的包围盒
 *
 * @param aBBox1
 * @param aBBox2
 * @param aResult
 * @return
 */
int intersectsBBoxes(const core::BBox& aBBox1, const core::BBox& aBBox2,
                     core::BBox& aResult);

}  // namespace geometry

#endif  //EDA_GL_INTERSECTION_H
