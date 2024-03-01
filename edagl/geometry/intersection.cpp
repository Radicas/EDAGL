#include "intersection.h"
#include "core/edge.h"
#include "geometry/geometry.h"

#include <algorithm>
#include <cmath>

namespace edagl {
namespace geometry {

using namespace edagl::core;

/********************************** Segment **********************************/

bool isSegSegIntersect(const Point& aS1, const Point& aE1, const Point& aS2,
                       const Point& aE2) {
    return (std::max(aS1.x, aE1.x) >= std::min(aS2.x, aE2.x) &&  // 排斥实验
            std::max(aS2.x, aE2.x) >= std::min(aS1.x, aE1.x) &&
            std::max(aS1.y, aE1.y) >= std::min(aS2.y, aE2.y) &&
            std::max(aS2.y, aE2.y) >= std::min(aS1.y, aE1.y) &&
            crossProduct(aS2, aE1, aS1) * crossProduct(aE1, aE2, aS1) >=
                0 &&  // 跨立实验
            crossProduct(aS1, aE2, aS2) * crossProduct(aE2, aE1, aS2) >= 0);
}

bool isSegCircleIntersect(const Point& aSegStart, const Point& aSegEnd,
                          const Point& aCenter, double aRadius) {
    double dist = distancePoint2Seg(aCenter, aSegStart, aSegEnd);
    double distCS = distancePoint2Point(aCenter, aSegStart);
    double distES = distancePoint2Point(aCenter, aSegEnd);
    double length = distancePoint2Point(aSegStart, aSegEnd);
    // 相切或者端点在圆上
    if (std::abs(dist - aRadius) < edagl::EPSILON) {
        return true;
    }
    // 相离
    // 端点在圆上时，浮点数误差可能也会判定为false，放在后面判断即可
    if (dist > aRadius) {
        return false;
    }
    // 跑到这里时，线段所在直线和圆只有相切和相交两种情况
    // 线段端点一个在圆外一个在圆内，或者线段长度大于等于直径
    if ((distCS >= aRadius && distES <= aRadius) ||
        (distCS <= aRadius && distES >= aRadius) || length >= 2 * aRadius) {
        return true;
    }
    return false;
}

bool segSegIntersectPoint(const Point& aSegStart1, const Point& aSegEnd1,
                          const Point& aSegStart2, const Point& aSegEnd2,
                          Point& aResult) {
    // 去处不相交的线段
    if (!isSegSegIntersect(aSegStart1, aSegEnd1, aSegStart2, aSegEnd2)) {
        return false;
    }

    // 计算直线一般式 Ax + By = C 的系数
    double A1 = aSegEnd1.y - aSegStart1.y;
    double B1 = aSegStart1.x - aSegEnd1.x;
    double C1 = A1 * aSegStart1.x + B1 * aSegStart1.y;

    double A2 = aSegEnd2.y - aSegStart2.y;
    double B2 = aSegStart2.x - aSegEnd2.x;
    double C2 = A2 * aSegStart2.x + B2 * aSegStart2.y;

    // 计算交点
    double determinant = A1 * B2 - A2 * B1;
    if (determinant == 0.0) {
        return false;
    }
    double x = (B2 * C1 - B1 * C2) / determinant;
    double y = (A1 * C2 - A2 * C1) / determinant;

    aResult.x = x;
    aResult.y = y;

    return true;
}

/********************************** Arc **********************************/

bool segArcIntersectPoints(const Point& aSegStart, const Point& aSegEnd,
                           const Point& aArcCenter, double aRadius,
                           double aStartAngle, double aSweepAngle, bool aIsCW,
                           std::vector<Point>& aResult) {
    std::vector<Point> result;
    segCircleIntersectPoints(aSegStart, aSegEnd, aArcCenter, aRadius, result);

    // 和圆没有交点
    if (result.empty()) {
        return false;
    }
    // 1个或2个
    for (const auto& point : result) {
        // 是否在圆弧范围内，包括端点
        bool onArc = isPointInArcRange(aArcCenter, aStartAngle, aSweepAngle,
                                       aIsCW, point);
        if (onArc) {
            aResult.emplace_back(point);
        }
    }
    return true;
}

bool lineCircleIntersectPoints(double A, double B, double C,
                               const Point& center, double radius,
                               std::vector<Point>& result) {
    result.clear();
    // 避免无效的输入
    if (radius <= 0 || (A == 0 && B == 0)) {
        return false;
    }
    // 计算直线的法线（垂直）距离到圆心的距离
    double dist = fabs(A * center.x + B * center.y + C) / sqrt(A * A + B * B);
    // 如果距离大于半径，则没有交点
    if (dist > radius) {
        return false;
    }
    // 计算交点的坐标
    double dx = A / sqrt(A * A + B * B);
    double dy = B / sqrt(A * A + B * B);
    double x0 = center.x - dx * (C / sqrt(A * A + B * B));
    double y0 = center.y - dy * (C / sqrt(A * A + B * B));
    // 直线与圆相切
    if (dist == radius) {
        result.emplace_back(x0, y0);
        return true;
    }
    // 计算两个交点
    double d = sqrt(radius * radius -
                    dist * dist);  // 从圆心到交点连线与直线的交点的距离
    double mult = sqrt(d * d / (A * A + B * B));
    Point p1 = {x0 + B * mult, y0 - A * mult};
    Point p2 = {x0 - B * mult, y0 + A * mult};
    result.push_back(p1);
    result.push_back(p2);
    return true;
}

bool arcArcIntersectPoints(const Point& aCenter1, double aRadius1,
                           double aStartAngle1, double aSweepAngle1,
                           bool aIsCW1, const Point& aCenter2, double aRadius2,
                           double aStartAngle2, double aSweepAngle2,
                           bool aIsCW2, std::vector<Point>& aResult) {
    // 声明临时点
    std::vector<Point> tmpRes{};
    // 计算圆弧所在圆的交点
    if (!circleCircleIntersectPoints(aCenter1, aRadius1, aCenter2, aRadius2,
                                     tmpRes)) {
        return false;
    }
    if (tmpRes.size() == 1) {
        // 交点数为1
        if (isPointInArcRange(aCenter1, aStartAngle1, aSweepAngle1, aIsCW1,
                              tmpRes[0]) &&
            isPointInArcRange(aCenter2, aStartAngle2, aSweepAngle2, aIsCW2,
                              tmpRes[0])) {
            aResult.emplace_back(std::move(tmpRes[0]));
            return true;
        }
    } else if (tmpRes.size() == 2) {
        // 交点数为2
        auto& p1 = tmpRes[0];
        auto& p2 = tmpRes[1];
        // 判断交点1同时在两个圆弧范围内
        if (isPointInArcRange(aCenter1, aStartAngle1, aSweepAngle1, aIsCW1,
                              p1) &&
            isPointInArcRange(aCenter2, aStartAngle2, aSweepAngle2, aIsCW2,
                              p1)) {
            aResult.emplace_back(std::move(p1));
        }
        // 判断交点2同时在两个圆弧范围内
        if (isPointInArcRange(aCenter1, aStartAngle1, aSweepAngle1, aIsCW1,
                              p2) &&
            isPointInArcRange(aCenter2, aStartAngle2, aSweepAngle2, aIsCW2,
                              p2)) {
            aResult.emplace_back(std::move(p2));
        }
        if (!aResult.empty()) {
            return true;
        }
    }
    return false;
}

/*********************************** Edge ***********************************/

bool edgeEdgeIntersectPoints(const Edge& aEdge1, const Edge& aEdge2,
                             std::vector<Point>& aResult) {
    if (aEdge1.isArc()) {
        if (aEdge2.isArc()) {
            // arc arc
            return arcArcIntersectPoints(
                aEdge1.getCenter(), aEdge1.getRadius(), aEdge1.getStartAngle(),
                aEdge1.getSweepAngle(), aEdge1.isCW(), aEdge2.getCenter(),
                aEdge2.getRadius(), aEdge2.getStartAngle(),
                aEdge2.getSweepAngle(), aEdge2.isCW(), aResult);
        } else {
            // arc seg
            return segArcIntersectPoints(
                aEdge2.getStart(), aEdge2.getEnd(), aEdge1.getCenter(),
                aEdge1.getRadius(), aEdge1.getStartAngle(),
                aEdge1.getSweepAngle(), aEdge1.isCW(), aResult);
        }
    } else {
        if (aEdge2.isArc()) {
            // seg arc
            return segArcIntersectPoints(
                aEdge1.getStart(), aEdge1.getEnd(), aEdge2.getCenter(),
                aEdge2.getRadius(), aEdge2.getStartAngle(),
                aEdge2.getSweepAngle(), aEdge2.isCW(), aResult);
        } else {
            // seg seg
            aResult.resize(1);
            return segSegIntersectPoint(aEdge1.getStart(), aEdge1.getEnd(),
                                        aEdge2.getStart(), aEdge2.getEnd(),
                                        aResult[0]);
        }
    }
    return false;
}

/********************************** Circle **********************************/

bool segCircleIntersectPoints(const Point& aSegStart, const Point& aSegEnd,
                              const Point& aCenter, double aRadius,
                              std::vector<Point>& aResult) {
    if (!isSegCircleIntersect(aSegStart, aSegEnd, aCenter, aRadius)) {
        return false;
    }
    // 是否有必要清空一下？
    aResult.clear();

    /**
     * 逻辑：
     * 求圆心到线段直线的投影
     * 求投影到交点的距离
     * 求线段方向的单位向量
     * 求出可能的两个交点
     * 判断交点是否在线段上
     * 经过圆心的线段也同样适用
     */
    auto pedal = perpendicular(aCenter, aSegStart, aSegEnd);
    Vector2D SE = aSegEnd - aSegStart;
    double distCP = distancePoint2Point(aCenter, pedal);
    double dist = std::sqrt(aRadius * aRadius - distCP * distCP);
    SE = normalized(SE);
    Point p1 = pedal + SE * dist;
    Point p2 = pedal - SE * dist;
    if (isPointOnSegment(p1, aSegStart, aSegEnd)) {
        aResult.emplace_back(p1);
    }
    if (isPointOnSegment(p2, aSegStart, aSegEnd)) {
        aResult.emplace_back(p2);
    }
    return true;
}

bool circleCircleIntersectPoints(const Point& aCenter1, double aRadius1,
                                 const Point& aCenter2, double aRadius2,
                                 std::vector<Point>& aResult) {
    double d = geometry::distancePoint2Point(aCenter1, aCenter2);
    // 两个圆没有相交
    if (d > aRadius1 + aRadius2) {
        return false;
    }
    // 一个圆包含在另一个圆内，没有相交点
    if (d < std::abs(aRadius1 - aRadius2)) {
        return false;
    }
    // 计算相交点
    double a = (aRadius1 * aRadius1 - aRadius2 * aRadius2 + d * d) / (2 * d);
    double h = std::sqrt(aRadius1 * aRadius1 - a * a);
    // 相交点的坐标
    double x2 = aCenter1.x + a * (aCenter2.x - aCenter1.x) / d;
    double y2 = aCenter1.y + a * (aCenter2.y - aCenter1.y) / d;
    // 两个相交点
    Point intersect1(x2 + h * (aCenter2.y - aCenter1.y) / d,
                     y2 - h * (aCenter2.x - aCenter1.x) / d);
    Point intersect2(x2 - h * (aCenter2.y - aCenter1.y) / d,
                     y2 + h * (aCenter2.x - aCenter1.x) / d);
    aResult.push_back(intersect1);
    if (intersect1 != intersect2) {
        aResult.push_back(intersect2);
    }
    return true;
}
/********************************** BBOx **********************************/

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
}  // namespace edagl