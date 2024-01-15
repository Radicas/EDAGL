#include <gtest/gtest.h>
#include "engine/geometry.h"

using namespace core;
using namespace geometry;

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