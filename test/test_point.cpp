#include <gtest/gtest.h>
#include "core/point.h"

using namespace core;

TEST(point, construct) {
    Point p(1, 2);
    EXPECT_EQ(p.x, 1.0);
    EXPECT_EQ(p.y, 2.0);
}