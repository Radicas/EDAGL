#include "bbox.h"
#include <algorithm>

namespace core
{
    /* region Constructors / Destructor */
    BBox::BBox() : mMinX(0.0), mMaxX(0.0), mMinY(0.0), mMaxY(0.0)
    {
    }

    BBox::BBox(double aMinX, double aMaxX, double aMinY, double aMaxY)
        : mMinX(aMinX), mMaxX(aMaxX), mMinY(aMinY), mMaxY(aMaxY)
    {
    }

    BBox::~BBox() = default;
    /* endregion */

    /* region General Methods */

    void BBox::reShape(double aMinX, double aMaxX, double aMinY, double aMaxY)
    {
        mMinX = aMinX;
        mMaxX = aMaxX;
        mMinY = aMinY;
        mMaxY = aMaxY;
    }

    int BBox::intersectionBBox(const BBox& aBBox1, const BBox& aBBox2,
                               BBox& aResult)
    {
        // 检查两个BBox是否相离或包含
        if (detached(aBBox1, aBBox2) || contains(aBBox1, aBBox2))
        {
            return 1; // 返回状态1
        }

        // 得到新的相交的BBox
        aResult.mMinX = std::max(aBBox1.mMinX, aBBox2.mMinX);
        aResult.mMinY = std::max(aBBox1.mMinY, aBBox2.mMinY);
        aResult.mMaxX = std::min(aBBox1.mMaxX, aBBox2.mMaxX);
        aResult.mMaxY = std::min(aBBox1.mMaxY, aBBox2.mMaxY);

        return 0; // 返回状态0
    }

    bool BBox::detached(const BBox& aBBox1, const BBox& aBBox2)
    {
        // 排斥实验，检查两者是否相离
        return (aBBox1.mMaxX < aBBox2.mMinX || aBBox1.mMaxY < aBBox2.mMinY ||
                aBBox2.mMaxX < aBBox1.mMinX || aBBox2.mMaxY < aBBox1.mMinY);
    }

    bool BBox::contains(const BBox& aBBox1, const BBox& aBBox2)
    {
        // 检查两者是否包含关系
        return ((aBBox1.mMinX < aBBox2.mMinX && aBBox2.mMaxX < aBBox1.mMaxX &&
                 aBBox1.mMinY < aBBox2.mMinY && aBBox2.mMaxY < aBBox1.mMaxY) ||
                (aBBox2.mMinX < aBBox1.mMinX && aBBox1.mMaxX < aBBox2.mMaxX &&
                 aBBox2.mMinY < aBBox1.mMinY && aBBox1.mMaxY < aBBox2.mMaxY));
    }

    void BBox::merge(const std::vector<BBox>& aBoxes)
    {
        for (const auto box : aBoxes)
        {
            mMinX = std::min(mMinX, box.mMinX);
            mMaxX = std::max(mMaxX, box.mMaxX);
            mMinY = std::min(mMinY, box.mMinY);
            mMaxY = std::max(mMaxY, box.mMaxY);
        }
    }

    /* endregion */

    /* region Getters */
    double BBox::getMinX() const
    {
        return mMinX;
    }

    double BBox::getMinY() const
    {
        return mMinY;
    }

    double BBox::getMaxX() const
    {
        return mMaxX;
    }

    double BBox::getMaxY() const
    {
        return mMaxY;
    }

    /* endregion */

    /* region Setters */
    void BBox::setMinX(double v)
    {
        mMinX = v;
    }

    void BBox::setMinY(double v)
    {
        mMinY = v;
    }

    void BBox::setMaxX(double v)
    {
        mMaxX = v;
    }

    void BBox::setMaxY(double v)
    {
        mMaxY = v;
    }
    /* endregion */

} // namespace core
