#include <gtest/gtest.h>
#include "core/edge.h"
#include "engine/geometry.h"

#include <cmath>

using namespace core;
using namespace geometry;

// 三点确定圆
class Geometry_CircleFrom3PointsTest : public testing::Test {};

TEST_F(Geometry_CircleFrom3PointsTest, ValidPoints) {
    // Test with valid points forming a circle
    core::Point aP1 = {0, 0};
    core::Point aP2 = {1, 0};
    core::Point aP3 = {0, 1};
    core::Point aCenter;
    double aRadius;

    circleFrom3Points(aP1, aP2, aP3, aCenter, aRadius);

    // Check the calculated center and radius
    EXPECT_DOUBLE_EQ(aCenter.x, 0.5);
    EXPECT_DOUBLE_EQ(aCenter.y, 0.5);
    EXPECT_DOUBLE_EQ(aRadius, 0.7071067811865476);
}

TEST_F(Geometry_CircleFrom3PointsTest, CollinearPoints) {
    //    // Test with collinear points, should not form a circle
    //    core::Point aP1 = {0, 0};
    //    core::Point aP2 = {1, 1};
    //    core::Point aP3 = {2, 2};
    //    core::Point aCenter;
    //    double aRadius;
    //
    //    circleFrom3Points(aP1, aP2, aP3, aCenter, aRadius);
    //
    //    // Check if the calculated radius is 0
    //    EXPECT_DOUBLE_EQ(aRadius, 0.0);
}

TEST_F(Geometry_CircleFrom3PointsTest, SamePoints) {
    //    // Test with same points, should not form a circle
    //    core::Point aP1 = {0, 0};
    //    core::Point aP2 = {0, 0};
    //    core::Point aP3 = {0, 0};
    //    core::Point aCenter;
    //    double aRadius;
    //
    //    circleFrom3Points(aP1, aP2, aP3, aCenter, aRadius);
    //
    //    // Check if the calculated radius is 0
    //    EXPECT_DOUBLE_EQ(aRadius, 0.0);
}

// 获取圆弧的包围盒
class Geometry_BBoxOfArcTest : public testing::Test {};

TEST_F(Geometry_BBoxOfArcTest, ValidArc) {
    // Test with valid arc
    core::Point A = {0, 0};
    core::Point B = {1, 0};
    core::Point M = {0.5, 0.5};
    core::BBox result;

    result = bBoxOfArc(A, B, M);

    // Check the calculated bounding box
    EXPECT_DOUBLE_EQ(result.getMinX(), 0.0);
    EXPECT_DOUBLE_EQ(result.getMaxX(), 1.0);
    EXPECT_DOUBLE_EQ(result.getMinY(), 0.0);
    EXPECT_DOUBLE_EQ(result.getMaxY(), 0.5);
}

TEST_F(Geometry_BBoxOfArcTest, ValidArc2) {
    // Test with valid arc
    core::Point A = {19.0, 3.0};
    core::Point B = {18.0, 6.0};
    core::Point M = {19.0, 5.0};
    core::BBox result;

    result = bBoxOfArc(A, B, M);

    // Check the calculated bounding box
    EXPECT_DOUBLE_EQ(result.getMinX(), 18.0);
    EXPECT_DOUBLE_EQ(result.getMaxX(), 19.2360679774998);
    EXPECT_DOUBLE_EQ(result.getMinY(), 3.0);
    EXPECT_DOUBLE_EQ(result.getMaxY(), 6.0);
}

TEST_F(Geometry_BBoxOfArcTest, ValidArc3) {
    // Test with valid arc
    core::Point A = {-2.0, 6.0};
    core::Point B = {-6.0, 6.0};
    core::Point M = {-4.0, 8.0};
    core::BBox result = bBoxOfArc(A, B, M);

    // Check the calculated bounding box
    EXPECT_DOUBLE_EQ(result.getMinX(), -6.0);
    EXPECT_DOUBLE_EQ(result.getMaxX(), -2.0);
    EXPECT_DOUBLE_EQ(result.getMinY(), 6.0);
    EXPECT_DOUBLE_EQ(result.getMaxY(), 8.0);
}

TEST_F(Geometry_BBoxOfArcTest, CollinearPoints) {
    //    // Test with collinear points, should return a bounding box with zero area
    //    core::Point A = {0, 0};
    //    core::Point B = {1, 1};
    //    core::Point M = {2, 2};
    //    core::BBox result;
    //
    //    result = bBoxOfArc(A, B, M);
    //
    //    // Check if the bounding box has zero area
    //    EXPECT_DOUBLE_EQ(result.getMinX(), 0.0);
    //    EXPECT_DOUBLE_EQ(result.getMaxX(), 0.0);
    //    EXPECT_DOUBLE_EQ(result.getMinY(), 0.0);
    //    EXPECT_DOUBLE_EQ(result.getMaxY(), 0.0);
}

