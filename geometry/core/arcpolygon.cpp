#include "arcpolygon.h"
#include "bbox.h"
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
            LinkedNode* nextNode = currentNode->np;
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
        // TODO: 这个是普通多边形的，圆弧多边形不适用，需要修改
        LinkedNode* currentNode = mHeadNode;
        // 初始化边界
        double minX = std::numeric_limits<double>::max();
        double maxX = std::numeric_limits<double>::lowest();
        double minY = std::numeric_limits<double>::max();
        double maxY = std::numeric_limits<double>::lowest();

        while (currentNode != nullptr)
        {
            // 获取当前节点的坐标
            double x = currentNode->data.x;
            double y = currentNode->data.y;
            // 更新边界框的最小和最大坐标
            minX = std::min(minX, x);
            maxX = std::max(maxX, x);
            minY = std::min(minY, y);
            maxY = std::max(maxY, y);
            // 移动到下一个节点
            currentNode = currentNode->np;
        }
        mBBox->reShape(minX, maxX, minY, maxY);
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
