#include "boolean.h"

#include "core/arcpolygon.h"
#include "core/bbox.h"
#include "core/edge.h"
#include "core/linkednode.h"
#include "engine/geometry.h"

namespace core {
class ArcPolygen;
}
namespace algorithm {

using namespace core;

int relatedEdgesBetweenAxis(core::ArcPolygon* aArcPolygon, double aAxisSmall,
                            double aAxisBig, bool aXAxis,
                            std::vector<core::Edge>& aRelatedEdge) {
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
            // 圆弧
            auto appendixPoint = next->mData;
            auto arcEndPoint = next->mNext->mData;
            auto arcBBox =
                geometry::bBoxOfArc(currPoint, arcEndPoint, appendixPoint);
            double startValue = aXAxis ? arcBBox.getMinX() : arcBBox.getMinY();
            double endValue = aXAxis ? arcBBox.getMaxX() : arcBBox.getMaxY();
            if ((startValue >= aAxisSmall && startValue <= aAxisBig) ||
                (endValue >= aAxisSmall && endValue <= aAxisBig) ||
                (startValue <= aAxisSmall && endValue >= aAxisBig)) {
                aRelatedEdge.emplace_back(currPoint, arcEndPoint, appendixPoint,
                                          true);
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
*  根据相关边，初始化边序列，我这里称之为边域
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
                        std::vector<EdgeDomain>& aEdgeDomain1,
                        std::vector<EdgeDomain>& aEdgeDomain2,
                        std::vector<Edge>& aRelatedEdge1,
                        std::vector<Edge>& aRelatedEdge2) {
    // 获取包围盒
    auto* bBox1 = aArcPoly1->getBBox();
    auto* bBox2 = aArcPoly2->getBBox();

    // 获取相交包围盒
    BBox newBBox;
    geometry::intersectsBBoxes(*bBox1, *bBox2, newBBox);

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
    initSequencedEdge(aEdgeDomain1, aRelatedEdge1);
    initSequencedEdge(aEdgeDomain2, aRelatedEdge2);

    // TODO: 未完待续
    return 0;
}

int initSequencedEdge(std::vector<core::EdgeDomain>& aSequencedEdge,
                      const std::vector<core::Edge>& aRelatedEdge) {
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
    for (const auto& rEdge : aRelatedEdge) {
        if (!rEdge.isXMonotone()) {
            // 非X单调
            // TODO: 分解非X单调弧
        } else {
            // X单调
            // TODO: 完善Edge Domain结构
        }
    }
    return 0;
}

int constructProcessedArcPolygon() {
    return 0;
}

std::vector<core::Edge> decomposeArc(const core::Edge& aEdge) {
    /**
     * 逻辑：
     * 观察一：
     *
     */
    return {};
}

}  // namespace algorithm