TEST_F(Geometry_BBoxOfArcTest, SamePoints) {
    //    // Test with same points, should return a bounding box with zero area
    //    core::Point A = {0, 0};
    //    core::Point B = {0, 0};
    //    core::Point M = {0, 0};
    //    core::BBox result;
    //
    //    result = bBoxOfArc(A, B, M);
    //
    //    // Check if the bounding box has zero area
    //    EXPECT_DOUBLE_EQ(result.getMinX(), 0.0);
    //    EXPECT_DOUBLE_EQ(result.getMaxX(), 0.0);
    //    EXPECT_DOUBLE_EQ(result.getMinY(), 0.0);
    //    EXPECT_DOUBLE_EQ(result.getMaxY(), 0.0);
}

// 判读圆弧是否X单调
class Geometry_IsXMonotoneArc : public testing::Test {};

TEST_F(Geometry_IsXMonotoneArc, test1) {
    Point center1(0.0, 0.0);
    Point start1(-2.0, 0.0);
    Point end1(2.0, 0.0);
    double sweepAngle1 = M_PI;

    auto res1 = geometry::isXMonotoneArc(start1, end1, center1, sweepAngle1);
    EXPECT_TRUE(res1);

    Point center2(0.0, 0.0);
    Point start2(-4.0, -1.0);
    Point end2(1.0, -4.0);
    double sweepAngle2 = M_PI * 0.5;
    auto res2 = geometry::isXMonotoneArc(start2, end2, center2, sweepAngle2);
    EXPECT_TRUE(res2);

    Point center3(0.0, 0.0);
    Point start3(-4.0, -1.0);
    Point end3(4.0, 1.0);
    double sweepAngle3 = M_PI * 0.5;
    auto res3 = geometry::isXMonotoneArc(start3, end3, center3, sweepAngle3);
    EXPECT_FALSE(res3);

    Point center4(0.0, 0.0);
    Point start4(-4.0, 0.0);
    Point end4(0.0, 4.0);
    double sweepAngle4 = M_PI * 1.5;
    auto res4 = geometry::isXMonotoneArc(start4, end4, center4, sweepAngle4);
    EXPECT_FALSE(res4);

    Point center5(0.0, 0.0);
    Point start5(-4.0, 0.0);
    Point end5(-4.0, 0.0);
    double sweepAngle5 = M_PI * 2;
    auto res5 = geometry::isXMonotoneArc(start5, end5, center5, sweepAngle5);
    EXPECT_FALSE(res5);
}

// 点是否在圆弧范围内(包括边)
class Geometry_IsPointInArcRange : public testing::Test {};

TEST_F(Geometry_IsPointInArcRange, test1) {
    Edge edge({-200.0, 0.0}, {0.0, 200.0}, {0.0, 0.0}, true, false);
    Point p1(-300.0, 0.0);
    Point p2(-200.0, 0.0);
    Point p3(-100.0, 0.0);
    Point p4(-50.0, 50.0);
    Point p5(-50.0, -50.0);
    Point p6(0.0, 300.0);
    Point p7(0.0, 200.0);
    Point p8(0.0, 100.0);
    Point p9(0.0, 0.0);
    Point p10(0.0, -100.0);
    Point p11(0.0, -200.0);
    Point p12(0.0, -300.0);
    Point p13(50.0, 50.0);
    Point p14(50.0, -50.0);
    Point p15(100.0, 0.0);
    Point p16(200.0, 0.0);
    Point p17(300.0, 0.0);

    bool res1 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                  edge.getSweepAngle(), edge.isCW(), p1);
    bool res2 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                  edge.getSweepAngle(), edge.isCW(), p2);
    bool res3 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                  edge.getSweepAngle(), edge.isCW(), p3);
    bool res4 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                  edge.getSweepAngle(), edge.isCW(), p4);
    bool res5 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                  edge.getSweepAngle(), edge.isCW(), p5);
    bool res6 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                  edge.getSweepAngle(), edge.isCW(), p6);
    bool res7 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                  edge.getSweepAngle(), edge.isCW(), p7);
    bool res8 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                  edge.getSweepAngle(), edge.isCW(), p8);
    bool res9 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                  edge.getSweepAngle(), edge.isCW(), p9);
    bool res10 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                   edge.getSweepAngle(), edge.isCW(), p10);
    bool res11 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                   edge.getSweepAngle(), edge.isCW(), p11);
    bool res12 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                   edge.getSweepAngle(), edge.isCW(), p12);
    bool res13 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                   edge.getSweepAngle(), edge.isCW(), p13);
    bool res14 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                   edge.getSweepAngle(), edge.isCW(), p14);
    bool res15 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                   edge.getSweepAngle(), edge.isCW(), p15);
    bool res16 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                   edge.getSweepAngle(), edge.isCW(), p16);
    bool res17 = isPointInArcRange(edge.getCenter(), edge.getStartAngle(),
                                   edge.getSweepAngle(), edge.isCW(), p17);

    EXPECT_TRUE(res1);
    EXPECT_TRUE(res2);
    EXPECT_TRUE(res3);
    EXPECT_FALSE(res4);
    EXPECT_TRUE(res5);
    EXPECT_TRUE(res6);
    EXPECT_TRUE(res7);
    EXPECT_TRUE(res8);
    EXPECT_TRUE(res9);
    EXPECT_TRUE(res10);
    EXPECT_TRUE(res11);
    EXPECT_TRUE(res12);
    EXPECT_TRUE(res13);
    EXPECT_TRUE(res14);
    EXPECT_TRUE(res15);
    EXPECT_TRUE(res16);
    EXPECT_TRUE(res17);
}

