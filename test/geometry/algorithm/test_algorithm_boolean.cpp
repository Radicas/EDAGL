#include <gtest/gtest.h>
#include "algorithm/boolean.h"
#include "core/arcpolygon.h"
#include "core/edge.h"
#include "core/linkednode.h"

using namespace core;
using namespace algorithm;

class Algorithm_Boolean : public ::testing::Test {
   public:
    // 共享资源
    ArcPolygon* poly1 = nullptr;
    ArcPolygon* poly2 = nullptr;
    ArcPolygon* poly3 = nullptr;
    ArcPolygon* poly4 = nullptr;
    Algorithm_Boolean() {
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

TEST_F(Algorithm_Boolean, relatedEdgesBetweenAxis) {
    std::vector<Edge> relatedEdges{};
    relatedEdgesBetweenAxis(poly1, 0.1, 0.2, true, relatedEdges);
    EXPECT_EQ(relatedEdges.size(), 1);
}

TEST_F(Algorithm_Boolean, relatedEdgesBetweenAxis2) {
    std::vector<Edge> relatedEdges{};
    relatedEdgesBetweenAxis(poly3, 0.0, 5.0, true, relatedEdges);
    EXPECT_EQ(relatedEdges.size(), 4);
}

class Algorithm_Boolean_DecomposeArc : public testing::Test {};

TEST_F(Algorithm_Boolean_DecomposeArc, test1) {
//    Edge edge({-200.0, 0.0}, {0.0, 200.0}, {0.0, -200.0}, true, true, false);
//    auto res = algorithm::decomposeArc(edge);
}