#include <gtest/gtest.h>
#include "engine/geometry.h"
using namespace core;
using namespace geometry;

class Core_BBoxTest : public testing::Test {};

TEST_F(Core_BBoxTest, ConstructorAndGetters) {
    // Test default constructor
    BBox bbox1;
    EXPECT_DOUBLE_EQ(bbox1.getMinX(), 0.0);
    EXPECT_DOUBLE_EQ(bbox1.getMaxX(), 0.0);
    EXPECT_DOUBLE_EQ(bbox1.getMinY(), 0.0);
    EXPECT_DOUBLE_EQ(bbox1.getMaxY(), 0.0);

    // Test parameterized constructor
    BBox bbox2(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(bbox2.getMinX(), 1.0);
    EXPECT_DOUBLE_EQ(bbox2.getMaxX(), 2.0);
    EXPECT_DOUBLE_EQ(bbox2.getMinY(), 3.0);
    EXPECT_DOUBLE_EQ(bbox2.getMaxY(), 4.0);
}

TEST_F(Core_BBoxTest, ReShape) {
    BBox bbox(1.0, 2.0, 3.0, 4.0);
    bbox.reShape(5.0, 6.0, 7.0, 8.0);

    EXPECT_DOUBLE_EQ(bbox.getMinX(), 5.0);
    EXPECT_DOUBLE_EQ(bbox.getMaxX(), 6.0);
    EXPECT_DOUBLE_EQ(bbox.getMinY(), 7.0);
    EXPECT_DOUBLE_EQ(bbox.getMaxY(), 8.0);
}

TEST_F(Core_BBoxTest, Merge) {
    BBox bbox1(0.0, 5.0, 0.0, 5.0);
    BBox bbox2(3.0, 7.0, -1.0, 6.0);
    BBox bbox3(-1.0, 8.0, -2.0, 1.0);

    bbox1.merge({bbox2, bbox3});

    EXPECT_DOUBLE_EQ(bbox1.getMinX(), -1.0);
    EXPECT_DOUBLE_EQ(bbox1.getMaxX(), 8.0);
    EXPECT_DOUBLE_EQ(bbox1.getMinY(), -2.0);
    EXPECT_DOUBLE_EQ(bbox1.getMaxY(), 6.0);
}

TEST_F(Core_BBoxTest, getMinX) {
    BBox bbox1(0.0, 5.0, 0.0, 5.0);

    EXPECT_DOUBLE_EQ(bbox1.getMinX(), 0.0);
}

TEST_F(Core_BBoxTest, getMinY) {
    BBox bbox1(0.0, 5.0, 0.0, 5.0);

    EXPECT_DOUBLE_EQ(bbox1.getMinY(), 0.0);
}

TEST_F(Core_BBoxTest, getMaxX) {
    BBox bbox1(0.0, 5.0, 0.0, 5.0);

    EXPECT_DOUBLE_EQ(bbox1.getMaxX(), 5.0);
}

TEST_F(Core_BBoxTest, getMaxY) {
    BBox bbox1(0.0, 5.0, 0.0, 5.0);

    EXPECT_DOUBLE_EQ(bbox1.getMaxY(), 5.0);
}

TEST_F(Core_BBoxTest, setMinX) {
    BBox bbox1(0.0, 5.0, 0.0, 5.0);
    bbox1.setMinX(100.0);
    EXPECT_DOUBLE_EQ(bbox1.getMinX(), 100.0);
}

TEST_F(Core_BBoxTest, setMinY) {
    BBox bbox1(0.0, 5.0, 0.0, 5.0);
    bbox1.setMinY(100.0);
    EXPECT_DOUBLE_EQ(bbox1.getMinY(), 100.0);
}

TEST_F(Core_BBoxTest, setMaxX) {
    BBox bbox1(0.0, 5.0, 0.0, 5.0);
    bbox1.setMaxX(100.0);
    EXPECT_DOUBLE_EQ(bbox1.getMaxX(), 100.0);
}

TEST_F(Core_BBoxTest, setMaxY) {
    BBox bbox1(0.0, 5.0, 0.0, 5.0);
    bbox1.setMaxY(100.0);
    EXPECT_DOUBLE_EQ(bbox1.getMaxY(), 100.0);
}
