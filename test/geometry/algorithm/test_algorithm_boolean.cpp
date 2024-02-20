#include <gtest/gtest.h>
#include "algorithm/boolean.h"
#include "core/arcpolygon.h"
#include "core/edge.h"
#include "core/linkednode.h"

#include <cmath>

using namespace edagl::core;
using namespace algorithm;

// 根据有效轴获取相关边
class Algorithm_BooleanRelatedEdges : public ::testing::Test {
   public:
    // 共享资源
    ArcPolygon* poly1 = nullptr;
    ArcPolygon* poly2 = nullptr;
    ArcPolygon* poly3 = nullptr;
    ArcPolygon* poly4 = nullptr;
    Algorithm_BooleanRelatedEdges() {
        // 初始图形坐标点
        std::vector<Point> poly1Points = {{0.0, 0.2},  {0.0, 0.4},  {-0.4, 0.4},
                                          {-0.4, 0.0}, {-0.2, 0.0}, {0.0, -0.2},
                                          {0.0, 0.2}};
        std::vector<Point> poly2Points = {{0.5, 0.0}, {0.7, 0.0}, {0.7, 0.4},
                                          {0.3, 0.4}, {0.3, 0.2}, {0.3, -0.2},
                                          {0.5, 0.0}};
        std::vector<Point> poly3Points = {{-2.0, 4.0}, {-3.0, -2.0},
                                          {5.0, -1.0}, {-1.0, -1.0},
                                          {1.0, 2.0},  {-2.0, 4.0}};
        std::vector<Point> poly4Points = {
            {0.0, 4.0}, {0.0, -3.0}, {7.0, -3.0}, {7.0, 4.0}, {0.0, 4.0}};

        // 构建环形双向链表
        auto* linkedNode1 = LinkedNode::constructLinkedNodes(poly1Points);
        auto* linkedNode2 = LinkedNode::constructLinkedNodes(poly2Points);
        auto* linkedNode3 = LinkedNode::constructLinkedNodes(poly3Points);
        auto* linkedNode4 = LinkedNode::constructLinkedNodes(poly4Points);

        // 初始化附加点
        int count = 0;
        auto lnTail1 = linkedNode1;
        auto lnTail2 = linkedNode2;
        while (true) {
            count++;
            if (count == 6) {
                lnTail1->mIsAppendix = true;
                lnTail2->mIsAppendix = true;
            }
            lnTail1 = lnTail1->mNext;
            lnTail2 = lnTail2->mNext;
            if (lnTail1 == linkedNode1 || lnTail2 == linkedNode2) {
                break;
            }
        }

        // 构造圆弧多边形
        poly1 = new ArcPolygon(linkedNode1);
        poly2 = new ArcPolygon(linkedNode2);
        poly3 = new ArcPolygon(linkedNode3);
        poly4 = new ArcPolygon(linkedNode4);
    }
};

TEST_F(Algorithm_BooleanRelatedEdges, relatedEdgesBetweenAxis) {
    std::vector<Edge> relatedEdges{};
    relatedEdgesBetweenAxis(poly1, 0.1, 0.2, true, relatedEdges);
    EXPECT_EQ(relatedEdges.size(), 1);
}

TEST_F(Algorithm_BooleanRelatedEdges, relatedEdgesBetweenAxis2) {
    std::vector<Edge> relatedEdges{};
    relatedEdgesBetweenAxis(poly3, 0.0, 5.0, true, relatedEdges);
    EXPECT_EQ(relatedEdges.size(), 4);
}

// 分解X单调圆弧
class Algorithm_Boolean_DecomposeArc : public testing::Test {};

