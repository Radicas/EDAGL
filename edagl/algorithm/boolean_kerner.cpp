#include "boolean_kerner.h"

#include "core/arcpolygon.h"
#include "core/bbox.h"
#include "core/edge.h"
#include "core/edgenode.h"
#include "core/eventnode.h"
#include "core/linkednode.h"
#include "core/point.h"
#include "geometry/geometry.h"
#include "geometry/intersection.h"
#include "utils/Timer.h"

#include <algorithm>

namespace algorithm {

using namespace edagl::core;
using namespace edagl::geometry;

int relatedEdgesBetweenAxis(ArcPolygon* aArcPolygon, double aAxisSmall,
                            double aAxisBig, bool aXAxis,
                            std::vector<Edge>& aRelatedEdge) {
    auto* tail = aArcPolygon->getHeadNode();
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
            auto arcBBox = bBoxOfArc(currPoint, arcEndPoint, appendixPoint);
            Point center{};
            double r;
            // 计算圆心、半径
            circleFrom3Points(currPoint, arcEndPoint, appendixPoint, center, r);
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

        if (tail == aArcPolygon->getHeadNode()) {
            break;
        }
    }

    return 0;
}

/**
*  逻辑：
*  获取两个圆弧多边形的包围盒
*  根据包围盒，计算出有效轴是x还是y
*  根据包围盒的边界值和有效轴，找出两个圆弧多边形各自的相关边
*  这里的相关边，可能是线段，也可能是圆弧
*  创建两个空序列，用于存放多边形的边以及附带信息
*  根据相关边，初始化边序列
*  排序边序列，所有端点存到优先队列Q里
*  遍历Q
*      如果点是线段的左端点
*          将线段赋予两个标签，将线段存到红黑树里
*          如果线段的第一个标签，和前或后的两个线段的标签不一致
*              如过此线段和前后两个点组成的线段相交
*                  将交点插入红黑树，并且将小数插入S1和S2
*      如果点是线段右端点
*          如果线段前后两个点组成的线段的第一个标签和线段不一致
*              如果它们存在交点，且交点不属于队列Q
*                  将点存入Q，将线段从红黑树删除，将小数插入S1和S2
*      否则
*          点就是两个线段的交点
*          交换红黑树中，两个线段的位置
*          如果两个线段之一的第一个标签和前或后的任意一条线段的第一个标签不一致
*              如果这两个线段相交
*                  将交点插入队列Q，并且将小数插入S1和S2
*  S1、S2、R1、R2就处理好了
*/
int arcPolyPretreatment(ArcPolygon* aArcPoly1, ArcPolygon* aArcPoly2,
                        std::vector<EdgeNode>& aSequencedEdge1,
                        std::vector<EdgeNode>& aSequencedEdge2,
                        std::vector<Edge>& aRelatedEdge1,
                        std::vector<Edge>& aRelatedEdge2) {
    edagl::Timer t("arc poly pretreatment", true);
    // 获取包围盒
    auto* bBox1 = aArcPoly1->getBBox();
    auto* bBox2 = aArcPoly2->getBBox();
#ifdef LOG_
    std::cout << "******** pre treatment ********" << std::endl;
    std::cout << "******** bbox1 ********" << std::endl;
    std::cout << *bBox1 << std::endl;
    std::cout << "******** bbox2 ********" << std::endl;
    std::cout << *bBox2 << std::endl;
#endif
    // 获取相交包围盒
    BBox newBBox;
    intersectsBBoxes(*bBox1, *bBox2, newBBox);

    // 获取有效轴，true为X，false为Y
    bool effectiveX = (newBBox.getMaxX() - newBBox.getMinX()) <=
                      (newBBox.getMaxY() - newBBox.getMinY());

    // 根据有效轴获取投影数值
    double axisSmall{}, axisBig{};
    if (effectiveX) {
        axisSmall = newBBox.getMinX();
        axisBig = newBBox.getMaxX();
    } else {
        axisSmall = newBBox.getMinY();
        axisBig = newBBox.getMaxY();
    }

    // 获取两个圆弧多边形的相关边
    relatedEdgesBetweenAxis(aArcPoly1, axisSmall, axisBig, effectiveX,
                            aRelatedEdge1);
    relatedEdgesBetweenAxis(aArcPoly2, axisSmall, axisBig, effectiveX,
                            aRelatedEdge2);
    // 根据相关边初始化序列边，插入额外信息
    initSequencedEdge(aSequencedEdge1, aRelatedEdge1);
    initSequencedEdge(aSequencedEdge2, aRelatedEdge2);
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
    /**
     * 逻辑:
     * 遍历相关边
     * 如果是非x单调圆弧
     *     将其分解为x单调圆弧，并放到边域中
     *     如果三值开关是1，就赋2
     *     如果三值开关是2，就赋1
     * 如果不是非x单调圆弧
     *     将其放入边域中，且三值开关设为0
     */
    short int mark = 1;
    for (const auto& rEdge : aRelatedEdge) {
        if (!rEdge.isXMonotone()) {
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
    for (auto& en : aSequencedEdge) {
        // 设置标记，辨别属于那个多边形
        en.setIsFromFirst(aFirst);
        // 初始化事件
        EventNode leftEvent{}, rightEvent{};
        // 初始化左端点事件
        leftEvent.mPoint = en.getRelatedEdge().getStart();
        leftEvent.mPosition = NodePosition::LEFT;
        leftEvent.mEdgeNode = &en;
        aPq.push(leftEvent);
        // 初始化右端点事件
        rightEvent.mPoint = en.getRelatedEdge().getEnd();
        rightEvent.mPosition = NodePosition::RIGHT;
        rightEvent.mEdgeNode = &en;
        aPq.push(rightEvent);
    }
}

void rebuildSequencedEdge(std::vector<EdgeNode>& aSequencedEdge1,
                          std::vector<EdgeNode>& aSequencedEdge2) {
    edagl::Timer t("rebuild sequenced edge", true);
    // 声明存储事件节点的优先队列，规则为最小堆
    std::priority_queue<EventNode> pq;
    // 初始化事件，并写入优先队列
    appendEventNode(pq, aSequencedEdge1, true);
    appendEventNode(pq, aSequencedEdge2, false);
    // 优化过的宾利-奥特曼算法
    // 初始化红黑树
    std::set<EdgeNode*> rbTree{};

    while (!pq.empty()) {
        auto event = pq.top();
        pq.pop();
        switch (event.mPosition) {
            case NodePosition::LEFT: {
                // 左节点
                handleLeftNode(rbTree, pq, event);
                break;
            }
            case NodePosition::RIGHT: {
                // 右节点
                handleRightNode(rbTree, pq, event);
                break;
            }
            case NodePosition::INTERSECT: {
                // 相交节点
                handleIntersectNode(rbTree, pq, event);
                break;
            }
            default:
                break;
        }
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
    bool westIn = isPointInArcRangeExceptEdge(
        edgeCenter, aEdge.getStartAngle(), aEdge.getSweepAngle(), isCW, west);
    bool eastIn = isPointInArcRangeExceptEdge(
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

void handleLeftNode(std::set<EdgeNode*>& aRbTree,
                    std::priority_queue<EventNode>& aPQueue,
                    EventNode& aEventNode) {
    std::cout << "********************* handleLeftNode *********************"
              << std::endl;
    aRbTree.insert(aEventNode.mEdgeNode);
    // 查找相邻节点
    EdgeNode *prev = nullptr, *next = nullptr;
    auto it = aRbTree.find(aEventNode.mEdgeNode);
    // 拿到前驱后继元素
    if (it != aRbTree.end()) {
        prev = *std::prev(it);
        next = *std::next(it);
    }
    // 前节点和当前节点是否在同一个多边形上
    if (prev && (prev->isFromFirst() == aEventNode.mEdgeNode->isFromFirst())) {
        // TODO: 计算交点，将交点插入队列中，并且两个线段插入小数
        // TODO: 增加Edge求交点接口
    }
    if (next && (next->isFromFirst() == aEventNode.mEdgeNode->isFromFirst())) {
        // TODO: 计算交点，将交点插入队列中，并且两个线段插入小数
    }
    std::cout << "**********************************************************"
              << std::endl;
}

void handleRightNode(std::set<EdgeNode*>& aRbTree,
                     std::priority_queue<EventNode>& aPQueue,
                     EventNode& aEventNode) {
    // 查找相邻节点
    auto lowIt = aRbTree.lower_bound(aEventNode.mEdgeNode);
    auto upIt = aRbTree.upper_bound(aEventNode.mEdgeNode);
    EdgeNode *prev = nullptr, *next = nullptr;
    if (lowIt != aRbTree.begin()) {
        prev = *(--lowIt);
    }
    if (upIt != aRbTree.end()) {
        next = *upIt;
    }
    if (prev && next && (prev->isFromFirst() == next->isFromFirst())) {
        // TODO: 检查是否有交点
        // TODO: 检查交点是否在队列里
    }
}

void handleIntersectNode(std::set<EdgeNode*>& aRbTree,
                         std::priority_queue<EventNode>& aPQueue,
                         EventNode& aEventNode) {
    // 查找相邻节点
    auto lowIt = aRbTree.lower_bound(aEventNode.mEdgeNode);
    auto upIt = aRbTree.upper_bound(aEventNode.mEdgeNode);
    EdgeNode *prev = nullptr, *next = nullptr;
    if (lowIt != aRbTree.begin()) {
        prev = *(--lowIt);
    }
    if (upIt != aRbTree.end()) {
        next = *upIt;
    }
    // TODO: 需要知道 aEventNode 是哪两个线段的交点
    // TODO: 红黑树交换两个元素
}

int constructProcessedArcPolygon() {
    /**
     * 逻辑:
     * 初始化两个空ArcPolygon
     * 遍历原始多边形的边
     *     如果边不属于相关边
     *         将边放入结果多边形，循环计数+1
     *     否则是相关边
     *         如果此边不是分解弧
     *             如果此边和其他没有交点
     *                 将此边放入结果多边形，循环计数+1
     *             否则有交点
     *                 如果此边是圆弧
     *                     插入附加点
     *                 将边放入结果多边形，循环计数+1
     *         如果是分解弧
     *             合并分解弧
     *             将处理后的边放入结果多边形
     */

    return 0;
}
}  // namespace algorithm
