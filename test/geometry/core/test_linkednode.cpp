#include "core/linkednode.h"
#include <gtest/gtest.h>

using namespace core;

class Core_LinkedNodeTest : public testing::Test {
public:
  void useConstructLinkedNodes() {}
};

TEST(Core_LinkedNodeTest, DefaultConstructor) {
  auto *node = new LinkedNode();

  // Check default values
  EXPECT_EQ(node->mData, Point(0.0, 0.0));
  EXPECT_FALSE(node->mIsAppendix);
  EXPECT_FALSE(node->mIsCrossing);
  EXPECT_FALSE(node->mEE);
  EXPECT_EQ(node->mPrev, nullptr);
  EXPECT_EQ(node->mNext, nullptr);
}

TEST(Core_LinkedNodeTest, DataConstructor) {
  Point data(1.0, 2.0);
  auto *node = new LinkedNode(data);

  // Check if the data is set correctly
  EXPECT_EQ(node->mData, data);
  EXPECT_FALSE(node->mIsAppendix);
  EXPECT_FALSE(node->mIsCrossing);
  EXPECT_FALSE(node->mEE);
  EXPECT_EQ(node->mPrev, nullptr);
  EXPECT_EQ(node->mNext, nullptr);
}

TEST(Core_LinkedNodeTest, FullConstructor) {
  Point data(1.0, 2.0);
  auto *prev = new LinkedNode();
  auto *next = new LinkedNode();
  LinkedNode node(data, true, true, true, prev, next);

  // Check if all the values are set correctly
  EXPECT_EQ(node.mData, data);
  EXPECT_TRUE(node.mIsAppendix);
  EXPECT_TRUE(node.mIsCrossing);
  EXPECT_TRUE(node.mEE);
  EXPECT_EQ(node.mPrev, prev);
  EXPECT_EQ(node.mNext, next);
}

TEST(Core_LinkedNodeTest, MoveConstructor) {
  Point data(1.0, 2.0);
  auto *node1 = new LinkedNode(data);
  auto *node2 = new LinkedNode(std::move(*node1));

  // Check if the data is moved correctly
  EXPECT_EQ(node2->mData, data);
  EXPECT_FALSE(node2->mIsAppendix);
  EXPECT_FALSE(node2->mIsCrossing);
  EXPECT_FALSE(node2->mEE);
  EXPECT_EQ(node2->mPrev, nullptr);
  EXPECT_EQ(node2->mNext, nullptr);
}

TEST(Core_LinkedNodeTest, MoveAssignmentOperator) {
  Point data(1.0, 2.0);
  LinkedNode node1(data);
  LinkedNode node2;

  node2 = std::move(node1);

  // Check if the data is moved correctly
  EXPECT_EQ(node2.mData, data);
  EXPECT_FALSE(node2.mIsAppendix);
  EXPECT_FALSE(node2.mIsCrossing);
  EXPECT_FALSE(node2.mEE);
  EXPECT_EQ(node2.mPrev, nullptr);
  EXPECT_EQ(node2.mNext, nullptr);
}

TEST(Core_LinkedNodeTest, EqualityOperator) {
  Point data1(1.0, 2.0);
  Point data2(3.0, 4.0);
  LinkedNode node1(data1);
  LinkedNode node2(data1);
  LinkedNode node3(data2);

  // Check equality of nodes with the same data
  EXPECT_EQ(node1, node2);
}

TEST(Core_LinkedNodeTest, ConstructLinkedNodes) {
  std::vector<Point> points = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};

  LinkedNode *head = LinkedNode::constructLinkedNodes(points);

  // Check if the linked nodes are constructed correctly
  LinkedNode *current = head;
  for (const auto &point : points) {
    EXPECT_EQ(current->mData, point);
    current = current->mNext;
  }

  // Check if the last node is nullptr
  EXPECT_EQ(current, nullptr);

  // Clean up memory
  current = head;
  while (current) {
    LinkedNode *next = current->mNext;
    delete current;
    current = next;
  }
}