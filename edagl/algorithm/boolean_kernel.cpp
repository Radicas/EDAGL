#include "boolean_kernel.h"

#include "core/arcpolygon.h"
#include "core/bbox.h"
#include "core/edge.h"
#include "core/edgenode.h"
#include "core/eventnode.h"
#include "core/linkednode.h"
#include "core/point.h"
#include "geometry/geometry.h"
#include "geometry/intersection.h"

#include <algorithm>

namespace edagl {
namespace algorithm {

int relatedEdgesBetweenAxis(const ArcPolygon& aArcPolygon, double aAxisSmall,
                            double aAxisBig, bool aXAxis,
                            std::vector<Edge>& aRelatedEdge) {
    auto* tail = aArcPolygon.getHeadNode();
    while (tail) {
        // 当前节点
        auto currPoint = tail->mData;
        auto* next = tail->mNext;
        if (next && !next->mIsAppendix) {
            // 下个节点
            auto nextPoint = next->mData;
            // 根据有效轴获取边的投影
            double startValue = aXAxis ? currPoint.x : currPoint.y;
            double endValue = aXAxis ? nextPoint.x : nextPoint.y;
            // 根据投影判断是否是相关边
            if ((startValue >= aAxisSmall && startValue <= aAxisBig) ||
                (endValue >= aAxisSmall && endValue <= aAxisBig) ||
                (startValue <= aAxisSmall && endValue >= aAxisBig)) {
                aRelatedEdge.emplace_back(currPoint, nextPoint);
            }
            // 尾指针后移
            tail = next;
        }
        if (next && next->mIsAppendix) {
            // 下一个是圆弧的附加点，要产生圆弧
            auto appendixPoint = next->mData;
            auto arcEndPoint = next->mNext->mData;
            // 计算包围盒
            auto arcBBox =
                geometry::bBoxOfArc(currPoint, arcEndPoint, appendixPoint);
            Point center{};
            double r;
            // 计算圆心、半径
            geometry::circleFrom3Points(currPoint, arcEndPoint, appendixPoint,
                                        center, r);
            double startValue = aXAxis ? arcBBox.getMinX() : arcBBox.getMinY();
            double endValue = aXAxis ? arcBBox.getMaxX() : arcBBox.getMaxY();
            // 根据有效轴判断是否是相关边
            if ((startValue >= aAxisSmall && startValue <= aAxisBig) ||
                (endValue >= aAxisSmall && endValue <= aAxisBig) ||
                (startValue <= aAxisSmall && endValue >= aAxisBig)) {
                aRelatedEdge.emplace_back(currPoint, arcEndPoint, center, true);
            }
            // 尾指针移动到圆弧终点
            tail = next->mNext;
        }

        if (tail == aArcPolygon.getHeadNode()) {
            break;
        }
    }
    return 0;
}

int pretreatment(const ArcPolygon& aArcPoly1, const ArcPolygon& aArcPoly2,
                 std::vector<EdgeNode>& aSequencedEdge1,
                 std::vector<EdgeNode>& aSequencedEdge2,
                 std::vector<Edge>& aRelatedEdge1,
                 std::vector<Edge>& aRelatedEdge2) {
    // 获取包围盒
    auto* bBox1 = aArcPoly1.getBBox();
    auto* bBox2 = aArcPoly2.getBBox();
    // 获取相交包围盒
    core::BBox newBBox;
    geometry::intersectsBBoxes(*bBox1, *bBox2, newBBox);
    // TODO: 包围盒没有处理包含、相切、相离等情况
    // 获取有效轴，true为X，false为Y
    bool effectiveX = (newBBox.getMaxX() - newBBox.getMinX()) <=
                      (newBBox.getMaxY() - newBBox.getMinY());

    // 根据有效轴获取投影数值
    double axisSmall{}, axisBig{};
    if (effectiveX) {
        std::cout << "有效轴: X\n" << std::endl;
        axisSmall = newBBox.getMinX();
        axisBig = newBBox.getMaxX();
    } else {
        std::cout << "有效轴: Y\n" << std::endl;
        axisSmall = newBBox.getMinY();
        axisBig = newBBox.getMaxY();
    }

    // 获取两个圆弧多边形的相关边
    relatedEdgesBetweenAxis(aArcPoly1, axisSmall, axisBig, effectiveX,
                            aRelatedEdge1);
    relatedEdgesBetweenAxis(aArcPoly2, axisSmall, axisBig, effectiveX,
                            aRelatedEdge2);
    std::cout << "原始多边形一相关边: " << aRelatedEdge1.size() << " 条\n";
    std::cout << "原始多边形二相关边: " << aRelatedEdge2.size() << " 条\n\n";
    // 根据相关边初始化序列边，插入额外信息
    initSequencedEdge(aSequencedEdge1, aRelatedEdge1);
    initSequencedEdge(aSequencedEdge2, aRelatedEdge2);
    std::cout << "分解后多边形一相关边: " << aRelatedEdge1.size() << " 条\n";
    std::cout << "分解后多边形二相关边: " << aRelatedEdge2.size() << " 条\n\n";
    // 重建序列边
    rebuildSequencedEdge(aSequencedEdge1, aSequencedEdge2);
    // TODO: 未完待续
#ifdef LOG_
    std::cout << "***************** pre treatment end ***************"
              << std::endl;
#endif
    return 0;
}

int initSequencedEdge(std::vector<EdgeNode>& aSequencedEdge,
                      const std::vector<Edge>& aRelatedEdge) {
    short int mark = 1;
    for (const auto& rEdge : aRelatedEdge) {
        if (rEdge.isArc() && !rEdge.isXMonotone()) {
            // 非X单调弧
            auto decomposedArcs = decomposeArc(rEdge);
            for (const auto& dArc : decomposedArcs) {
                EdgeNode ed(dArc, {}, mark);
                aSequencedEdge.emplace_back(std::move(ed));
            }
            // 切换开关
            mark = mark == 1 ? 2 : 1;
        } else {
            // 线段或者单调圆弧
            EdgeNode ed(rEdge, {}, 0);
            aSequencedEdge.emplace_back(std::move(ed));
        }
    }
    return 0;
}

void appendEventNode(std::priority_queue<EventNode>& aPq,
                     std::vector<EdgeNode>& aSequencedEdge, bool aFirst) {
    /**
     * 注意，扫描线算法处理不了竖直的线段
     * 本质问题在于，可能先找到右端点从而导致异常
     * 只要保证竖直线段先进入左端点即可
     */
    for (auto& edgeNode : aSequencedEdge) {
        auto& edge = edgeNode.getRelatedEdge();
        // 设置两个标签
        // 标签一：来自哪个多边形
        // 标签二：在序列中的位置
        edge.setIsFirst(aFirst);
        edge.setLocation((int)(&edgeNode - &aSequencedEdge[0]));
        // 添加左端点事件
        aPq.push(EventNode::createLeft(&edge));
        // 添加右端点事件
        aPq.push(EventNode::createRight(&edge));
    }
}

void rebuildSequencedEdge(std::vector<EdgeNode>& aSequencedEdge1,
                          std::vector<EdgeNode>& aSequencedEdge2) {
    // 声明存储事件节点的最小堆
    std::priority_queue<EventNode> pQueue;
    // 初始化两个序列边的事件
    appendEventNode(pQueue, aSequencedEdge1, true);
    appendEventNode(pQueue, aSequencedEdge2, false);
    std::cout << "事件数: " << pQueue.size() << "\n\n";
    // 初始化红黑树
    std::set<Edge*> rbTree{};
    while (!pQueue.empty()) {
        const EventNode& event = pQueue.top();
        std::cout << "事件点: " << *event.mPoint
                  << "\t状态: " << static_cast<int>(event.mPosition) << "\n";
        switch (event.mPosition) {
            case EventNode::EventPosition::LEFT: {
                handleLeftNode(rbTree, pQueue, event);
                break;
            }
            case EventNode::EventPosition::RIGHT: {
                handleRightNode(rbTree, pQueue, event);
                break;
            }
            case EventNode::EventPosition::INTERSECT: {
                handleIntersectNode(rbTree, pQueue, event);
                break;
            }
            default:
                break;
        }
        // pop完对象会析构，所以放后面处理
        pQueue.pop();
    }
}

std::vector<Edge> decomposeArc(const Edge& aEdge) {
    /**
     * 定理：一个非x单调圆弧，一定可以分解成两到三个x单调圆弧
     * 圆形是特殊圆弧
     */
    const auto& edgeCenter = aEdge.getCenter();
    bool isCW = aEdge.isCW();

    Point west(edgeCenter.x - aEdge.getRadius(), edgeCenter.y);
    Point east(edgeCenter.x + aEdge.getRadius(), edgeCenter.y);
    bool westIn = geometry::isPointInArcRangeExceptEdge(
        edgeCenter, aEdge.getStartAngle(), aEdge.getSweepAngle(), isCW, west);
    bool eastIn = geometry::isPointInArcRangeExceptEdge(
        edgeCenter, aEdge.getStartAngle(), aEdge.getSweepAngle(), isCW, east);

    // TODO: NOTE: 圆形要特殊处理
    if (westIn && eastIn) {
        return decomposeArcToThree(aEdge, east, west);
    }
    if (westIn && !eastIn) {
        return decomposeArcToTwo(aEdge, west);
    }
    if (!westIn && eastIn) {
        return decomposeArcToTwo(aEdge, east);
    }
    std::cerr << "decomposeArc error " << __FILE_NAME__ << __LINE__
              << std::endl;
    throw;
    return {};
}

std::vector<Edge> decomposeArcToTwo(const Edge& aEdge,
                                    const Point& aBreakPoint) {
    /**
    * 分析：
    * 分解为两段圆弧
    * 为真的顶点一定是第二个圆弧的起点
    */
    // 第一个圆弧
    Edge firstEdge(aEdge.getStart(), aBreakPoint, aEdge.getCenter(), true,
                   aEdge.isCW());
    // 第二个圆弧
    Edge secondEdge(aBreakPoint, aEdge.getEnd(), aEdge.getCenter(), true,
                    aEdge.isCW());

    std::vector<Edge> res;
    res.emplace_back(firstEdge);
    res.emplace_back(secondEdge);
    return res;
}

std::vector<Edge> decomposeArcToThree(const Edge& aEdge, const Point& aEast,
                                      const Point& aWest) {
    /**
    * 分析：
    * 分解为三段圆弧
    * 原始圆弧的两个端点一定在圆心y轴的同侧
    * 第一段圆弧的起始角一定是原始圆弧的起始角
    * 第三段圆弧的终止角一定是原始圆弧的终止角
    * 三段圆弧的方向不变
    * 目标就是确定第一段圆弧的终点、第三段圆弧的起点
    * 只要确定Edge的起点、终点、附加点即可
    * 如果顺时针，且起点y坐标在圆心y轴下方，则左边的是第二条弧的起点
    * 如果顺时针，且起点y坐标在圆心y轴上方，则右边的是第二条弧的起点
    * 如果逆时针，且起点y坐标在圆心y轴下方，则右边的是第二条弧的起点
    * 如果逆时针，且起点y坐标在圆心y轴上方，则左边的是第二条弧的起点
    */

    const auto& edgeStart = aEdge.getStart();
    const auto& edgeEnd = aEdge.getEnd();
    const auto& edgeCenter = aEdge.getCenter();
    bool isCW = aEdge.isCW();

    Point secondStart{}, secondEnd{};
    if ((isCW && edgeStart.y < edgeCenter.y) ||
        (!isCW && edgeStart.y > edgeCenter.y)) {
        secondStart = aWest;
        secondEnd = aEast;
    } else if ((isCW && edgeStart.y > edgeCenter.y) ||
               (!isCW && edgeStart.y < edgeCenter.y)) {
        secondStart = aEast;
        secondEnd = aWest;
    } else {
        std::cerr << "decomposeArcToThree error " << __FILE_NAME__ << __LINE__
                  << std::endl;
        throw;
    }

    // 第一个圆弧
    Edge firstEdge(edgeStart, secondStart, aEdge.getCenter(), true, isCW);
    // 第二个圆弧
    Edge secondEdge(secondStart, secondEnd, aEdge.getCenter(), true, isCW);
    // 第三个圆弧
    Edge thirdEdge(secondEnd, edgeEnd, aEdge.getCenter(), true, isCW);

    std::vector<Edge> res;
    res.emplace_back(std::move(firstEdge));
    res.emplace_back(std::move(secondEdge));
    res.emplace_back(std::move(thirdEdge));
    return res;
}

void handleLeftNode(std::set<Edge*>& rbTree,
                    std::priority_queue<EventNode>& pQueue,
                    const EventNode& eventNode) {
    rbTree.insert(eventNode.mEdge);
    auto it = rbTree.find(eventNode.mEdge);
    if (it != rbTree.end()) {
        // 找到前一个元素
        if (it != rbTree.begin()) {
            auto prevIt = std::prev(it);
        } else {
        }

        // 找到后一个元素
        auto nextIt = std::next(it);
        if (nextIt != rbTree.end()) {
        } else {
        }
    } else {
        std::cout << "没有此元素\n";
    }
}

void handleRightNode(std::set<Edge*>& rbTree,
                     std::priority_queue<EventNode>& pQueue,
                     const EventNode& eventNode) {}

void handleIntersectNode(std::set<Edge*>& rbTree,
                         std::priority_queue<EventNode>& pQueue,
                         const EventNode& eventNode) {}

int constructProcessedArcPolygon() {
    return 0;
}

PolygonsWithHoles booleanOperation(const ArcPolygon& ap1, const ArcPolygon& ap2,
                                   Traits traits) {
    std::vector<EdgeNode> sequencedEdge1;
    std::vector<EdgeNode> sequencedEdge2;
    std::vector<Edge> relatedEdge1;
    std::vector<Edge> relatedEdge2;

    pretreatment(ap1, ap2, sequencedEdge1, sequencedEdge2, relatedEdge1,
                 relatedEdge2);
    // TODO:
    // 组织好数据，返回运算结果
}

}  // namespace algorithm
}  // namespace edagl