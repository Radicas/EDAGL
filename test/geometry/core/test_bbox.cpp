#include <gtest/gtest.h>
#include "core/bbox.h"

using namespace core;
TEST(Core_BBox, ConstructorAndGetters) {
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

TEST(Core_BBox, ReShape) {
    BBox bbox(1.0, 2.0, 3.0, 4.0);
    bbox.reShape(5.0, 6.0, 7.0, 8.0);

    EXPECT_DOUBLE_EQ(bbox.getMinX(), 5.0);
    EXPECT_DOUBLE_EQ(bbox.getMaxX(), 6.0);
    EXPECT_DOUBLE_EQ(bbox.getMinY(), 7.0);
    EXPECT_DOUBLE_EQ(bbox.getMaxY(), 8.0);
}

TEST(Core_BBox, Detached) {
    BBox bbox1(1.0, 2.0, 3.0, 4.0);
    BBox bbox2(3.0, 4.0, 5.0, 6.0);

    EXPECT_TRUE(BBox::detached(bbox1, bbox2));
    EXPECT_TRUE(BBox::detached(bbox2, bbox1));

    BBox bbox3(1.0, 3.0, 2.0, 4.0);

    EXPECT_FALSE(BBox::detached(bbox1, bbox3));
    EXPECT_FALSE(BBox::detached(bbox3, bbox1));
}

TEST(Core_BBox, Contains) {
    BBox bbox1(1.0, 4.0, 2.0, 5.0);
    BBox bbox2(2.0, 3.0, 3.0, 4.0);

    EXPECT_TRUE(BBox::contains(bbox1, bbox2));
    EXPECT_TRUE(BBox::contains(bbox2, bbox1));
}

TEST(Core_BBox, IntersectionBBox) {
    BBox bbox1(1.0, 5.0, -1.0, 3.0);
    BBox bbox2(2.0, 6.0, 1.0, 5.0);
    BBox bbox3;
    BBox::intersectionBBox(bbox1, bbox2, bbox3);
    EXPECT_DOUBLE_EQ(bbox3.getMinX(), 2.0);
    EXPECT_DOUBLE_EQ(bbox3.getMaxX(), 5.0);
    EXPECT_DOUBLE_EQ(bbox3.getMinY(), 1.0);
    EXPECT_DOUBLE_EQ(bbox3.getMaxY(), 3.0);
}
