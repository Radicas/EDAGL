#include <gtest/gtest.h>
#include "core/edge.h"

using namespace core;

class Core_EdgeTest : public testing::Test {};

TEST_F(Core_EdgeTest, construct) {
    // 默认构造
    Edge edge1;
    //    EXPECT_EQ(edge1.getStart(), Point(0.0, 0.0));
    //    EXPECT_EQ(edge1.getEnd(), Point(0.0, 0.0));
    //    EXPECT_EQ(edge1.getAppendix(), Point(0.0, 0.0));
    EXPECT_FALSE(edge1.isArc());

    // 自定义构造
    Edge edge2({1.1, 1.1}, {2.2, 2.2}, {3.3, 3.3}, true);
    EXPECT_TRUE(edge2.isArc());
    EXPECT_DOUBLE_EQ(edge2.getEnd().x, 2.2);

    // 拷贝构造
    Edge edge3(edge2);
    EXPECT_TRUE(edge3.isArc());
    EXPECT_DOUBLE_EQ(edge3.getAppendix().x, 3.3);

    // 赋值构造
    edge1 = edge3;
    EXPECT_TRUE(edge1.isArc());
    EXPECT_DOUBLE_EQ(edge1.getStart().x, 1.1);
}

TEST_F(Core_EdgeTest, getters) {
    Edge edge({1.1, 1.1}, {2.2, 2.2}, {3.3, 3.3}, true);

    EXPECT_EQ(edge.getStart(), Point(1.1, 1.1));
    EXPECT_EQ(edge.getEnd(), Point(2.2, 2.2));
    EXPECT_EQ(edge.getAppendix(), Point(3.3, 3.3));
    EXPECT_TRUE(edge.isArc());
}