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
#include "core/point.h"

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

/********************************** Point *********************************/

/**
 * @brief 返回两点之间欧氏距离
 *        d = √((x2 - x1)² + (y2 - y1)²)
 * @param aP1 点1
 * @param aP2 点2
 * @return double 两点之间欧氏距离
 */
double pointsDistance(const core::Point& aP1, const core::Point& aP2);

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

/****************************** Circle / Arc ******************************/
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
bool detached(const core::BBox& aBBox1, const core::BBox& aBBox2);

bool contains(const core::BBox& aBBox1, const core::BBox& aBBox2);

int unionBBoxes(const core::BBox& aBBox1, const core::BBox& aBBox2,
                core::BBox& aResult);
}  // namespace geometry

#endif  // EDA_GL_GEOMETRY_H
