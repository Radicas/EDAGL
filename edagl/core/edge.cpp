#include "edge.h"
#include "geometry/geometry.h"
#include "geometry/intersection.h"
#include "global.h"

namespace edagl {

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
      mIsCW(false),
      mIsFirst(false),
      mLocation(-1),
      mSlopIntercept(std::make_pair(0.0, 0.0)),
      mYCoord(EPSILON) {
    initSegAttributes();  // 初始化线段属性
    initArcAttributes();  // 初始化圆弧属性
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
      mIsCW(aIsCW),
      mIsFirst(false),
      mLocation(-1),
      mSlopIntercept(std::make_pair(EPSILON,
                                    EPSILON)),
      mYCoord(EPSILON) {
    initSegAttributes();  // 初始化线段属性
    initArcAttributes();  // 初始化圆弧属性
}

Edge::Edge(const Edge& aRhs) = default;

Edge& Edge::operator=(const Edge& aRhs) = default;

Edge::~Edge() = default;

/* endregion */

/* region General Methods */
std::ostream& operator<<(std::ostream& os, const Edge& edge) {
    os << "********** edge info **********\n"
       << "is Arc: " << edge.isArc() << "\n"
       << "is X Monotone: " << edge.isXMonotone() << "\n"
       << "is CW: " << edge.isCW() << "\n"
       << "start: " << edge.getStart() << "\n"
       << "end: " << edge.getEnd() << "\n"
       << "center: " << edge.getCenter() << "\n"
       << "radius: " << edge.getRadius() << "\n"
       << "startAngle: " << edge.getStartAngle() << "\n"
       << "endAngle: " << edge.getEndAngle() << "\n"
       << "sweepAngle: " << edge.getSweepAngle() << "\n";
    return os;
}

void Edge::calcYCoord(double xCoord) {
    if (mIsArc)
        calcArcYCoord(xCoord);
    calcSegYCoord(xCoord);
}

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

bool Edge::isFirst() const {
    return mIsFirst;
}

int Edge::getLocation() const {
    return mLocation;
}
/* endregion */

/* region Setters */
void Edge::setIsFirst(bool isFirst) {
    mIsFirst = isFirst;
}

void Edge::setLocation(int location) {
    mLocation = location;
}
/* endregion */

/* region Private Methods */

void Edge::initSegAttributes() {
    if (mStart.x == mEnd.x)
        return;
    mSlopIntercept.first = (mEnd.y - mStart.y) / (mEnd.x - mStart.x);
    mSlopIntercept.second = mStart.y - mSlopIntercept.first * mStart.x;
}

void Edge::initArcAttributes() {
    // 线段直接退出
    if (!mIsArc) {
        return;
    }
    mRadius = geometry::arcRadius(mStart, mCenter);
    // 计算起始角度，范围为 [0, 2π)
    mStartAngle = geometry::arcStartAngle(mStart, mCenter);
    // 计算终止角度，范围为 [0, 2π)
    mEndAngle = geometry::arcEndAngle(mEnd, mCenter);
    // 计算扫过的角度，范围为 [0, 2π)
    mSweepAngle = geometry::arcSweepAngle(mStartAngle, mEndAngle, mIsCW);
    // 计算圆弧X单调性
    mIsXMonotone = geometry::isXMonotoneArc(mStart, mEnd, mCenter, mSweepAngle);
    // 计算圆弧的附加点
    mAppendix = geometry::midPointOfArc(mStart, mEnd, mCenter, mIsCW);
}

void Edge::calcSegYCoord(double x) {
    mYCoord = mSlopIntercept.first * x + mSlopIntercept.second;
}

void Edge::calcArcYCoord(double x) {
    std::vector<Point> results;
    geometry::lineCircleIntersectPoints(1, 0, -x, getCenter(), getRadius(),
                                        results);
    for (const auto& point : results) {
        bool in = geometry::isPointInArcRange(point, getStartAngle(),
                                              getSweepAngle(), isCW(), point);
        if (in) {
            mYCoord = point.y;
            return;
        }
    }
}

/* endregion */

}  // namespace core
}  // namespace edagl
