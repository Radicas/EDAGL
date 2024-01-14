#include "boolean.h"

#include "core/arcpolygon.h"
#include "core/bbox.h"
#include "core/edge.h"
#include "core/point.h"
#include "engine/geometry.h"

namespace core {
class ArcPolygen;
}
namespace algorithm {

using namespace core;

int arcPolyPretreatment(ArcPolygon* AP1, ArcPolygon* AP2,
                        std::vector<EdgeDomain>& S1,
                        std::vector<EdgeDomain>& S2, std::vector<Edge>& R1,
                        std::vector<Edge>& R2) {
    /**
         *  逻辑：
         *  获取两个圆弧多边形的包围盒
         *  根据包围盒，计算出有效轴是x还是y
         *  根据包围盒的边界值和有效轴，找出两个圆弧多边形各自的相关边
         *  这里的相关边，可能是线段，也可能是圆弧
         *  创建两个空序列，用于存放多边形的边
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

    // 获取包围盒
    auto* bBox1 = AP1->getBBox();
    auto* bBox2 = AP2->getBBox();
    BBox newBBox;
    geometry::unionBBoxes(*bBox1, *bBox2, newBBox);

    // 有效轴，false为x，true为y
    bool effectiveAxis = (newBBox.getMaxX() - newBBox.getMinX() >=
                          newBBox.getMaxY() - newBBox.getMinY());
    // 有效轴的第一条，如果是x,则是左边；如果是y，则是下边
    double effectiveAxis1 =
        effectiveAxis ? newBBox.getMinY() : newBBox.getMinX();
    // 有效轴的第二条，如果是x,则是右边；如果是y，则是上边
    double effectiveAxis2 =
        effectiveAxis ? newBBox.getMaxY() : newBBox.getMaxX();

    std::cout << "effective axis: " << effectiveAxis << std::endl;
    // TODO: 未完待续
    /**
         * 能进入此函数，说明包围盒是相交的，不相离，不包含
         *
         */

    return 0;
}

int initializeSequenceList(std::vector<core::EdgeDomain>& S,
                           std::vector<core::Edge>& R) {
    return 0;
}

int constructNewLinkedLists() {
    return 0;
}

}  // namespace algorithm
