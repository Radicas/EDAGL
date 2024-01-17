#include <gtest/gtest.h>
#include "core/edgedomain.h"

using namespace core;

class Core_EdgeDomainTest : public testing::Test {};

TEST_F(Core_EdgeDomainTest, construct) {
    EdgeDomain ed;
    EXPECT_EQ(ed.getArcMark(), 0);

    Edge edge{};
    EdgeDomain ed2(edge, {0.2, 0.3}, 1);
    EXPECT_DOUBLE_EQ(ed2.getLocation().first, 0.2);
    EXPECT_DOUBLE_EQ(ed2.getLocation().second, 0.3);
    EXPECT_EQ(ed2.getArcMark(), 1);
}