// 点是否在圆弧范围内(不包括边)
class Geometry_IsPointInArcRangeExceptEdge : public testing::Test {};

TEST_F(Geometry_IsPointInArcRangeExceptEdge, test1) {
    Edge edge({-200.0, 0.0}, {0.0, 200.0}, {0.0, 0.0}, true, false);
    Point p1(-300.0, 0.0);
    Point p2(-200.0, 0.0);
    Point p3(-100.0, 0.0);
    Point p4(-50.0, 50.0);
    Point p5(-50.0, -50.0);
    Point p6(0.0, 300.0);
    Point p7(0.0, 200.0);
    Point p8(0.0, 100.0);
    Point p9(0.0, 0.0);
    Point p10(0.0, -100.0);
    Point p11(0.0, -200.0);
    Point p12(0.0, -300.0);
    Point p13(50.0, 50.0);
    Point p14(50.0, -50.0);
    Point p15(100.0, 0.0);
    Point p16(200.0, 0.0);
    Point p17(300.0, 0.0);

    bool res1 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p1);
    bool res2 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p2);
    bool res3 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p3);
    bool res4 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p4);
    bool res5 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p5);
    bool res6 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p6);
    bool res7 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p7);
    bool res8 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p8);
    bool res9 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p9);
    bool res10 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p10);
    bool res11 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p11);
    bool res12 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p12);
    bool res13 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p13);
    bool res14 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p14);
    bool res15 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p15);
    bool res16 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p16);
    bool res17 =
        isPointInArcRangeExceptEdge(edge.getCenter(), edge.getStartAngle(),
                                    edge.getSweepAngle(), edge.isCW(), p17);

    EXPECT_FALSE(res1);
    EXPECT_FALSE(res2);
    EXPECT_FALSE(res3);
    EXPECT_FALSE(res4);
    EXPECT_TRUE(res5);
    EXPECT_FALSE(res6);
    EXPECT_FALSE(res7);
    EXPECT_FALSE(res8);
    EXPECT_FALSE(res9);
    EXPECT_TRUE(res10);
    EXPECT_TRUE(res11);
    EXPECT_TRUE(res12);
    EXPECT_TRUE(res13);
    EXPECT_TRUE(res14);
    EXPECT_TRUE(res15);
    EXPECT_TRUE(res16);
    EXPECT_TRUE(res17);
}

// 获取圆弧的中点
class Geometry_GetMidOfArc : public testing::Test {};

TEST_F(Geometry_GetMidOfArc, test1) {
    core::Point center(0.0, 0.0);
    double radius = 5.0;
    double startAngle = 0.0;
    double endAngle = M_PI_2;
    bool isCW = false;

    core::Point midPoint =
        midPointOfArc(startAngle, endAngle, radius, center, isCW);

    EXPECT_TRUE(std::abs(midPoint.x - 3.5355339059327) < geometry::EPSILON);
    EXPECT_TRUE(std::abs(midPoint.y - 3.5355339059327) < geometry::EPSILON);
}

TEST_F(Geometry_GetMidOfArc, test2) {
    core::Point center(0.0, 0.0);
    double radius = 2.0;
    double startAngle = 1.5 * M_PI;
    double endAngle = M_PI_2;
    bool isCW = false;

    core::Point midPoint =
        midPointOfArc(startAngle, endAngle, radius, center, isCW);

    EXPECT_TRUE(std::abs(midPoint.x - 2.0) < geometry::EPSILON);
    EXPECT_TRUE(std::abs(midPoint.y - 0.0) < geometry::EPSILON);
}

TEST_F(Geometry_GetMidOfArc, test3) {
    core::Point center(0.0, 0.0);
    double radius = 2.0;
    double startAngle = M_PI_2;
    double endAngle = 1.5 * M_PI;
    bool isCW = false;

    core::Point midPoint =
        midPointOfArc(startAngle, endAngle, radius, center, isCW);

    EXPECT_TRUE(std::abs(midPoint.x - (-2.0)) < geometry::EPSILON);
    EXPECT_TRUE(std::abs(midPoint.y - 0.0) < geometry::EPSILON);
}

TEST_F(Geometry_GetMidOfArc, test4) {
    core::Point center(0.0, 0.0);
    double radius = 2.8284271247462;
    double startAngle = M_PI + M_PI_4;
    double endAngle = M_PI + M_PI_2 + M_PI_4;
    bool isCW = true;

    core::Point midPoint =
        midPointOfArc(startAngle, endAngle, radius, center, isCW);

    // (0,2.8284271247462)
    EXPECT_TRUE(std::abs(midPoint.x - 0.0) < geometry::EPSILON);
    EXPECT_TRUE(std::abs(midPoint.y - 2.8284271247462) < geometry::EPSILON);
}