TEST_F(Algorithm_Boolean_DecomposeArc, two1) {
    Edge edge({-200.0, 0.0}, {0.0, 200.0}, {0.0, 0.0}, true, false);
    auto res = algorithm::decomposeArc(edge);
    EXPECT_DOUBLE_EQ(res[0].getStart().x, -200.0);
    EXPECT_DOUBLE_EQ(res[0].getStart().y, 0.0);
    EXPECT_DOUBLE_EQ(res[0].getEnd().x, 200.0);
    EXPECT_DOUBLE_EQ(res[0].getEnd().y, 0.0);
    EXPECT_DOUBLE_EQ(res[0].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[0].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[0].getStartAngle(), M_PI);
    EXPECT_DOUBLE_EQ(res[0].getEndAngle(), 0.0);
    EXPECT_DOUBLE_EQ(res[0].getSweepAngle(), M_PI);
    EXPECT_DOUBLE_EQ(res[0].getRadius(), 200.0);
    EXPECT_TRUE(res[0].isXMonotone());
    EXPECT_TRUE(res[0].isArc());
    EXPECT_FALSE(res[0].isCW());

    EXPECT_DOUBLE_EQ(res[1].getStart().x, 200.0);
    EXPECT_DOUBLE_EQ(res[1].getStart().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getEnd().x, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getEnd().y, 200.0);
    EXPECT_DOUBLE_EQ(res[1].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getStartAngle(), 0.0);
    EXPECT_DOUBLE_EQ(res[1].getEndAngle(), M_PI_2);
    EXPECT_DOUBLE_EQ(res[1].getSweepAngle(), M_PI_2);
    EXPECT_DOUBLE_EQ(res[1].getRadius(), 200.0);
    EXPECT_TRUE(res[1].isXMonotone());
    EXPECT_TRUE(res[1].isArc());
    EXPECT_FALSE(res[1].isCW());
}

TEST_F(Algorithm_Boolean_DecomposeArc, two2) {
    Edge edge({0.0, 200.0}, {-200.0, 0.0}, {0.0, 0.0}, true, true);
    auto res = algorithm::decomposeArc(edge);

    EXPECT_DOUBLE_EQ(res[0].getStart().x, 0.0);
    EXPECT_DOUBLE_EQ(res[0].getStart().y, 200.0);
    EXPECT_DOUBLE_EQ(res[0].getEnd().x, 200.0);
    EXPECT_DOUBLE_EQ(res[0].getEnd().y, 0.0);
    EXPECT_DOUBLE_EQ(res[0].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[0].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[0].getStartAngle(), M_PI_2);
    EXPECT_DOUBLE_EQ(res[0].getEndAngle(), 0.0);
    EXPECT_DOUBLE_EQ(res[0].getSweepAngle(), M_PI_2);
    EXPECT_DOUBLE_EQ(res[0].getRadius(), 200.0);
    EXPECT_TRUE(res[0].isXMonotone());
    EXPECT_TRUE(res[0].isArc());
    EXPECT_TRUE(res[0].isCW());

    EXPECT_DOUBLE_EQ(res[1].getStart().x, 200.0);
    EXPECT_DOUBLE_EQ(res[1].getStart().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getEnd().x, -200.0);
    EXPECT_DOUBLE_EQ(res[1].getEnd().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getStartAngle(), 0.0);
    EXPECT_DOUBLE_EQ(res[1].getEndAngle(), M_PI);
    EXPECT_DOUBLE_EQ(res[1].getSweepAngle(), M_PI);
    EXPECT_DOUBLE_EQ(res[1].getRadius(), 200.0);
    EXPECT_TRUE(res[1].isXMonotone());
    EXPECT_TRUE(res[1].isArc());
    EXPECT_TRUE(res[1].isCW());
}

TEST_F(Algorithm_Boolean_DecomposeArc, three1) {
    Edge edge({-150.0, 100.0}, {100.0, 150.0}, {0, 0}, true, false);
    auto res = algorithm::decomposeArc(edge);

    // 第一段
    EXPECT_DOUBLE_EQ(res[0].getStart().x, -150.0);
    EXPECT_DOUBLE_EQ(res[0].getStart().y, 100.0);
    EXPECT_DOUBLE_EQ(res[0].getEnd().x, -180.2775637731995);
    EXPECT_DOUBLE_EQ(res[0].getEnd().y, 0.0);
    EXPECT_DOUBLE_EQ(res[0].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[0].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[0].getStartAngle(), 146.3099324740202 * M_PI / 180.0);
    EXPECT_DOUBLE_EQ(res[0].getEndAngle(), M_PI);
    EXPECT_DOUBLE_EQ(res[0].getSweepAngle(),
                     M_PI - (146.3099324740202 * M_PI / 180.0));
    EXPECT_DOUBLE_EQ(res[0].getRadius(), 180.2775637731995);
    EXPECT_TRUE(res[0].isXMonotone());
    EXPECT_TRUE(res[0].isArc());
    EXPECT_FALSE(res[0].isCW());

    // 第二段
    EXPECT_DOUBLE_EQ(res[1].getStart().x, -180.2775637731995);
    EXPECT_DOUBLE_EQ(res[1].getStart().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getEnd().x, 180.2775637731995);
    EXPECT_DOUBLE_EQ(res[1].getEnd().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getStartAngle(), M_PI);
    EXPECT_DOUBLE_EQ(res[1].getEndAngle(), 0.0);
    EXPECT_DOUBLE_EQ(res[1].getSweepAngle(), M_PI);
    EXPECT_DOUBLE_EQ(res[1].getRadius(), 180.2775637731995);
    EXPECT_TRUE(res[1].isXMonotone());
    EXPECT_TRUE(res[1].isArc());
    EXPECT_FALSE(res[1].isCW());

    // 第三段
    EXPECT_DOUBLE_EQ(res[2].getStart().x, 180.2775637731995);
    EXPECT_DOUBLE_EQ(res[2].getStart().y, 0.0);
    EXPECT_DOUBLE_EQ(res[2].getEnd().x, 100.0);
    EXPECT_DOUBLE_EQ(res[2].getEnd().y, 150.0);
    EXPECT_DOUBLE_EQ(res[2].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[2].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[2].getStartAngle(), 0.0);
    EXPECT_DOUBLE_EQ(res[2].getEndAngle(), 56.3099324740202 * M_PI / 180.0);
    EXPECT_DOUBLE_EQ(res[2].getSweepAngle(), 56.3099324740202 * M_PI / 180.0);
    EXPECT_DOUBLE_EQ(res[2].getRadius(), 180.2775637731995);
    EXPECT_TRUE(res[2].isXMonotone());
    EXPECT_TRUE(res[2].isArc());
    EXPECT_FALSE(res[2].isCW());
}

