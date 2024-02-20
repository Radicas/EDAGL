#include <gtest/gtest.h>
#include "core/edge.h"

using namespace edagl::core;

class Core_EdgeTest : public testing::Test {};

TEST_F(Core_EdgeTest, construct) {
    // 默认构造
    Edge edge1;
    EXPECT_FALSE(edge1.isArc());
    EXPECT_FALSE(edge1.isXMonotone());

    // 自定义构造
    Edge edge2({1.1, 1.1}, {2.2, 2.2}, {3.3, 3.3}, false, false);
    EXPECT_FALSE(edge2.isArc());
    EXPECT_DOUBLE_EQ(edge2.getEnd().x, 2.2);

    // 拷贝构造
    const Edge& edge3(edge2);
    EXPECT_FALSE(edge3.isArc());

    // 赋值构造
    edge1 = edge3;
    EXPECT_FALSE(edge1.isArc());
    EXPECT_DOUBLE_EQ(edge1.getStart().x, 1.1);

    // 自定义构造2
    Edge edge5({-200.0, 0.0}, {0.0, 200.0}, {0.0, 0.0}, true, false);
    EXPECT_FALSE(edge5.isXMonotone());
}
