#include <gtest/gtest.h>
#include "core/arcpolygon.h"
#include "core/bbox.h"
#include "core/linkednode.h"
#include "core/point.h"
#include "engine/geometry.h"

using namespace edagl::core;

class Core_ArcPolygonTest : public testing::Test {};
//
//TEST_F(Core_ArcPolygonTest, generateBBox) {
//
//    std::vector<Point> points = {{0.0, 400.0},  {-400.0, 400.0}, {-400.0, 0.0},
//                                 {-200.0, 0.0}, {0.0, -200},     {0, 200}};
//    auto* head = new LinkedNode(points[0]);
//    auto* tail = head;
//    for (int i = 1; i < 6; i++) {
//        bool appendix = i == 4;
//        auto* node =
//            new LinkedNode(points[i], appendix, false, false, nullptr, nullptr);
//        tail->mNext = node;
//        node->mPrev = tail;
//        tail = node;
//    }
//    auto* poly = new ArcPolygon(head);
//    EXPECT_EQ(poly->getHeadNode(), head);
//}
//
//TEST_F(Core_ArcPolygonTest, getHeadNode) {
//    std::vector<Point> points = {{0.0, 400.0},  {-400.0, 400.0}, {-400.0, 0.0},
//                                 {-200.0, 0.0}, {0.0, -200},     {0, 200}};
//    auto* head = new LinkedNode(points[0]);
//    auto* tail = head;
//    for (int i = 1; i < 6; i++) {
//        bool appendix = i == 4;
//        auto* node =
//            new LinkedNode(points[i], appendix, false, false, nullptr, nullptr);
//        tail->mNext = node;
//        node->mPrev = tail;
//        tail = node;
//    }
//    auto* poly = new ArcPolygon(head);
//    EXPECT_EQ(poly->getHeadNode(), head);
//}

TEST_F(Core_ArcPolygonTest, getBBox) {
    std::vector<Point> points = {
        {-6.0, 6.0},  {-9.0, 3.0},  {-8.5000987014026, 1.3418364123992},
        {-6.0, 0.0},  {-6.0, -1.0}, {-3.2214664261134, -2.842250111774},
        {-2.0, -1.0}, {-3.0, 1.0},  {-1.3254293797126, 2.8711037876389},
        {1.0, 3.0},   {-2.0, 6.0},  {-4.0, 8.0},
        {-6.0, 6.0}};
    auto* head = LinkedNode::constructLinkedNodes(points);
    auto* it = head;

    int count = 0;
    while (it != nullptr) {
        if (++count > 12) {
            break;
        }
        if (count == 3 || count == 6 || count == 9 || count == 12) {
            it->mIsAppendix = true;
        }
        it = it->mNext;
    }

    auto* poly = new ArcPolygon(head);
    auto* bbox = poly->getBBox();
    ASSERT_TRUE(bbox);
    EXPECT_TRUE(std::abs(bbox->getMinX() - (-9.0)) < edagl::EPSILON);
    EXPECT_TRUE(std::abs(bbox->getMaxX() - 1.0) < edagl::EPSILON);
    EXPECT_TRUE(std::abs(bbox->getMinY() - (-3.0)) < edagl::EPSILON);
    EXPECT_TRUE(std::abs(bbox->getMaxY() - 8.0) < edagl::EPSILON);
}