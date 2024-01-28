#include "geometry.h"
#include <algorithm>
#include <cmath>
#include "core/point.h"

using namespace core;
namespace geometry {

/********************************* Vector *********************************/

double dotProduct(const Point& aS, const Point& aE, const Point& aO) {
    return (aS.x - aO.x) * (aE.x - aO.x) + (aS.y - aO.y) * (aE.y - aO.y);
}

double dotProduct(const Vector2D& aVec1, const Vector2D& aVec2) {
    return aVec1.x * aVec2.x + aVec1.y * aVec2.y;
}

double crossProduct(const Point& aS, const Point& aE, const Point& aO) {
    return (aS.x - aO.x) * (aE.y - aO.y) - (aE.x - aO.x) * (aS.y - aO.y);
}

double crossProduct(const Vector2D& aVec1, const Vector2D& aVec2) {
    return aVec1.x * aVec2.y - aVec1.y * aVec2.x;
}

core::Vector2D normalized(const core::Vector2D& aVector) {
    double l = aVector.length();
    return {aVector.x / l, aVector.y / l};
}

core::Vector2D normalized(const core::Point& aStart, const core::Point& aEnd) {
    return normalized(aEnd - aStart);
}

/********************************** Point *********************************/

bool isCollinear(const Point& aP1, const Point& aP2, const Point& aP3) {
    return std::abs(crossProduct(aP1, aP2, aP3) - 0.0) < EPSILON;
}

double relationPointAndSeg(const Point& aPoint, const Point& aSegStart,
                           const Point& aSegEnd) {
    return dotProduct(aPoint, aSegEnd, aSegStart) /
           (distancePoint2Point(aSegStart, aSegEnd) *
            distancePoint2Point(aSegStart, aSegEnd));
}

Point perpendicular(const Point& aPoint, const Point& aSegStart,
                    const Point& aSegEnd) {
    double r = relationPointAndSeg(aPoint, aSegStart, aSegEnd);
    Point p;
    p.x = aSegStart.x + r * (aSegEnd.x - aSegStart.x);
    p.y = aSegStart.y + r * (aSegEnd.y - aSegStart.y);
    return p;
}

double distancePoint2Point(const Point& aP1, const Point& aP2) {
    return std::sqrt((aP1.x - aP2.x) * (aP1.x - aP2.x) +
                     (aP1.y - aP2.y) * (aP1.y - aP2.y));
}

double distancePoint2Line(const Point& aPoint, const Point& aSegStart,
                          const Point& aSegEnd) {
    auto p = geometry::perpendicular(aPoint, aSegStart, aSegEnd);
    return distancePoint2Point(aPoint, p);
}

double distancePoint2Seg(const Point& aPoint, const Point& aSegStart,
                         const Point& aSegEnd) {
    double r = relationPointAndSeg(aPoint, aSegStart, aSegEnd);
    if (r >= 1) {
        return distancePoint2Point(aPoint, aSegEnd);
    }
    if (r <= 0) {
        return distancePoint2Point(aPoint, aSegStart);
    }
    return distancePoint2Line(aPoint, aSegStart, aSegEnd);
}

bool isPointOnSegment(const core::Point& aPoint, const core::Point& aSegStart,
                      const core::Point& aSegEnd) {
    auto SE = aSegEnd - aSegStart;
    auto SP = aPoint - aSegStart;
    auto EP = aPoint - aSegEnd;

    double dotSP_SE = dotProduct(SP, SE);
    double dotEP_SE = dotProduct(EP, -SE);
    double crossSP_SE = crossProduct(SP, SE);

    // 点积排除延长线，差积排除非共线
    if (std::abs(crossSP_SE) > geometry::EPSILON || dotSP_SE < 0 ||
        dotEP_SE < 0) {
        return false;
    }

    return true;
}

/****************************** Circle / Arc ******************************/

double arcRadius(const Point& aEndPoint, const Point& aCenterPoint) {
    return distancePoint2Point(aEndPoint, aCenterPoint);
}

double arcStartAngle(const Point& aStart, const Point& aCenter) {
    // 角度范围为 [0, 2π)
    double startAngle = std::atan2(aStart.y - aCenter.y, aStart.x - aCenter.x);
    if (startAngle < 0) {
        startAngle += 2 * M_PI;
    }
    return startAngle;
}

double arcEndAngle(const Point& aEnd, const Point& aCenter) {
    // 角度范围为 [0, 2π)
    double endAngle = std::atan2(aEnd.y - aCenter.y, aEnd.x - aCenter.x);
    if (endAngle < 0) {
        endAngle += 2 * M_PI;
    }
    return endAngle;
}

double arcSweepAngle(double aStartAngle, double endAngle, bool aIsCW) {
    double sweepAngle{};
    if (aIsCW) {
        sweepAngle = (aStartAngle < endAngle)
                         ? aStartAngle + 2 * M_PI - endAngle
                         : aStartAngle - endAngle;
    } else {
        sweepAngle = (endAngle < aStartAngle)
                         ? endAngle + 2 * M_PI - aStartAngle
                         : endAngle - aStartAngle;
    }
    return sweepAngle;
}

Point midPointOfArc(const Point& aStart, const Point& aEnd,
                    const Point& aCenter, bool aIsCW) {
    double startAngle = arcStartAngle(aStart, aCenter);
    double endAngle = arcEndAngle(aEnd, aCenter);
    double radius = distancePoint2Point(aStart, aCenter);
    return midPointOfArc(startAngle, endAngle, radius, aCenter, aIsCW);
}

Point midPointOfArc(double aStartAngle, double aEndAngle, double aRadius,
                    const Point& aCenter, bool aIsCW) {

    double midAngle{};

    if (((aEndAngle > aStartAngle) && aIsCW) ||
        ((aEndAngle < aStartAngle) && !aIsCW)) {
        midAngle = (aStartAngle + aEndAngle) * 0.5 + M_PI;
    } else if (((aEndAngle > aStartAngle) && !aIsCW) ||
               ((aEndAngle < aStartAngle) && aIsCW)) {
        midAngle = (aStartAngle + aEndAngle) * 0.5;
    } else {
        std::cerr << "midPointOfArc error " << __FILE_NAME__ << __LINE__
                  << std::endl;
        throw;
    }

    return {aCenter.x + aRadius * std::cos(midAngle),
            aCenter.y + aRadius * std::sin(midAngle)};
}

bool isPointInArcRange(const Point& aCenter, double aStartAngle,
                       double aSweepAngle, bool aIsCW, const Point& aTarget) {
    Point vector = aTarget - aCenter;
    // [-PI,PI)
    double pointAngle = std::atan2(vector.y, vector.x);
    // [0,2PI)
    if (pointAngle < 0) {
        pointAngle += 2 * M_PI;
    }

    double endAngle =
        aIsCW ? aStartAngle - aSweepAngle : aStartAngle + aSweepAngle;

    if (endAngle >= 2 * M_PI) {
        endAngle -= 2 * M_PI;
        return ((pointAngle >= aStartAngle) && (pointAngle <= 2 * M_PI) ||
                (pointAngle >= 0.0) && (pointAngle <= endAngle));
    } else if (endAngle < 0.0) {
        endAngle += 2 * M_PI;
        return ((pointAngle >= 0.0) && (pointAngle <= aStartAngle) ||
                (pointAngle <= 2 * M_PI) && (pointAngle >= endAngle));
    } else {
        return pointAngle >= aStartAngle && pointAngle <= endAngle;
    }
}

bool isPointInArcRangeExceptEdge(const Point& aCenter, double aStartAngle,
                                 double aSweepAngle, bool aIsCW,
                                 const Point& aTarget) {
    if (aTarget == aCenter) {
        return false;
    }
    Point vector = aTarget - aCenter;
    // [-PI,PI)
    double pointAngle = std::atan2(vector.y, vector.x);
    // [0,2PI)
    if (pointAngle < 0) {
        pointAngle += 2 * M_PI;
    }

    double endAngle =
        aIsCW ? aStartAngle - aSweepAngle : aStartAngle + aSweepAngle;

    if (endAngle >= 2 * M_PI) {
        endAngle -= 2 * M_PI;
        return ((pointAngle > aStartAngle) && (pointAngle < 2 * M_PI) ||
                (pointAngle >= 0.0) && (pointAngle < endAngle));
    } else if (endAngle < 0.0) {
        endAngle += 2 * M_PI;
        return ((pointAngle >= 0.0) && (pointAngle < aStartAngle) ||
                (pointAngle < 2 * M_PI) && (pointAngle > endAngle));
    } else {
        return pointAngle > aStartAngle && pointAngle < endAngle;
    }
}

bool isXMonotoneArc(const Point& aStart, const Point& aEnd,
                    const Point& aCenter, double aSweepAngle) {
    /**
     * 观察一：
     *      优弧一定是非X单调圆弧
     * 观察二：
     *      如果起点和终点的y轴，分布在圆心y轴的上下两侧，则一定是非x单调
     *
     * 基于上述观察可以作以下实现
     */
    // 优弧
    if (aSweepAngle > (M_PI + geometry::EPSILON)) {
        return false;
    }
    double impreciseStartY = aStart.y, impreciseEndY = aEnd.y;
    if (std::abs(aStart.y - aCenter.y) < geometry::EPSILON) {
        impreciseStartY = aCenter.y;
    }
    if (std::abs(aEnd.y - aCenter.y) < geometry::EPSILON) {
        impreciseEndY = aCenter.y;
    }
    // 180度
    if (impreciseStartY == aCenter.y && impreciseEndY == aCenter.y) {
        return true;
    }
    // 一上一下，上面已排除了等于圆心y的情况
    if ((impreciseStartY > aCenter.y && impreciseEndY < aCenter.y) ||
        (impreciseStartY < aCenter.y && impreciseEndY > aCenter.y)) {
        return false;
    }
    return true;
}

bool isYMonotoneArc(const Point& aStart, const Point& aEnd,
                    const Point& aCenter) {
    // 暂未开发
    return false;
}

void circleFrom3Points(const Point& aP1, const Point& aP2, const Point& aP3,
                       Point& aCenter, double& aRadius) {
    if (isCollinear(aP1, aP2, aP3)) {
        std::cerr << "[error] three points are Collinear" << __FILE__
                  << __LINE__ << std::endl;
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
    double B = (x1 * x1 + y1 * y1) * (y3 - y2) +
               (x2 * x2 + y2 * y2) * (y1 - y3) +
               (x3 * x3 + y3 * y3) * (y2 - y1);
    double C = (x1 * x1 + y1 * y1) * (x2 - x3) +
               (x2 * x2 + y2 * y2) * (x3 - x1) +
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

BBox bBoxOfArc(const Point& A, const Point& B, const Point& M) {
    // TODO: 这里用的是附加点计算的。用圆心可能会快一些。

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

bool detached(const BBox& aBBox1, const BBox& aBBox2) {
    // 排斥实验，检查两者是否相离
    return (aBBox1.getMaxX() < aBBox2.getMinX() ||
            aBBox1.getMaxY() < aBBox2.getMinY() ||
            aBBox2.getMaxX() < aBBox1.getMinX() ||
            aBBox2.getMaxY() < aBBox1.getMinY());
}

bool contains(const BBox& aBBox1, const BBox& aBBox2) {
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

}  // namespace geometry
