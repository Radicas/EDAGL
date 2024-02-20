#include <gtest/gtest.h>
#include "core/point.h"
#include "engine/geometry.h"
#include "engine/intersection.h"

#include <cmath>

using namespace edagl::core;
using namespace edagl::geometry;

// 线段和线段是否相交
class Geometry_IsSegSegIntersect : public testing::Test {};

TEST_F(Geometry_IsSegSegIntersect, test1) {

    Point p1(0.0, 0.0);
    Point p2(2.0, 2.0);
    Point p3(0.0, -2.0);
    Point p4(1.0, 2.0);
    Point p5(1.0, 1.0);
    Point p6(-0.5, -0.5);
    Point p7(1.0, -1.0);
    Point p8(1.0, -2.0);

    bool res1 = isSegSegIntersect(p1, p2, p3, p1);
    EXPECT_TRUE(res1);

    bool res2 = isSegSegIntersect(p1, p2, p3, p4);
    EXPECT_TRUE(res2);

    bool res3 = isSegSegIntersect(p1, p2, p3, p5);
    EXPECT_TRUE(res3);

    bool res4 = isSegSegIntersect(p1, p2, p3, p6);
    EXPECT_FALSE(res4);

    bool res5 = isSegSegIntersect(p1, p2, p3, p7);
    EXPECT_FALSE(res5);

    bool res6 = isSegSegIntersect(p1, p2, p3, p8);
    EXPECT_FALSE(res6);

    bool res7 = isSegSegIntersect(p1, p2, p1, p2);
    EXPECT_TRUE(res7);
}

// 线段和圆是否相交
class Geometry_IsSegCircleIntersect : public testing::Test {
   public:
    Point center;
    double radius;

    Point p1;
    Point p2;
    Point p3;
    Point p4;
    Point p5;
    Point p6;
    Point p7;
    Point p8;
    Point p9;
    Point p10;

    Geometry_IsSegCircleIntersect()
        : center(0.0, 0.0),
          radius(5.0),
          p1(6.0, 4.0),
          p2(8.0, 0.0),
          p3(5.0, 0.0),
          p4(5.5, 1.0),
          p5(2.0, 0.0),
          p6(2.0, -2.0),
          p7(4.0, 5.0),
          p8(-5.0, -4.0),
          p9(-5.0, 1.0),
          p10(-5.0, -1.0) {}
};

TEST_F(Geometry_IsSegCircleIntersect, test1) {
    bool result = isSegCircleIntersect(p1, p2, center, radius);
    EXPECT_FALSE(result);
}

TEST_F(Geometry_IsSegCircleIntersect, test2) {
    bool result = isSegCircleIntersect(p3, p4, center, radius);
    EXPECT_TRUE(result);
}

TEST_F(Geometry_IsSegCircleIntersect, test3) {
    bool result = isSegCircleIntersect(p5, p6, center, radius);
    EXPECT_FALSE(result);
}

TEST_F(Geometry_IsSegCircleIntersect, test4) {
    bool result = isSegCircleIntersect(p7, p8, center, radius);
    EXPECT_TRUE(result);
}

TEST_F(Geometry_IsSegCircleIntersect, test5) {
    bool result = isSegCircleIntersect(p9, p10, center, radius);
    EXPECT_TRUE(result);
}

// 线段和线段求交点
class Geometry_SegSegIntersectPoint : public testing::Test {};

TEST_F(Geometry_SegSegIntersectPoint, test1) {
    Point p1(0.0, 0.0);
    Point p2(2.0, 2.0);
    Point p3(0.0, -2.0);
    Point p4(1.0, 2.0);
    Point p5(1.0, 1.0);
    Point p6(-0.5, -0.5);
    Point p7(1.0, -1.0);
    Point p8(1.0, -2.0);

    Point res1p;
    bool res1 = segSegIntersectPoint(p1, p2, p3, p1, res1p);
    EXPECT_TRUE(res1);
    EXPECT_DOUBLE_EQ(res1p.x, 0.0);
    EXPECT_DOUBLE_EQ(res1p.y, 0.0);

    Point res2p;
    bool res2 = segSegIntersectPoint(p1, p2, p3, p4, res2p);
    EXPECT_TRUE(res2);
    EXPECT_DOUBLE_EQ(res2p.x, 0.66666666666666666);
    EXPECT_DOUBLE_EQ(res2p.y, 0.66666666666666666);

    Point res3p;
    bool res3 = segSegIntersectPoint(p1, p2, p3, p5, res3p);
    EXPECT_TRUE(res3);
    EXPECT_DOUBLE_EQ(res3p.x, 1.0);
    EXPECT_DOUBLE_EQ(res3p.y, 1.0);

    Point res4p;
    bool res4 = segSegIntersectPoint(p1, p2, p3, p6, res4p);
    EXPECT_FALSE(res4);

    Point res5p;
    bool res5 = segSegIntersectPoint(p1, p2, p3, p7, res5p);
    EXPECT_FALSE(res5);

    Point res6p;
    bool res6 = segSegIntersectPoint(p1, p2, p3, p8, res6p);
    EXPECT_FALSE(res6);
}

