#include "engine/geometry.h"
#include <gtest/gtest.h>

using namespace core;
using namespace geometry;

// 点积1
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

// 差积1
class Geometry_CrossProductTest : public testing::Test {};

TEST_F(Geometry_CrossProductTest, PositiveValues) {
    // Test with positive values
    core::Point aS = {1, 2};
    core::Point aE = {3, 4};
    core::Point aO = {0, 0};

    double result = crossProduct(aS, aE, aO);

    // Check the calculated cross product
    EXPECT_EQ(result, -2);
}

TEST_F(Geometry_CrossProductTest, NegativeValues) {
    // Test with negative values
    core::Point aS = {-1, -2};
    core::Point aE = {-3, -4};
    core::Point aO = {0, 0};

    double result = crossProduct(aS, aE, aO);

    // Check the calculated cross product
    EXPECT_EQ(result, -2);
}

TEST_F(Geometry_CrossProductTest, MixedValues) {
    // Test with mixed positive and negative values
    core::Point aS = {-1, 2};
    core::Point aE = {3, -4};
    core::Point aO = {0, 0};

    double result = crossProduct(aS, aE, aO);

    // Check the calculated cross product
    EXPECT_EQ(result, -2);
}

TEST_F(Geometry_CrossProductTest, ZeroValues) {
    // Test with zero values
    core::Point aS = {0, 0};
    core::Point aE = {0, 0};
    core::Point aO = {0, 0};

    double result = crossProduct(aS, aE, aO);

    // Check the calculated cross product
    EXPECT_EQ(result, 0);
}

// 差积2
class Geometry_CrossProductTest2 : public testing::Test {};

TEST_F(Geometry_CrossProductTest2, PositiveValues) {
    // Test with positive values
    core::Vector2D aVec1 = {1, 2};
    core::Vector2D aVec2 = {3, 4};

    double result = crossProduct(aVec1, aVec2);

    // Check the calculated cross product
    EXPECT_EQ(result, -2);
}

TEST_F(Geometry_CrossProductTest2, NegativeValues) {
    // Test with negative values
    core::Vector2D aVec1 = {-1, -2};
    core::Vector2D aVec2 = {-3, -4};

    double result = crossProduct(aVec1, aVec2);

    // Check the calculated cross product
    EXPECT_EQ(result, -2);
}

TEST_F(Geometry_CrossProductTest2, MixedValues) {
    // Test with mixed positive and negative values
    core::Vector2D aVec1 = {-1, 2};
    core::Vector2D aVec2 = {3, -4};

    double result = crossProduct(aVec1, aVec2);

    // Check the calculated cross product
    EXPECT_EQ(result, -2);
}

TEST_F(Geometry_CrossProductTest2, ZeroValues) {
    // Test with zero values
    core::Vector2D aVec1 = {0, 0};
    core::Vector2D aVec2 = {0, 0};

    double result = crossProduct(aVec1, aVec2);

    // Check the calculated cross product
    EXPECT_EQ(result, 0);
}