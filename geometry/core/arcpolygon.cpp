#include "arcpolygon.h"
#include "bbox.h"
#include "engine/geometry.h"
#include "linkednode.h"

namespace core
{
    /* region Constructors / Destructor */
    ArcPolygon::ArcPolygon(LinkedNode* aHeadNode)
        : mHeadNode(aHeadNode), mBBox(new BBox())
    {
        generateBBox();
    }

    ArcPolygon::~ArcPolygon()
    {
        // 删除所有节点
        LinkedNode* currentNode = mHeadNode;
        while (currentNode != nullptr)
        {
            LinkedNode* nextNode = currentNode->mNext;
            delete currentNode;
            currentNode = nextNode;
        }
        // 删除bbox
        if (mBBox != nullptr)
        {
            delete mBBox;
        }
    }
    /* endregion */

    /* region Private Methods */
    void ArcPolygon::generateBBox() const
    {
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
        while (currentNode != nullptr)
        {
            // 找到圆弧的BBox，存起来
            if (currentNode->mIsAppendix)
            {
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
        }
        mBBox->reShape(minX, maxX, minY, maxY);
        mBBox->merge(arcBBoxes);
    }

    /* endregion */

    /* region General Methods */

    /* endregion */

    /* region Getter Methods */
    LinkedNode* ArcPolygon::getHeadNode() const
    {
        return mHeadNode;
    }

    BBox* ArcPolygon::getBBox() const
    {
        return mBBox;
    }
    /* endregion */

    /* region Setter Methods */

    /* endregion */

} // namespace core
