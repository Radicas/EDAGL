#include <gtest/gtest.h>
#include "engine/geometry.h"

using namespace core;
using namespace geometry;

// 点距离
class Geometry_PointsDistanceTest : public testing::Test {};

TEST_F(Geometry_PointsDistanceTest, DistanceBetweenPositivePoints) {
    // Test distance between two positive points
    core::Point aP1 = {1, 2};
    core::Point aP2 = {4, 6};

    double result = pointsDistance(aP1, aP2);

    // Check the calculated distance
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST_F(Geometry_PointsDistanceTest, DistanceBetweenNegativePoints) {
    // Test distance between two negative points
    core::Point aP1 = {-1, -2};
    core::Point aP2 = {-4, -6};

    double result = pointsDistance(aP1, aP2);

    // Check the calculated distance
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST_F(Geometry_PointsDistanceTest, DistanceBetweenMixedPoints) {
    // Test distance between mixed positive and negative points
    core::Point aP1 = {-1, 2};
    core::Point aP2 = {4, -6};

    double result = pointsDistance(aP1, aP2);

    // Check the calculated distance
    EXPECT_DOUBLE_EQ(result, 9.433981132056603);
}

TEST_F(Geometry_PointsDistanceTest, DistanceBetweenPointsWithZeroCoordinates) {
    // Test distance between points with zero coordinates
    core::Point aP1 = {0, 0};
    core::Point aP2 = {0, 0};

    double result = pointsDistance(aP1, aP2);

    // Check the calculated distance
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(Geometry_PointsDistanceTest, DistanceBetweenHorizontalPoints) {
    // Test distance between two points with same y-coordinate
    core::Point aP1 = {1, 2};
    core::Point aP2 = {4, 2};

    double result = pointsDistance(aP1, aP2);

    // Check the calculated distance
    EXPECT_DOUBLE_EQ(result, 3.0);
}

TEST_F(Geometry_PointsDistanceTest, DistanceBetweenVerticalPoints) {
    // Test distance between two points with same x-coordinate
    core::Point aP1 = {1, 2};
    core::Point aP2 = {1, 6};

    double result = pointsDistance(aP1, aP2);

    // Check the calculated distance
    EXPECT_DOUBLE_EQ(result, 4.0);
}

// 共线判定
class Geometry_CollinearTest : public testing::Test {};

TEST_F(Geometry_CollinearTest, CollinearPoints) {
    // Test collinear points
    core::Point aP1 = {1, 1};
    core::Point aP2 = {2, 2};
    core::Point aP3 = {3, 3};

    bool result = isCollinear(aP1, aP2, aP3);

    // Check if the points are collinear
    EXPECT_TRUE(result);
}

TEST_F(Geometry_CollinearTest, NonCollinearPoints) {
    // Test non-collinear points
    core::Point aP1 = {1, 1};
    core::Point aP2 = {2, 2};
    core::Point aP3 = {3, 4};

    bool result = isCollinear(aP1, aP2, aP3);

    // Check if the points are not collinear
    EXPECT_FALSE(result);
}

TEST_F(Geometry_CollinearTest, CollinearPointsWithZeroCoordinates) {
    // Test collinear points with zero coordinates
    core::Point aP1 = {0, 0};
    core::Point aP2 = {0, 0};
    core::Point aP3 = {0, 0};

    bool result = isCollinear(aP1, aP2, aP3);

    // Check if the points are collinear
    EXPECT_TRUE(result);
}

TEST_F(Geometry_CollinearTest, CollinearPointsWithDifferentCoordinates) {
    // Test collinear points with different coordinates
    core::Point aP1 = {1, 2};
    core::Point aP2 = {2, 4};
    core::Point aP3 = {3, 6};

    bool result = isCollinear(aP1, aP2, aP3);

    // Check if the points are collinear
    EXPECT_TRUE(result);
}