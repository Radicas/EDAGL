#include <gtest/gtest.h>
#include "core/edge.h"

using namespace core;

class Core_EdgeTest : public testing::Test {};

TEST_F(Core_EdgeTest, construct) {
    // 默认构造
    Edge edge1;
    EXPECT_FALSE(edge1.isArc());
    EXPECT_FALSE(edge1.isXMonotone());

    // 自定义构造
    Edge edge2({1.1, 1.1}, {2.2, 2.2}, {3.3, 3.3}, false);
    EXPECT_FALSE(edge2.isArc());
    EXPECT_DOUBLE_EQ(edge2.getEnd().x, 2.2);

    // 拷贝构造
    const Edge& edge3(edge2);
    EXPECT_FALSE(edge3.isArc());
    EXPECT_DOUBLE_EQ(edge3.getAppendix().x, 3.3);

    // 赋值构造
    edge1 = edge3;
    EXPECT_FALSE(edge1.isArc());
    EXPECT_DOUBLE_EQ(edge1.getStart().x, 1.1);

    // 自定义构造2
    Edge edge5({-200.0, 0.0}, {0.0, 200.0}, {0.0, -200.0}, true, true, false);
    EXPECT_FALSE(edge5.isXMonotone());
}

TEST_F(Core_EdgeTest, getters) {
    Edge edge({-200.0, 0.0}, {0.0, 200.0}, {0.0, -200.0}, true, true, false);

    EXPECT_EQ(edge.getStart(), Point(-200.0, 0.0));
    EXPECT_EQ(edge.getEnd(), Point(0.0, 200.0));
    EXPECT_EQ(edge.getAppendix(), Point(0.0, -200.0));
    EXPECT_TRUE(edge.isArc());
    EXPECT_FALSE(edge.isXMonotone());
    EXPECT_FALSE(edge.isCW());
}

TEST_F(Core_EdgeTest, initValues) {
    Edge edge({-200.0, 0.0}, {0.0, 200.0}, {0.0, -200.0}, true, true, false);
    EXPECT_DOUBLE_EQ(edge.getCenter().x, 0.0);
    EXPECT_DOUBLE_EQ(edge.getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(edge.getRadius(), 200.0);
    EXPECT_DOUBLE_EQ(edge.getStartAngle(), M_PI);
    EXPECT_DOUBLE_EQ(edge.getEndAngle(), M_PI * 0.5);
    EXPECT_DOUBLE_EQ(edge.getSweepAngle(), 1.5 * M_PI);

    Edge edge2({1000.0, 300.0}, {1150.0, 150.0}, {1100.0, 300.0}, true, true,
               true);
    EXPECT_DOUBLE_EQ(edge2.getSweepAngle(), 143.130102354156 * M_PI / 180.0);

    Edge edge3({1150.0, 150.0}, {1000.0, 300.0}, {1100.0, 300.0}, true, true,
               false);
    EXPECT_DOUBLE_EQ(edge3.getSweepAngle(), 143.130102354156 * M_PI / 180.0);
}