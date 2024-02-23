#include "edge.h"
#include "geometry/geometry.h"

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
      mXCoord(std::numeric_limits<double>::max()) {
    initArcValues();  // 初始化圆弧属性
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
      mXCoord(std::numeric_limits<double>::max()) {
    initArcValues();  // 初始化圆弧属性
}

Edge::Edge(const Edge& aRhs) = default;

Edge& Edge::operator=(const Edge& aRhs) = default;

Edge::~Edge() = default;

bool Edge::operator<(const Edge& aRhs) const {
    /**
     * // TODO: 性能优化点
     * 这里的比较主要用于红黑树中排序的规则
     * true：元素放在靠左的位置
     * false：元素放在靠右的位置
     * 对于线段，可以考虑缓存一个斜截式，利用插值x计算出y。但要考虑斜率不存在情况
     * 对于圆弧，稍微麻烦一点了
     */

    return false;
}

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
void Edge::initArcValues() {
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

/* endregion */

}  // namespace core
}  // namespace edagl
