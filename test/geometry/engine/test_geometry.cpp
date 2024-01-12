#include "engine/geometry.h"
#include <gtest/gtest.h>

using namespace core;
using namespace geometry;

// 点积
class Geometry_DotProductTest : public testing::Test
{
};

TEST_F(Geometry_DotProductTest, PositiveValues)
{
    // Test with positive values
    core::Point s = {1, 2};
    core::Point e = {3, 4};
    core::Point o = {0, 0};

    double result = dotProduct(s, e, o);

    // Check the calculated dot product
    EXPECT_EQ(result, 11);
}

TEST_F(Geometry_DotProductTest, NegativeValues)
{
    // Test with negative values
    core::Point s = {-1, -2};
    core::Point e = {-3, -4};
    core::Point o = {0, 0};

    double result = dotProduct(s, e, o);

    // Check the calculated dot product
    EXPECT_EQ(result, 11);
}

TEST_F(Geometry_DotProductTest, MixedValues)
{
    // Test with mixed positive and negative values
    core::Point s = {-1, 2};
    core::Point e = {3, -4};
    core::Point o = {0, 0};

    double result = dotProduct(s, e, o);

    // Check the calculated dot product
    EXPECT_EQ(result, -11);
}

TEST_F(Geometry_DotProductTest, ZeroValues)
{
    // Test with zero values
    core::Point s = {0, 0};
    core::Point e = {0, 0};
    core::Point o = {0, 0};

    double result = dotProduct(s, e, o);

    // Check the calculated dot product
    EXPECT_EQ(result, 0);
}

// 点积2
class Geometry_DotProductTest2 : public testing::Test
{
};

TEST_F(Geometry_DotProductTest2, PositiveValues)
{
    // Test with positive values
    core::Vector2D vec1 = {1, 2};
    core::Vector2D vec2 = {3, 4};

    double result = dotProduct(vec1, vec2);

    // Check the calculated dot product
    EXPECT_EQ(result, 11);
}

TEST_F(Geometry_DotProductTest2, NegativeValues)
{
    // Test with negative values
    core::Vector2D vec1 = {-1, -2};
    core::Vector2D vec2 = {-3, -4};

    double result = dotProduct(vec1, vec2);

    // Check the calculated dot product
    EXPECT_EQ(result, 11);
}

TEST_F(Geometry_DotProductTest2, MixedValues)
{
    // Test with mixed positive and negative values
    core::Vector2D vec1 = {-1, 2};
    core::Vector2D vec2 = {3, -4};

    double result = dotProduct(vec1, vec2);

    // Check the calculated dot product
    EXPECT_EQ(result, -11);
}

TEST_F(Geometry_DotProductTest2, ZeroValues)
{
    // Test with zero values
    core::Vector2D vec1 = {0, 0};
    core::Vector2D vec2 = {0, 0};

    double result = dotProduct(vec1, vec2);

    // Check the calculated dot product
    EXPECT_EQ(result, 0);
}

