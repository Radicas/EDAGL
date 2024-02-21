#include "bbox.h"
#include <algorithm>

namespace edagl {
namespace core {
/* region Constructors / Destructor */
BBox::BBox() : mMinX(0.0), mMaxX(0.0), mMinY(0.0), mMaxY(0.0) {}

BBox::BBox(double aMinX, double aMaxX, double aMinY, double aMaxY)
    : mMinX(aMinX), mMaxX(aMaxX), mMinY(aMinY), mMaxY(aMaxY) {}

BBox::~BBox() = default;
/* endregion */

/* region General Methods */

void BBox::reShape(double aMinX, double aMaxX, double aMinY, double aMaxY) {
    mMinX = aMinX;
    mMaxX = aMaxX;
    mMinY = aMinY;
    mMaxY = aMaxY;
}

void BBox::merge(const std::vector<BBox>& aBoxes) {
    for (const auto& box : aBoxes) {
        mMinX = std::min(mMinX, box.mMinX);
        mMaxX = std::max(mMaxX, box.mMaxX);
        mMinY = std::min(mMinY, box.mMinY);
        mMaxY = std::max(mMaxY, box.mMaxY);
    }
}

/* endregion */

/* region Getters */
double BBox::getMinX() const {
    return mMinX;
}

double BBox::getMinY() const {
    return mMinY;
}

double BBox::getMaxX() const {
    return mMaxX;
}

double BBox::getMaxY() const {
    return mMaxY;
}

/* endregion */

/* region Setters */
void BBox::setMinX(double v) {
    mMinX = v;
}

void BBox::setMinY(double v) {
    mMinY = v;
}

void BBox::setMaxX(double v) {
    mMaxX = v;
}

void BBox::setMaxY(double v) {
    mMaxY = v;
}
/* endregion */

}  // namespace core
}  // namespace edagl