TEST_F(Algorithm_Boolean_DecomposeArc, three2) {
    Edge edge({100.0, 150.0}, {-150.0, 100.0}, {0, 0}, true, true);
    auto res = algorithm::decomposeArc(edge);

    // 第一段
    EXPECT_DOUBLE_EQ(res[0].getStart().x, 100.0);
    EXPECT_DOUBLE_EQ(res[0].getStart().y, 150.0);
    EXPECT_DOUBLE_EQ(res[0].getEnd().x, 180.2775637731995);
    EXPECT_DOUBLE_EQ(res[0].getEnd().y, 0.0);
    EXPECT_DOUBLE_EQ(res[0].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[0].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[0].getStartAngle(), 56.3099324740202 * M_PI / 180.0);
    EXPECT_DOUBLE_EQ(res[0].getEndAngle(), 0.0);
    EXPECT_DOUBLE_EQ(res[0].getSweepAngle(), 56.3099324740202 * M_PI / 180.0);
    EXPECT_DOUBLE_EQ(res[0].getRadius(), 180.2775637731995);
    EXPECT_TRUE(res[0].isXMonotone());
    EXPECT_TRUE(res[0].isArc());
    EXPECT_TRUE(res[0].isCW());

    // 第二段
    EXPECT_DOUBLE_EQ(res[1].getStart().x, 180.2775637731995);
    EXPECT_DOUBLE_EQ(res[1].getStart().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getEnd().x, -180.2775637731995);
    EXPECT_DOUBLE_EQ(res[1].getEnd().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[1].getStartAngle(), 0.0);
    EXPECT_DOUBLE_EQ(res[1].getEndAngle(), M_PI);
    EXPECT_DOUBLE_EQ(res[1].getSweepAngle(), M_PI);
    EXPECT_DOUBLE_EQ(res[1].getRadius(), 180.2775637731995);
    EXPECT_TRUE(res[1].isXMonotone());
    EXPECT_TRUE(res[1].isArc());
    EXPECT_TRUE(res[1].isCW());

    // 第三段
    EXPECT_DOUBLE_EQ(res[2].getStart().x, -180.2775637731995);
    EXPECT_DOUBLE_EQ(res[2].getStart().y, 0.0);
    EXPECT_DOUBLE_EQ(res[2].getEnd().x, -150.0);
    EXPECT_DOUBLE_EQ(res[2].getEnd().y, 100.0);
    EXPECT_DOUBLE_EQ(res[2].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[2].getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(res[2].getStartAngle(), M_PI);
    EXPECT_DOUBLE_EQ(res[2].getEndAngle(), 146.3099324740202 * M_PI / 180.0);
    EXPECT_DOUBLE_EQ(res[2].getSweepAngle(),
                     (180.0 - 146.3099324740202) * M_PI / 180.0);
    EXPECT_DOUBLE_EQ(res[2].getRadius(), 180.2775637731995);
    EXPECT_TRUE(res[2].isXMonotone());
    EXPECT_TRUE(res[2].isArc());
    EXPECT_TRUE(res[2].isCW());
}