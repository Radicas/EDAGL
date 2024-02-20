#include <gtest/gtest.h>
#include "engine/geometry.h"

using namespace edagl::core;
using namespace edagl::geometry;

// 点距离
class Geometry_PointsDistanceTest : public testing::Test {};

TEST_F(Geometry_PointsDistanceTest, DistanceBetweenPositivePoints) {
    // Test distance between two positive points
    Point aP1 = {1, 2};
    Point aP2 = {4, 6};

    double result = distancePoint2Point(aP1, aP2);

    // Check the calculated distance
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST_F(Geometry_PointsDistanceTest, DistanceBetweenNegativePoints) {
    // Test distance between two negative points
    Point aP1 = {-1, -2};
    Point aP2 = {-4, -6};

    double result = distancePoint2Point(aP1, aP2);

    // Check the calculated distance
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST_F(Geometry_PointsDistanceTest, DistanceBetweenMixedPoints) {
    // Test distance between mixed positive and negative points
    Point aP1 = {-1, 2};
    Point aP2 = {4, -6};

    double result = distancePoint2Point(aP1, aP2);

    // Check the calculated distance
    EXPECT_DOUBLE_EQ(result, 9.433981132056603);
}

TEST_F(Geometry_PointsDistanceTest, DistanceBetweenPointsWithZeroCoordinates) {
    // Test distance between points with zero coordinates
    Point aP1 = {0, 0};
    Point aP2 = {0, 0};

    double result = distancePoint2Point(aP1, aP2);

    // Check the calculated distance
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(Geometry_PointsDistanceTest, DistanceBetweenHorizontalPoints) {
    // Test distance between two points with same y-coordinate
    Point aP1 = {1, 2};
    Point aP2 = {4, 2};

    double result = distancePoint2Point(aP1, aP2);

    // Check the calculated distance
    EXPECT_DOUBLE_EQ(result, 3.0);
}

TEST_F(Geometry_PointsDistanceTest, DistanceBetweenVerticalPoints) {
    // Test distance between two points with same x-coordinate
    Point aP1 = {1, 2};
    Point aP2 = {1, 6};

    double result = distancePoint2Point(aP1, aP2);

    // Check the calculated distance
    EXPECT_DOUBLE_EQ(result, 4.0);
}

// 共线判定
class Geometry_CollinearTest : public testing::Test {};

TEST_F(Geometry_CollinearTest, CollinearPoints) {
    // Test collinear points
    Point aP1 = {1, 1};
    Point aP2 = {2, 2};
    Point aP3 = {3, 3};

    bool result = isCollinear(aP1, aP2, aP3);

    // Check if the points are collinear
    EXPECT_TRUE(result);
}

TEST_F(Geometry_CollinearTest, NonCollinearPoints) {
    // Test non-collinear points
    Point aP1 = {1, 1};
    Point aP2 = {2, 2};
    Point aP3 = {3, 4};

    bool result = isCollinear(aP1, aP2, aP3);

    // Check if the points are not collinear
    EXPECT_FALSE(result);
}

TEST_F(Geometry_CollinearTest, CollinearPointsWithZeroCoordinates) {
    // Test collinear points with zero coordinates
    Point aP1 = {0, 0};
    Point aP2 = {0, 0};
    Point aP3 = {0, 0};

    bool result = isCollinear(aP1, aP2, aP3);

    // Check if the points are collinear
    EXPECT_TRUE(result);
}

TEST_F(Geometry_CollinearTest, CollinearPointsWithDifferentCoordinates) {
    // Test collinear points with different coordinates
    Point aP1 = {1, 2};
    Point aP2 = {2, 4};
    Point aP3 = {3, 6};

    bool result = isCollinear(aP1, aP2, aP3);

    // Check if the points are collinear
    EXPECT_TRUE(result);
}

// 点和线段关系判断
class Geometry_RelationPointAndSeg : public testing::Test {};

TEST_F(Geometry_RelationPointAndSeg, test1) {
    // p1 p2是线段
    Point p1(-2.0, 1.0);
    Point p2(2.0, 1.0);
    Point p3(0.0, 0.0);
    Point p4(-3.0, 1.0);
    Point p5(3.0, 1.0);
    Point p6(1.0, 1.0);

    double res1 = relationPointAndSeg(p1, p1, p2);
    EXPECT_DOUBLE_EQ(res1, 0.0);
    double res2 = relationPointAndSeg(p2, p1, p2);
    EXPECT_DOUBLE_EQ(res2, 1.0);
    double res3 = relationPointAndSeg(p3, p1, p2);
    EXPECT_TRUE(res3 > 0 && res3 < 1);
    double res4 = relationPointAndSeg(p4, p1, p2);
    EXPECT_TRUE(res4 < 0);
    double res5 = relationPointAndSeg(p5, p1, p2);
    EXPECT_TRUE(res5 > 1);
    double res6 = relationPointAndSeg(p6, p1, p2);
    EXPECT_TRUE(res6 > 0 && res3 < 1);
}

// 点到直线距离
class Geometry_DistancePoint2Line : public testing::Test {};

TEST_F(Geometry_PointsDistanceTest, test1) {
    // p1 p2是线段
    Point p1(-2.0, 1.0);
    Point p2(2.0, 1.0);
    Point p3(0.0, 0.0);
    Point p4(-3.0, 1.0);
    Point p5(3.0, 1.0);
    Point p6(1.0, 1.0);

    double res1 = distancePoint2Line(p3, p1, p2);
    EXPECT_DOUBLE_EQ(res1, 1.0);

    double res2 = distancePoint2Line(p6, p1, p2);
    EXPECT_DOUBLE_EQ(res2, 0.0);

    double res3 = distancePoint2Line(p2, p1, p2);
    EXPECT_DOUBLE_EQ(res3, 0.0);

    double res4 = distancePoint2Line(p5, p1, p2);
    EXPECT_DOUBLE_EQ(res4, 0.0);
}

// 点到直线距离
class Geometry_DistancePoint2Seg : public testing::Test {};

TEST_F(Geometry_DistancePoint2Seg, test1) {
    // p1 p2是线段
    Point p1(-2.0, 1.0);
    Point p2(2.0, 1.0);
    Point p3(0.0, 0.0);
    Point p4(-3.0, 1.0);
    Point p5(3.0, 1.0);
    Point p6(1.0, 1.0);

    double res1 = distancePoint2Seg(p3, p1, p2);
    EXPECT_DOUBLE_EQ(res1, 1.0);

    double res2 = distancePoint2Seg(p6, p1, p2);
    EXPECT_DOUBLE_EQ(res2, 0.0);

    double res3 = distancePoint2Seg(p2, p1, p2);
    EXPECT_DOUBLE_EQ(res3, 0.0);

    double res4 = distancePoint2Seg(p5, p1, p2);
    EXPECT_DOUBLE_EQ(res4, 1.0);
}

// 点是否在线段上(包括端点)
class Geometry_IsPointOnSegment : public testing::Test {
   public:
    Point s;
    Point e;
    Geometry_IsPointOnSegment() : s(6.0, 4.0), e(8.0, 0.0) {}
};

TEST_F(Geometry_IsPointOnSegment, test1) {
    bool result = isPointOnSegment(s, s, e);
    EXPECT_TRUE(result);
}

TEST_F(Geometry_IsPointOnSegment, test2) {
    bool result = isPointOnSegment(e, s, e);
    EXPECT_TRUE(result);
}

TEST_F(Geometry_IsPointOnSegment, test3) {
    Point p(7.0, 2.0);
    bool result = isPointOnSegment(p, s, e);
    EXPECT_TRUE(result);
}

TEST_F(Geometry_IsPointOnSegment, test4) {
    Point p(9.0, 1.0);
    bool result = isPointOnSegment(p, s, e);
    EXPECT_FALSE(result);
}

TEST_F(Geometry_IsPointOnSegment, test5) {
    Point p(7.5888040504911, 0.8223918990177);
    bool result = isPointOnSegment(p, s, e);
    EXPECT_TRUE(result);
}

TEST_F(Geometry_IsPointOnSegment, test6) {
    Point st(4.0, 5.0);
    Point et(-5.0, -4.0);
    Point pt(3.0000000000000004, 4.0);
    bool result = isPointOnSegment(pt, st, et);
    EXPECT_TRUE(result);
}