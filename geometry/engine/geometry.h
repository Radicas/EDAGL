/**
 * @file geometry.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef EDA_GL_GEOMETRY_H
#define EDA_GL_GEOMETRY_H

#include "core/bbox.h"
#include "core/edge.h"
#include "core/point.h"
#include "global.h"

namespace geometry {

/********************************* Vector *********************************/

/**
 * @brief 向量的点积
 *
 * @details
 *      OS * OE
 *      r<0：两个向量相反，钝角
 *      r=0：两个向量垂直，直角
 *      r>0：两个向量同向，锐角
 * @param aS
 * @param aE
 * @param aO
 * @return 点积结果
 */
double dotProduct(const core::Point& aS, const core::Point& aE,
                  const core::Point& aO);

/**
 * @brief 向量的点积
 *
 * @details
 *      aVec1 * aVec2
 *      r<0：两个向量相反，钝角
 *      r=0：两个向量垂直，直角
 *      r>0：两个向量同向，锐角
 * @param aVec1
 * @param aVec2
 * @return 点积结果
 */
double dotProduct(const core::Vector2D& aVec1, const core::Vector2D& aVec2);

/**
 * @brief 向量的差积
 *
 * @details
 *      OS X OE
 *      r>0：ep在矢量 op sp 的逆时针方向
 *      r=0：op sp ep 三点共线
 *      r<0：ep在矢量 op sp 的顺时针方向
 * @param aS
 * @param aE
 * @param aO
 * @return double
 */
double crossProduct(const core::Point& aS, const core::Point& aE,
                    const core::Point& aO);

/**
 * @brief 向量的差积
 *
 * @details
 *      aVec1 X aVec2
 * @param aVec1
 * @param aVec2
 * @return double
 */
double crossProduct(const core::Vector2D& aVec1, const core::Vector2D& aVec2);

/**
 * @brief 向量归一化
 *
 * @param aVector
 * @return
 */
core::Vector2D normalized(const core::Vector2D& aVector);

/**
 * @brief 向量归一化
 *
 * @param aStart
 * @param aEnd
 * @return
 */
core::Vector2D normalized(const core::Point& aStart, const core::Point& aEnd);

/******************************** Point / Seg *******************************/

/**
 * @brief 三点共线判断
 *
 * @param aP1
 * @param aP2
 * @param aP3
 * @return true 共线
 * @return false 不共线
 */
bool isCollinear(const core::Point& aP1, const core::Point& aP2,
                 const core::Point& aP3);

/**
 * @brief 判断点与线段的关系,用途很广泛
 *        本函数是根据下面的公式写的，P是点C到线段AB所在直线的垂足
 *                       AC dot AB
 *        r =            ---------
 *                       ||AB||^2
 *             (Cx-Ax)(Bx-Ax) + (Cy-Ay)(By-Ay)
 *          = -------------------------------
 *                          L^2
 *        r 有下列含义:
 *          r=0    P = A
 *          r=1    P = B
 *          r<0    P 在AB的背面延伸
 *          r>1    P 在AB的前方延伸
 *          0<r<1  P 在AB范围内
 *
 * @param p
 * @param l
 * @return double
 */
double relationPointAndSeg(const core::Point& aPoint,
                           const core::Point& aSegStart,
                           const core::Point& aSegEnd);

/**
 * @brief 点到线段所在直线垂足
 *
 * @param aPoint
 * @param aSegStart
 * @param aSegEnd
 * @return
 */
core::Point perpendicular(const core::Point& aPoint,
                          const core::Point& aSegStart,
                          const core::Point& aSegEnd);

/**
 * @brief 返回两点之间欧氏距离
 *        d = √((x2 - x1)² + (y2 - y1)²)
 * @param aP1 点1
 * @param aP2 点2
 * @return double 两点之间欧氏距离
 */
double distancePoint2Point(const core::Point& aP1, const core::Point& aP2);

/**
 * @brief 点到线段所在直线最短距离
 * @param aPoint
 * @param aSegStart
 * @param aSegEnd
 * @return
 */
double distancePoint2Line(const core::Point& aPoint,
                          const core::Point& aSegStart,
                          const core::Point& aSegEnd);

/**
 * @brief 点到线段最短距离
 * @param aPoint
 * @param aSegStart
 * @param aSegEnd
 * @return
 */
double distancePoint2Seg(const core::Point& aPoint,
                         const core::Point& aSegStart,
                         const core::Point& aSegEnd);