// 线段和圆弧求交点
class Geometry_SegArcIntersectPoints : public testing::Test {
   public:
    Point center;
    double radius;
    double startAngle;
    double sweepAngle;
    bool isCW;
    std::vector<Point> result;
    Geometry_SegArcIntersectPoints()
        : center(0.0, 0.0),
          radius(4.0),
          startAngle(0.0),
          sweepAngle(M_PI + M_PI_2),
          isCW(false),
          result() {}

    void printResult() {
        for (const auto& r : result) {
            std::cout << "(" << r.x << "," << r.y << ")\n";
        }
    }
};

TEST_F(Geometry_SegArcIntersectPoints, test1) {
    Point p1(4.0, 0.0);
    Point p2(8.0, 1.0);
    segArcIntersectPoints(p1, p2, center, radius, startAngle, sweepAngle, false,
                          result);
    EXPECT_EQ(result.size(), 1);
    EXPECT_DOUBLE_EQ(result[0].x, 4.0);
    EXPECT_DOUBLE_EQ(result[0].y, 0.0);
}

TEST_F(Geometry_SegArcIntersectPoints, test2) {
    Point p1(-1.0, -2.0);
    Point p2(4.0, -2.0);
    segArcIntersectPoints(p1, p2, center, radius, startAngle, sweepAngle, false,
                          result);
    EXPECT_EQ(result.size(), 0);
}

TEST_F(Geometry_SegArcIntersectPoints, test3) {
    Point p1(-4.0, 0.0);
    Point p2(4.0, 0.0);
    segArcIntersectPoints(p1, p2, center, radius, startAngle, sweepAngle, false,
                          result);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE((result[0].x - 4) < edagl::EPSILON ||
                (result[0].x) < edagl::EPSILON);
    EXPECT_TRUE((result[0].y + 4) < edagl::EPSILON ||
                (result[0].y) < edagl::EPSILON);
    EXPECT_TRUE((result[1].x - 4) < edagl::EPSILON ||
                (result[1].x) < edagl::EPSILON);
    EXPECT_TRUE((result[1].y + 4) < edagl::EPSILON ||
                (result[1].y) < edagl::EPSILON);
}

TEST_F(Geometry_SegArcIntersectPoints, test4) {
    Point p1(3.0, 1.0);
    Point p2(-2.0, 5.0);
    segArcIntersectPoints(p1, p2, center, radius, startAngle, sweepAngle, false,
                          result);
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(std::abs(result[0].x + 0.6777126903254) < edagl::EPSILON);
    EXPECT_TRUE(std::abs(result[0].y - 3.9421701522603) < edagl::EPSILON);
}

TEST_F(Geometry_SegArcIntersectPoints, test5) {
    Point p1(-6.0, -2.0);
    Point p2(-4.0, -5.0);
    segArcIntersectPoints(p1, p2, center, radius, startAngle, sweepAngle, false,
                          result);
    EXPECT_EQ(result.size(), 0);
}

// 圆弧和圆弧求交点
class Geometry_ArcArcIntersectPoints : public testing::Test {
   public:
    Point center;
    double radius;
    double sa;
    double sw;
    bool cw;
    std::vector<Point> result;
    Geometry_ArcArcIntersectPoints()
        : center(0.0, 0.0),
          radius(5.0),
          sa(0.0),
          sw(M_PI_2),
          cw(false),
          result() {}
};

