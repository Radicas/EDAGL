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

Edge::Edge(const Point& aStart, const Point& aEnd, const Point& aAppendix,
           bool aIsArc, bool aIsNonXMonotone, bool aIsCW)
    : mStart(aStart),
      mEnd(aEnd),
      mAppendix(aAppendix),
      mIsArc(aIsArc),
      mIsXMonotone(aIsNonXMonotone),
      mCenter(),
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
Point Edge::getStart() {
    return mStart;
}

Point Edge::getEnd() {
    return mEnd;
}

Point Edge::getAppendix() {
    return mAppendix;
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

Point Edge::getCenter() {
    return mCenter;
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
    if (geometry::isCollinear(mStart, mEnd, mAppendix)) {
        std::cerr << "error: three points in a line -> " << __FILE_NAME__
                  << __LINE__ << std::endl;
        exit(-1);
    }
    geometry::circleFrom3Points(mStart, mEnd, mAppendix, mCenter, mRadius);
    // 计算起始角度和终止角度
    mStartAngle = std::atan2(mStart.y - mCenter.y, mStart.x - mCenter.x);
    mEndAngle = std::atan2(mEnd.y - mCenter.y, mEnd.x - mCenter.x);
    // 调整角度范围为 (0, 2π]
    if (mStartAngle <= 0) {
        mStartAngle += 2 * M_PI;
    }
    if (mEndAngle <= 0) {
        mEndAngle += 2 * M_PI;
    }

    // 计算扫过的角度
    if (mIsCW) {
        mSweepAngle = (mStartAngle < mEndAngle)
                          ? mStartAngle + 2 * M_PI - mEndAngle
                          : mStartAngle - mEndAngle;
    } else {
        mSweepAngle = (mEndAngle < mStartAngle)
                          ? mEndAngle + 2 * M_PI - mStartAngle
                          : mEndAngle - mStartAngle;
    }

    // 判断圆弧X单调性
    mIsXMonotone = geometry::isXMonotoneArc(mStart, mEnd, mCenter, mSweepAngle);
}

/* endregion */

}  // namespace core
