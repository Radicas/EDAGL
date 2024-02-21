#include "arcpolygon.h"
#include "bbox.h"
#include "engine/geometry.h"
#include "linkednode.h"
#include "point.h"

#include <limits>
#include <vector>

namespace edagl {
namespace core {

/* region Constructors / Destructor */
ArcPolygon::ArcPolygon(LinkedNode* aHeadNode)
    : mHeadNode(aHeadNode), mBBox(new BBox()) {
    generateBBox();
}

ArcPolygon::ArcPolygon(const std::vector<edagl::core::Point>& points)
    : mHeadNode(LinkedNode::constructLinkedNodes(points)), mBBox(new BBox()) {
    generateBBox();
}

ArcPolygon::ArcPolygon(const ArcPolygon& other)
    : mHeadNode(nullptr), mBBox(nullptr) {
    if (other.mHeadNode) {
        // 深拷贝 LinkedNode 链表
        mHeadNode = new LinkedNode(*other.mHeadNode);
        LinkedNode* thisCurrent = mHeadNode;
        LinkedNode* otherCurrent = other.mHeadNode->mNext;
        while (otherCurrent != nullptr && otherCurrent != other.mHeadNode) {
            thisCurrent->mNext = new LinkedNode(*otherCurrent);
            thisCurrent->mNext->mPrev = thisCurrent;
            thisCurrent = thisCurrent->mNext;
            otherCurrent = otherCurrent->mNext;
        }
        // 确保链表的尾部正确连接
        thisCurrent->mNext = mHeadNode;
        mHeadNode->mPrev = thisCurrent;
    }
    if (other.mBBox) {
        // 深拷贝 BBox
        mBBox = new BBox(*other.mBBox);
    }
}

ArcPolygon& ArcPolygon::operator=(const ArcPolygon& other) {
    if (this != &other) {
        // 删除当前对象的资源
        delete mHeadNode;  // 注意：这里需要编写代码来逐个删除链表中的所有节点
        delete mBBox;

        mHeadNode = nullptr;
        mBBox = nullptr;

        // 深拷贝新对象的资源
        if (other.mHeadNode) {
            mHeadNode = new LinkedNode(*other.mHeadNode);
            // 重复上面的深拷贝链表逻辑
        }
        if (other.mBBox) {
            mBBox = new BBox(*other.mBBox);
        }
    }
    return *this;
}

ArcPolygon::~ArcPolygon() {
    if (mHeadNode) {
        LinkedNode* tail = mHeadNode->mNext;
        while (tail && tail != mHeadNode) {
            LinkedNode* next = tail->mNext;
            delete tail;
            tail = next;
        }
        delete mHeadNode;
    }
    delete mBBox;
}

/* endregion */

/* region Private Methods */

/* endregion */

/* region General Methods */
void ArcPolygon::generateBBox() const {
    /**
    * 实现基于以下观察
    * 观察一：
    *  圆弧多边形中，圆弧边要么是凸边，要么是凹边。凸边需要考虑圆弧的包围盒；凹边只需要处理顶点。
    *
    * 思考：
    * 有两个做法
    * 做法一：
    *  AABB法求出整体BBox
    *  遍历过程识别出圆弧段，将圆弧段的BBox求出放一边
    *  合并整体BBox和圆弧段BBox
    * 做法二：
    *  AABB法求出整体BBox
    *  遍历过程识别出凸圆弧段，将圆弧段的BBox求出放一边
    *  合并整体BBox和圆弧段BBox
    *
    *  做法一的好处是不需要识别凸圆弧边，但是要额外增加凹圆弧段的识别
    *  做法二的好处是过滤了凹圆弧段，但是增加了凸圆弧段的识别过程
    */

    // 头指针
    LinkedNode* currentNode = mHeadNode;
    // 初始化边界
    double minX = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();

    // 所有圆弧BBox
    std::vector<BBox> arcBBoxes{};
    while (currentNode != nullptr) {
        // 找到圆弧的BBox，存起来
        if (currentNode->mIsAppendix) {
            auto* prev = currentNode->mPrev;
            auto* next = currentNode->mNext;
            auto arcBBox = geometry::bBoxOfArc(prev->mData, next->mData,
                                               currentNode->mData);
            arcBBoxes.emplace_back(arcBBox);
        }

        // 获取当前节点的坐标
        double x = currentNode->mData.x;
        double y = currentNode->mData.y;
        // 更新边界框的最小和最大坐标
        minX = std::min(minX, x);
        maxX = std::max(maxX, x);
        minY = std::min(minY, y);
        maxY = std::max(maxY, y);
        // 移动到下一个节点
        currentNode = currentNode->mNext;
        if (currentNode == mHeadNode) {
            break;
        }
    }
    mBBox->reShape(minX, maxX, minY, maxY);
    mBBox->merge(arcBBoxes);
}

std::ostream& operator<<(std::ostream& os, ArcPolygon& ap) {
    auto* head = ap.getHeadNode();
    auto* tail = head;
    while (tail) {
        bool appendix = tail->mIsAppendix;
        os << "(" << tail->mData << ")";
        if (appendix) {
            os << "\tarc\n";
        } else {
            os << "\n";
        }
        tail = tail->mNext;
        if (tail == head)
            break;
    }
    return os;
}
/* endregion */

/* region Getter Methods */
LinkedNode* ArcPolygon::getHeadNode() const {
    return mHeadNode;
}

BBox* ArcPolygon::getBBox() const {
    return mBBox;
}

/* endregion */

/* region Setter Methods */

/* endregion */

}  // namespace core
}  // namespace edagl
