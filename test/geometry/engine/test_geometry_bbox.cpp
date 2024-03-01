#include <gtest/gtest.h>
#include "geometry/geometry.h"
#include "geometry/intersection.h"

using namespace edagl::core;
using namespace edagl::geometry;

// 分离检测
class Geometry_DetachedTest : public testing::Test {};

TEST_F(Geometry_DetachedTest, DetachedBBoxes) {
    // Test with detached bounding boxes
    BBox aBBox1(0, 1, 0, 1);
    BBox aBBox2(2, 3, 0, 1);

    bool result = detached(aBBox1, aBBox2);

    // Check if the result is true (detached)
    EXPECT_TRUE(result);
}

TEST_F(Geometry_DetachedTest, OverlappingBBoxes) {
    // Test with overlapping bounding boxes
    BBox aBBox1(0, 5, 0, 5);
    BBox aBBox2(3, 7, -1, 6);

    bool result = detached(aBBox1, aBBox2);

    // Check if the result is false (not detached)
    EXPECT_FALSE(result);
}

// 相交检测
class Geometry_ContainsTest : public testing::Test {};

TEST_F(Geometry_ContainsTest, ContainedBBoxes) {
    // Test with contained bounding boxes
    BBox aBBox1(0, 100, 0, 100);
    BBox aBBox2(10, 90, 10, 90);

    bool result1 = contains(aBBox1, aBBox2);
    bool result2 = contains(aBBox2, aBBox1);

    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
}

TEST_F(Geometry_ContainsTest, NonContainedBBoxes) {
    // Test with non-contained bounding boxes
    BBox aBBox1(0, 5, 0, 5);
    BBox aBBox2(3, 7, -1, 6);

    bool result = contains(aBBox1, aBBox2);

    // Check if the result is false (aBBox1 does not contain aBBox2)
    EXPECT_FALSE(result);
}

// 合并BBox
class Geometry_UnionBBox : public testing::Test {};

TEST_F(Geometry_UnionBBox, IntersectsBBoxes) {
    BBox aBBox1(0, 5, 0, 5);
    BBox aBBox2(3, 7, -1, 6);
    BBox aBBox3;
    intersectsBBoxes(aBBox1, aBBox2, aBBox3);
    EXPECT_DOUBLE_EQ(aBBox3.getMinX(), 3.0);
    EXPECT_DOUBLE_EQ(aBBox3.getMaxX(), 5.0);
    EXPECT_DOUBLE_EQ(aBBox3.getMinY(), 0.0);
    EXPECT_DOUBLE_EQ(aBBox3.getMaxY(), 5.0);
}

TEST_F(Geometry_UnionBBox, NonIntersectsBBoxes) {
    BBox aBBox1(0, 5, 0, 5);
    BBox aBBox2(6, 9, 0, 6);
    BBox aBBox3;
    intersectsBBoxes(aBBox1, aBBox2, aBBox3);
    EXPECT_DOUBLE_EQ(aBBox3.getMinX(), 0.0);
    EXPECT_DOUBLE_EQ(aBBox3.getMaxX(), 0.0);
    EXPECT_DOUBLE_EQ(aBBox3.getMinY(), 0.0);
    EXPECT_DOUBLE_EQ(aBBox3.getMaxY(), 0.0);
}