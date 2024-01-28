#ifndef EDA_GL_INTERSECTION_H
#define EDA_GL_INTERSECTION_H

#include "core/point.h"

namespace core {
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

bool segArcIntersectPoints(const core::Point& aSegStart,
                           const core::Point& aSegEnd,
                           const core::Point& aArcStart,
                           const core::Point& aArcEnd,
                           const core::Point& aArcCenter, double aRadius,
                           double aStartAngle, double aEndAngle,
                           double aSweepAngle, bool aIsCW,
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
