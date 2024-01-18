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
/********************************** Point *********************************/

bool isCollinear(const Point& aP1, const Point& aP2, const Point& aP3) {
    return std::abs(crossProduct(aP1, aP2, aP3) - 0.0) < EPSILON;
}

double pointsDistance(const Point& aP1, const Point& aP2) {
    return std::sqrt((aP1.x - aP2.x) * (aP1.x - aP2.x) +
                     (aP1.y - aP2.y) * (aP1.y - aP2.y));
}
/****************************** Circle / Arc ******************************/

double getStartAngle(const core::Point& aStart, const core::Point& aCenter) {
    // 角度范围为 [0, 2π)
    double startAngle = std::atan2(aStart.y - aCenter.y, aStart.x - aCenter.x);
    if (startAngle < 0) {
        startAngle += 2 * M_PI;
    }
    return startAngle;
}

double getEndAngle(const core::Point& aEnd, const core::Point& aCenter) {
    // 角度范围为 [0, 2π)
    double endAngle = std::atan2(aEnd.y - aCenter.y, aEnd.x - aCenter.x);
    if (endAngle <= 0) {
        endAngle += 2 * M_PI;
    }
    return endAngle;
}

double getSweepAngle(double aStartAngle, double endAngle, bool aIsCW) {
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

core::Point getMidOfArc(const core::Point& aStart, const core::Point& aEnd,
                        const core::Point& aCenter, bool aIsCW) {
    double startAngle = getStartAngle(aStart, aCenter);
    double endAngle = getEndAngle(aEnd, aCenter);
    double radius = pointsDistance(aStart, aCenter);
    return getMidOfArc(startAngle, endAngle, radius, aCenter, aIsCW);
}

Point getMidOfArc(double aStartAngle, double aEndAngle, double aRadius,
                  const Point& aCenter, bool aIsCW) {

    double midAngle{};

    if (((aEndAngle > aStartAngle) && aIsCW) ||
        ((aEndAngle < aStartAngle) && !aIsCW)) {
        midAngle = (aStartAngle + aEndAngle) * 0.5 + M_PI;
    } else if (((aEndAngle > aStartAngle) && !aIsCW) ||
               ((aEndAngle < aStartAngle) && aIsCW)) {
        midAngle = (aStartAngle + aEndAngle) * 0.5;
    } else {
        std::cerr << "getMidOfArc error " << __FILE_NAME__ << __LINE__
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
    double endAngle{};
    if (aIsCW) {
        endAngle = aStartAngle - aSweepAngle;
    } else {
        endAngle = aStartAngle + aSweepAngle;
    }
    return (pointAngle >= aStartAngle && pointAngle <= endAngle);
}

bool isXMonotoneArc(const Point& aStart, const Point& aEnd,
                    const Point& aCenter, double aSweepAngle) {
    /**
     * 观察一：
     *      如果起点和终点的y轴，分布在圆心y轴的上下两侧，则一定是非x单调
     * 观察二：
     *      如果起点和终点的y轴，分布在圆心同侧时，如果圆弧是劣弧，则是x单调；如果是优弧，则是非x单调
     * 观察三：
     *      优弧一定是非X单调圆弧
     * 基于上述观察可以作以下实现
     */
    if (aStart.y < aCenter.y && aEnd.y > aCenter.y ||
        aStart.y > aCenter.y && aEnd.y < aCenter.y) {
        return false;
    }
    if (aSweepAngle <= M_PI &&
        ((aStart.y <= aCenter.y && aEnd.y <= aCenter.y) ||
         (aStart.y >= aCenter.y && aEnd.y >= aCenter.y))) {
        return true;
    }
    return false;
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

int intersectsBBoxes(const BBox& aBBox1, const BBox& aBBox2, BBox& aResult) {
    // 检查两个BBox是否相离或包含
    if (detached(aBBox1, aBBox2) || contains(aBBox1, aBBox2)) {
        return 1;  // 返回状态1
        // TODO: 定义异常
    }
    // 得到新的相交的BBox
    aResult.setMinX(std::max(aBBox1.getMinX(), aBBox2.getMinX()));
    aResult.setMinY(std::max(aBBox1.getMinY(), aBBox2.getMinY()));
    aResult.setMaxX(std::min(aBBox1.getMaxX(), aBBox2.getMaxX()));
    aResult.setMaxY(std::min(aBBox1.getMaxY(), aBBox2.getMaxY()));
    return 0;  // 返回状态0
}

}  // namespace geometry
