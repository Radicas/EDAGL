#include "geometry.h"
#include "core/point.h"
#include <algorithm>
#include <cmath>

using namespace core;
namespace geometry {
static double EPSILON = 1E-10;

/********************************* Vector *********************************/

double dotProduct(const core::Point &aS, const core::Point &aE,
                  const core::Point &aO) {
  return (aS.x - aO.x) * (aE.x - aO.x) + (aS.y - aO.y) * (aE.y - aO.y);
}

double dotProduct(const core::Vector2D &aVec1, const core::Vector2D &aVec2) {
  return aVec1.x * aVec2.x + aVec1.y * aVec2.y;
}

double crossProduct(const core::Point &aS, const core::Point &aE,
                    const core::Point &aO) {
  return (aS.x - aO.x) * (aE.y - aO.y) - (aE.x - aO.x) * (aS.y - aO.y);
}

double crossProduct(const core::Vector2D &aVec1, const core::Vector2D &aVec2) {
  return aVec1.x * aVec2.y - aVec1.y * aVec2.x;
}
/********************************** Point *********************************/

bool isCollinear(const core::Point &aP1, const core::Point &aP2,
                 const core::Point &aP3) {
  return std::abs(crossProduct(aP1, aP2, aP3) - 0.0) < EPSILON;
}

double pointsDistance(const core::Point &aP1, const core::Point &aP2) {
  return std::sqrt((aP1.x - aP2.x) * (aP1.x - aP2.x) +
                   (aP1.y - aP2.y) * (aP1.y - aP2.y));
}
/****************************** Circle / Arc ******************************/

void circleFrom3Points(const Point &aP1, const Point &aP2, const Point &aP3,
                       Point &aCenter, double &aRadius) {
  if (isCollinear(aP1, aP2, aP3)) {
    std::cerr << "[error] three points are Collinear" << __FILE__ << __LINE__
              << std::endl;
    aRadius = 0.0;
    return;
  }
  double x1 = aP1.x;
  double y1 = aP1.y;
  double x2 = aP2.x;
  double y2 = aP2.y;
  double x3 = aP3.x;
  double y3 = aP3.y;

  double A = x1 * (y2 - y3) - y1 * (x2 - x3) + x2 * y3 - x3 * y2;
  double B = (x1 * x1 + y1 * y1) * (y3 - y2) + (x2 * x2 + y2 * y2) * (y1 - y3) +
             (x3 * x3 + y3 * y3) * (y2 - y1);
  double C = (x1 * x1 + y1 * y1) * (x2 - x3) + (x2 * x2 + y2 * y2) * (x3 - x1) +
             (x3 * x3 + y3 * y3) * (x1 - x2);
  double D = (x1 * x1 + y1 * y1) * (x3 * y2 - x2 * y3) +
             (x2 * x2 + y2 * y2) * (x1 * y3 - x3 * y1) +
             (x3 * x3 + y3 * y3) * (x2 * y1 - x1 * y2);

  double centerX = -B / (2 * A);
  double centerY = -C / (2 * A);
  double radius = std::sqrt((B * B + C * C - 4 * A * D) / (4 * A * A));

  aCenter.x = centerX;
  aCenter.y = centerY;
  aRadius = radius;
}

BBox bBoxOfArc(const Point &A, const Point &B, const Point &M) {
  Point t;
  double r;
  circleFrom3Points(A, B, M, t, r);
  if (r == 0.0) {
    return {};
  }
  BBox result;
  // 求圆心和半径
  Point center{};
  double radius{};
  circleFrom3Points(A, B, M, center, radius);

  // 初始化圆东北西南四个点
  Point E(center.x + radius, center.y);
  Point N(center.x, center.y + radius);
  Point W(center.x - radius, center.y);
  Point S(center.x, center.y - radius);

  // 计算三角形的有向面积
  double ABM =
      (A.x * (B.y - M.y) + B.x * (M.y - A.y) + M.x * (A.y - B.y)) * 0.5;
  double ABE =
      (A.x * (B.y - E.y) + B.x * (E.y - A.y) + E.x * (A.y - B.y)) * 0.5;
  double ABN =
      (A.x * (B.y - N.y) + B.x * (N.y - A.y) + N.x * (A.y - B.y)) * 0.5;
  double ABW =
      (A.x * (B.y - W.y) + B.x * (W.y - A.y) + W.x * (A.y - B.y)) * 0.5;
  double ABS =
      (A.x * (B.y - S.y) + B.x * (S.y - A.y) + S.x * (A.y - B.y)) * 0.5;

  if (ABM * ABE > 0) {
    result.setMaxX(E.x);
  } else {
    result.setMaxX(std::max(A.x, B.x));
  }

  if (ABM * ABN > 0) {
    result.setMaxY(N.y);
  } else {
    result.setMaxY(std::max(A.y, B.y));
  }

  if (ABM * ABW > 0) {
    result.setMinX(W.x);
  } else {
    result.setMinX(std::min(A.x, B.x));
  }

  if (ABM * ABS > 0) {
    result.setMinY(S.y);
  } else {
    result.setMinY(std::min(A.y, B.y));
  }
  return result;
}
/********************************** BBOx *********************************/

bool detached(const BBox &aBBox1, const BBox &aBBox2) {
  // 排斥实验，检查两者是否相离
  return (aBBox1.getMaxX() < aBBox2.getMinX() ||
          aBBox1.getMaxY() < aBBox2.getMinY() ||
          aBBox2.getMaxX() < aBBox1.getMinX() ||
          aBBox2.getMaxY() < aBBox1.getMinY());
}

bool contains(const BBox &aBBox1, const BBox &aBBox2) {
  // 检查两者是否包含关系
  return ((aBBox1.getMinX() < aBBox2.getMinX() &&
           aBBox2.getMaxX() < aBBox1.getMaxX() &&
           aBBox1.getMinY() < aBBox2.getMinY() &&
           aBBox2.getMaxY() < aBBox1.getMaxY()) ||
          (aBBox2.getMinX() < aBBox1.getMinX() &&
           aBBox1.getMaxX() < aBBox2.getMaxX() &&
           aBBox2.getMinY() < aBBox1.getMinY() &&
           aBBox1.getMaxY() < aBBox2.getMaxY()));
}

int unionBBoxes(const core::BBox &aBBox1, const core::BBox &aBBox2,
                core::BBox &aResult) {
  // 检查两个BBox是否相离或包含
  if (detached(aBBox1, aBBox2) || contains(aBBox1, aBBox2)) {
    return 1; // 返回状态1
  }
  // 得到新的相交的BBox
  aResult.setMinX(std::max(aBBox1.getMinX(), aBBox2.getMinX()));
  aResult.setMinY(std::max(aBBox1.getMinY(), aBBox2.getMinY()));
  aResult.setMaxX(std::min(aBBox1.getMaxX(), aBBox2.getMaxX()));
  aResult.setMaxY(std::min(aBBox1.getMaxY(), aBBox2.getMaxY()));
  return 0; // 返回状态0
}

} // namespace geometry