/**
 * @brief 判断点是否在线段上(包括端点)
 *
 * @param aPoint
 * @param aSegStart
 * @param aSegEnd
 * @return
 */
bool isPointOnSegment(const core::Point& aPoint, const core::Point& aSegStart,
                      const core::Point& aSegEnd);

/****************************** Circle / Arc ******************************/

/**
 * @brief 获取圆弧半径
 *
 * @param aEndPoint
 * @param aCenterPoint
 * @return
 */
double arcRadius(const core::Point& aEndPoint, const core::Point& aCenterPoint);

/**
 * @brief 获取圆弧起始角度，弧度
 *
 * @param aStart
 * @param aCenter
 * @return
 */
double arcStartAngle(const core::Point& aStart, const core::Point& aCenter);

/**
 * @brief 获取圆弧终止角度，弧度
 *
 * @param aEnd
 * @param aCenter
 * @return
 */
double arcEndAngle(const core::Point& aEnd, const core::Point& aCenter);

/**
 * @brief 获取圆弧偏转角度，弧度
 *
 * @param aStartAngle
 * @param endAngle
 * @param aIsCW
 * @return
 */
double arcSweepAngle(double aStartAngle, double endAngle, bool aIsCW);

/**
 * @brief 获取圆弧中点
 *
 * @param aStart
 * @param aEnd
 * @param aCenter
 * @param aIsCW
 * @return
 */
core::Point midPointOfArc(const core::Point& aStart, const core::Point& aEnd,
                          const core::Point& aCenter, bool aIsCW);

/**
 * @brief 获取圆弧中点
 *
 * @param aStartAngle
 * @param aEndAngle
 * @param aRadius
 * @param aCenter
 * @param aIsCW
 * @return
 */
core::Point midPointOfArc(double aStartAngle, double aEndAngle, double aRadius,
                          const core::Point& aCenter, bool aIsCW);

/**
 * @brief 判断点是否在圆弧射线范围内(包含边)
 *
 * @param aStart
 * @param aCenter
 * @param aStartAngle
 * @param aSweepAngle
 * @param aIsCW
 * @return
 */
bool isPointInArcRange(const core::Point& aCenter, double aStartAngle,
                       double aSweepAngle, bool aIsCW,
                       const core::Point& aTarget);

/**
 * @brief 判断点是否在圆弧射线范围内(不包含边)
 *
 * @param aStart
 * @param aCenter
 * @param aStartAngle
 * @param aSweepAngle
 * @param aIsCW
 * @return
 */
bool isPointInArcRangeExceptEdge(const core::Point& aCenter, double aStartAngle,
                                 double aSweepAngle, bool aIsCW,
                                 const core::Point& aTarget);

/**
 * @brief 判断是否X单调圆弧
 *
 * @param aStart
 * @param aEnd
 * @param aCenter
 * @param aSweepAngle
 * @return
 */
bool isXMonotoneArc(const core::Point& aStart, const core::Point& aEnd,
                    const core::Point& aCenter, double aSweepAngle);

/**
 * @brief 判断是否Y单调圆弧(未开发)
 *
 * @param aStart
 * @param aEnd
 * @param aCenter
 * @return
 */
bool isYMonotoneArc(const core::Point& aStart, const core::Point& aEnd,
                    const core::Point& aCenter);

/**
 * @brief 根据圆上三点计算出圆心和半径
 *
 * @param aP1
 * @param aP2
 * @param aP3
 * @param aCenter
 * @param aRadius
 */
void circleFrom3Points(const core::Point& aP1, const core::Point& aP2,
                       const core::Point& aP3, core::Point& aCenter,
                       double& aRadius);

/**
 * @brief 获取圆弧段的BBox
 * @details
 *        本函数思想来自：https://stackoverflow.com/questions/77798747/how-to-calculate-the-bounding-box-of-an-arc
 * @param A
 * @param B
 * @param M
 * @return 圆弧的BBox
 */
core::BBox bBoxOfArc(const core::Point& A, const core::Point& B,
                     const core::Point& M);

/********************************** BBOx **********************************/

/**
 * @brief 两个包围盒相离
 *
 * @param aBBox1
 * @param aBBox2
 * @return
 */
bool detached(const core::BBox& aBBox1, const core::BBox& aBBox2);

/**
 * @brief 两个包围盒有包含关系
 *
 * @param aBBox1
 * @param aBBox2
 * @return
 */
bool contains(const core::BBox& aBBox1, const core::BBox& aBBox2);

}  // namespace geometry

#endif  // EDA_GL_GEOMETRY_H
