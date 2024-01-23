#include "edge.h"
#include "engine/geometry.h"

namespace core {

/* region Constructors / Destructor */
Edge::Edge()
    : mStart(0.0, 0.0),
      mEnd(0.0, 0.0),
      mAppendix(0.0, 0.0),
      mIsArc(false),
      mIsXMonotone(false),
      mCenter(0.0, 0.0),
      mRadius(0.0),
      mStartAngle(0.0),
      mEndAngle(0.0),
      mSweepAngle(0.0),
      mIsCW(false) {
    // 初始化圆弧属性
    initArcValues();
}

Edge::Edge(const Point& aStart, const Point& aEnd, const Point& aCenter,
           bool aIsArc, bool aIsCW)
    : mStart(aStart),
      mEnd(aEnd),
      mAppendix(),
      mIsArc(aIsArc),
      mIsXMonotone(),
      mCenter(aCenter),
      mRadius(),
      mStartAngle(),
      mEndAngle(),
      mSweepAngle(),
      mIsCW(aIsCW) {
    // 初始化圆弧属性
    initArcValues();
}

Edge::Edge(const Edge& aRhs) = default;

Edge& Edge::operator=(const Edge& aRhs) = default;

Edge::~Edge() = default;

/* endregion */

/* region General Methods */

/* endregion */

/* region Getters */
const Point& Edge::getStart() const {
    return mStart;
}

const Point& Edge::getEnd() const {
    return mEnd;
}

const Point& Edge::getAppendix() const {
    return mAppendix;
}

const Point& Edge::getCenter() const {
    return mCenter;
}

bool Edge::isArc() const {
    return mIsArc;
}

bool Edge::isXMonotone() const {
    return mIsXMonotone;
}

bool Edge::isCW() const {
    return mIsCW;
}

double Edge::getRadius() const {
    return mRadius;
}

double Edge::getStartAngle() const {
    return mStartAngle;
}

double Edge::getEndAngle() const {
    return mEndAngle;
}

double Edge::getSweepAngle() const {
    return mSweepAngle;
}
/* endregion */

/* region Setters */

/* endregion */

/* region Private Methods */
void Edge::initArcValues() {
    // 线段直接退出
    if (!mIsArc) {
        return;
    }
    //    if (geometry::isCollinear(mStart, mEnd, mAppendix)) {
    //        std::cerr << "error: three points in a line -> " << __FILE_NAME__
    //                  << __LINE__ << std::endl;
    //        exit(-1);
    //    }
    //    geometry::circleFrom3Points(mStart, mEnd, mAppendix, mCenter, mRadius);
    mRadius = geometry::getRadius(mStart, mCenter);
    // 计算起始角度，范围为 [0, 2π)
    mStartAngle = geometry::getStartAngle(mStart, mCenter);
    // 计算终止角度，范围为 [0, 2π)
    mEndAngle = geometry::getEndAngle(mEnd, mCenter);
    // 计算扫过的角度，范围为 [0, 2π)
    mSweepAngle = geometry::getSweepAngle(mStartAngle, mEndAngle, mIsCW);
    // 计算圆弧X单调性
    mIsXMonotone = geometry::isXMonotoneArc(mStart, mEnd, mCenter, mSweepAngle);
    // 计算圆弧的附加点
    mAppendix = geometry::getMidOfArc(mStart, mEnd, mCenter, mIsCW);
}

/* endregion */

}  // namespace core