TEST_F(Geometry_ArcArcIntersectPoints, test1) {
    Point center2(6.0, 4.0);
    double radius2 = 3.1622776601684;
    double sa2 = 161.565051177078 * M_PI / 180.0;
    double sw2 = 288.434948822922 * M_PI / 180.0;
    bool cw2 = false;
    bool ok = arcArcIntersectPoints(center, radius, sa, sw, cw, center2,
                                    radius2, sa2, sw2, cw2, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(std::abs(result[0].x - 2.839823721079) < edagl::EPSILON ||
                std::abs(result[1].x - 2.839823721079) < edagl::EPSILON);

    EXPECT_TRUE(std::abs(result[0].x - 4.8909455096903) < edagl::EPSILON ||
                std::abs(result[1].x - 4.8909455096903) < edagl::EPSILON);

    EXPECT_TRUE(std::abs(result[0].y - 4.1152644183815) < edagl::EPSILON ||
                std::abs(result[1].y - 4.1152644183815) < edagl::EPSILON);

    EXPECT_TRUE(std::abs(result[0].y - 1.0385817354646) < edagl::EPSILON ||
                std::abs(result[1].y - 1.0385817354646) < edagl::EPSILON);
}

TEST_F(Geometry_ArcArcIntersectPoints, test2) {
    Point center2(0.0, 7.0);
    double radius2 = 4.0;
    double sa2 = M_PI;
    double sw2 = M_PI;
    bool cw2 = false;
    bool ok = arcArcIntersectPoints(center, radius, sa, sw, cw, center2,
                                    radius2, sa2, sw2, cw2, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result.size(), 1);
    // (2.7994168488951,-4.1428571428571)
    EXPECT_TRUE(std::abs(result[0].x - 2.7994168488951) < edagl::EPSILON);
    EXPECT_TRUE(std::abs(result[0].y - 4.1428571428571) < edagl::EPSILON);
}

TEST_F(Geometry_ArcArcIntersectPoints, test3) {
    Point center2(10.0, 0.0);
    double radius2 = 5.0;
    double sa2 = M_PI;
    double sw2 = M_PI_2;
    bool cw2 = false;
    bool ok = arcArcIntersectPoints(center, radius, sa, sw, cw, center2,
                                    radius2, sa2, sw2, cw2, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result.size(), 1);
    // (2.7994168488951,-4.1428571428571)
    EXPECT_TRUE(std::abs(result[0].x - 5.0) < edagl::EPSILON);
    EXPECT_TRUE(std::abs(result[0].y - 0.0) < edagl::EPSILON);
}

// 边和边求交点
class Geometry_EdgeEdgeIntersectPoints : public testing::Test {};

// 线段和圆求交点
class Geometry_SegCircleIntersectPoints : public testing::Test {
   public:
    Point center;
    double radius;
    std::vector<Point> result;
    Geometry_SegCircleIntersectPoints()
        : center(0.0, 0.0), radius(5.0), result() {}
    void printResult() {
        for (const auto& r : result) {
            std::cout << "(" << r.x << "," << r.y << ")\n";
        }
    }
};

TEST_F(Geometry_SegCircleIntersectPoints, test1) {
    Point p1(4.0, 5.0);
    Point p2(-5.0, -4.0);
    segCircleIntersectPoints(p1, p2, center, radius, result);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE((result[0].x - 3) < edagl::EPSILON ||
                (result[0].x + 4) < edagl::EPSILON);
    EXPECT_TRUE((result[0].y - 4) < edagl::EPSILON ||
                (result[0].y + 3) < edagl::EPSILON);
    EXPECT_TRUE((result[1].x - 3) < edagl::EPSILON ||
                (result[1].x + 4) < edagl::EPSILON);
    EXPECT_TRUE((result[1].y - 4) < edagl::EPSILON ||
                (result[1].y + 3) < edagl::EPSILON);
}

TEST_F(Geometry_SegCircleIntersectPoints, test2) {
    Point p1(5.0, 0.0);
    Point p2(6.0, -1.0);
    segCircleIntersectPoints(p1, p2, center, radius, result);
    EXPECT_EQ(result.size(), 1);
    EXPECT_DOUBLE_EQ(result[0].x, 5.0);
    EXPECT_DOUBLE_EQ(result[0].y, 0.0);
}

TEST_F(Geometry_SegCircleIntersectPoints, test3) {
    Point p1(6.0, 4.0);
    Point p2(8.0, 0.0);
    segCircleIntersectPoints(p1, p2, center, radius, result);
    EXPECT_EQ(result.size(), 0);
}

// 圆和圆求交点
class Geometry_CircleCircleIntersectPoints : public testing::Test {
   public:
    Point center;
    double radius;
    std::vector<Point> result;
    Geometry_CircleCircleIntersectPoints()
        : center(0.0, 0.0), radius(5.0), result() {}
};

TEST_F(Geometry_CircleCircleIntersectPoints, test1) {
    Point center2(10.0, 0.0);
    double radius2 = 5.0;
    bool ok =
        circleCircleIntersectPoints(center, radius, center2, radius2, result);
    EXPECT_TRUE(ok);
    EXPECT_EQ(result.size(), 1);
    EXPECT_DOUBLE_EQ(result[0].x, 5.0);
    EXPECT_DOUBLE_EQ(result[0].y, 0.0);
}

TEST_F(Geometry_CircleCircleIntersectPoints, test2) {}