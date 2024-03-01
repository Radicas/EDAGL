#include <gtest/gtest.h>
#include "geometry/geometry.h"

using namespace edagl::core;
using namespace edagl::geometry;

// 点积1
class Geometry_DotProductTest : public testing::Test {};

TEST_F(Geometry_DotProductTest, PositiveValues) {
    // Test with positive values
    Point s = {1, 2};
    Point e = {3, 4};
    Point o = {0, 0};

    double result = dotProduct(s, e, o);

    // Check the calculated dot product
    EXPECT_EQ(result, 11);
}

TEST_F(Geometry_DotProductTest, NegativeValues) {
    // Test with negative values
    Point s = {-1, -2};
    Point e = {-3, -4};
    Point o = {0, 0};

    double result = dotProduct(s, e, o);

    // Check the calculated dot product
    EXPECT_EQ(result, 11);
}

TEST_F(Geometry_DotProductTest, MixedValues) {
    // Test with mixed positive and negative values
    Point s = {-1, 2};
    Point e = {3, -4};
    Point o = {0, 0};

    double result = dotProduct(s, e, o);

    // Check the calculated dot product
    EXPECT_EQ(result, -11);
}

TEST_F(Geometry_DotProductTest, ZeroValues) {
    // Test with zero values
    Point s = {0, 0};
    Point e = {0, 0};
    Point o = {0, 0};

    double result = dotProduct(s, e, o);

    // Check the calculated dot product
    EXPECT_EQ(result, 0);
}

// 点积2
class Geometry_DotProductTest2 : public testing::Test {};

TEST_F(Geometry_DotProductTest2, PositiveValues) {
    // Test with positive values
    Vector2D vec1 = {1, 2};
    Vector2D vec2 = {3, 4};

    double result = dotProduct(vec1, vec2);

    // Check the calculated dot product
    EXPECT_EQ(result, 11);
}

TEST_F(Geometry_DotProductTest2, NegativeValues) {
    // Test with negative values
    Vector2D vec1 = {-1, -2};
    Vector2D vec2 = {-3, -4};

    double result = dotProduct(vec1, vec2);

    // Check the calculated dot product
    EXPECT_EQ(result, 11);
}

TEST_F(Geometry_DotProductTest2, MixedValues) {
    // Test with mixed positive and negative values
    Vector2D vec1 = {-1, 2};
    Vector2D vec2 = {3, -4};

    double result = dotProduct(vec1, vec2);

    // Check the calculated dot product
    EXPECT_EQ(result, -11);
}

TEST_F(Geometry_DotProductTest2, ZeroValues) {
    // Test with zero values
    Vector2D vec1 = {0, 0};
    Vector2D vec2 = {0, 0};

    double result = dotProduct(vec1, vec2);

    // Check the calculated dot product
    EXPECT_EQ(result, 0);
}

// 差积1
class Geometry_CrossProductTest : public testing::Test {};

TEST_F(Geometry_CrossProductTest, PositiveValues) {
    // Test with positive values
    Point aS = {1, 2};
    Point aE = {3, 4};
    Point aO = {0, 0};

    double result = crossProduct(aS, aE, aO);

    // Check the calculated cross product
    EXPECT_EQ(result, -2);
}

TEST_F(Geometry_CrossProductTest, NegativeValues) {
    // Test with negative values
    Point aS = {-1, -2};
    Point aE = {-3, -4};
    Point aO = {0, 0};

    double result = crossProduct(aS, aE, aO);

    // Check the calculated cross product
    EXPECT_EQ(result, -2);
}

TEST_F(Geometry_CrossProductTest, MixedValues) {
    // Test with mixed positive and negative values
    Point aS = {-1, 2};
    Point aE = {3, -4};
    Point aO = {0, 0};

    double result = crossProduct(aS, aE, aO);

    // Check the calculated cross product
    EXPECT_EQ(result, -2);
}

TEST_F(Geometry_CrossProductTest, ZeroValues) {
    // Test with zero values
    Point aS = {0, 0};
    Point aE = {0, 0};
    Point aO = {0, 0};

    double result = crossProduct(aS, aE, aO);

    // Check the calculated cross product
    EXPECT_EQ(result, 0);
}

// 差积2
class Geometry_CrossProductTest2 : public testing::Test {};

TEST_F(Geometry_CrossProductTest2, PositiveValues) {
    // Test with positive values
    Vector2D aVec1 = {1, 2};
    Vector2D aVec2 = {3, 4};

    double result = crossProduct(aVec1, aVec2);

    // Check the calculated cross product
    EXPECT_EQ(result, -2);
}

TEST_F(Geometry_CrossProductTest2, NegativeValues) {
    // Test with negative values
    Vector2D aVec1 = {-1, -2};
    Vector2D aVec2 = {-3, -4};

    double result = crossProduct(aVec1, aVec2);

    // Check the calculated cross product
    EXPECT_EQ(result, -2);
}

TEST_F(Geometry_CrossProductTest2, MixedValues) {
    // Test with mixed positive and negative values
    Vector2D aVec1 = {-1, 2};
    Vector2D aVec2 = {3, -4};

    double result = crossProduct(aVec1, aVec2);

    // Check the calculated cross product
    EXPECT_EQ(result, -2);
}

TEST_F(Geometry_CrossProductTest2, ZeroValues) {
    // Test with zero values
    Vector2D aVec1 = {0, 0};
    Vector2D aVec2 = {0, 0};

    double result = crossProduct(aVec1, aVec2);

    // Check the calculated cross product
    EXPECT_EQ(result, 0);
}