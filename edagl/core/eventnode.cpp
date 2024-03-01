#include "eventnode.h"
#include "core/edgenode.h"

namespace edagl {
namespace core {

EventNode::EventNode(Edge* edge)
    : mPosition(),
      mPoint(),
      mEdge(edge),
      mAnotherEdge(nullptr),
      mIsVertical(edge->getStart().x == edge->getEnd().x) {}

EventNode::EventNode(const EventNode& rhs) = default;

bool EventNode::operator<(const EventNode& rhs) const {
    // 先比较x坐标
    if (mPoint.x != rhs.mPoint.x) {
        // x越小，优先级越高
        return mPoint.x > rhs.mPoint.x;
    }
    // x相同，比较y坐标
    if (mPoint.y != rhs.mPoint.y) {
        // y越大，优先级越高
        return mPoint.y < rhs.mPoint.y;
    }
    // x和y都相同，比较端点类型（左端点优先）
    if (mPosition != rhs.mPosition) {
        return mPosition == EventPosition::RIGHT;
    }
    // 端点类型也相同，比较斜率的绝对值
    double slope1 = std::abs((mEdge->getEnd().y - mEdge->getStart().y) /
                             (mEdge->getEnd().x - mEdge->getStart().x));
    double slope2 = std::abs((rhs.mEdge->getEnd().y - rhs.mEdge->getStart().y) /
                             (rhs.mEdge->getEnd().x - rhs.mEdge->getStart().x));
    // 斜率绝对值大的优先级高
    return slope1 < slope2;
}

Point determineEventPoint(Edge* edge, bool isLeft) {
    const Point& start = edge->getStart();
    const Point& end = edge->getEnd();
    /**
     * 这里的比较主要用于优先队列的排序
     * x小的优先级高
     * 如果x相等，y越大优先级越高
     */
    if (start.x < end.x || (start.x == end.x && start.y > end.y)) {
        return isLeft ? start : end;
    } else {
        return isLeft ? end : start;
    }
}

EventNode EventNode::createLeft(Edge* edge) {
    EventNode leftEvent(edge);
    leftEvent.mPosition = EventPosition::LEFT;
    leftEvent.mPoint = determineEventPoint(edge, true);
    return leftEvent;
}

EventNode EventNode::createRight(Edge* edge) {
    EventNode rightEvent(edge);
    rightEvent.mPosition = EventPosition::RIGHT;
    rightEvent.mPoint = determineEventPoint(edge, false);
    return rightEvent;
}

EventNode EventNode::createIntersect(Edge* edge, Edge* another,
                                     const Point& point) {
    EventNode intersectEvent(edge);
    intersectEvent.mAnotherEdge = another;
    intersectEvent.mPosition = EventPosition::INTERSECT;
    intersectEvent.mPoint = point;
    std::cout << "!!!报告交点:" << point << "\t来自边:" << edge->getStart()
              << "," << edge->getEnd() << "\t" << another->getStart() << ","
              << another->getEnd() << "\n\n ";
    return intersectEvent;
}

}  // namespace core
}  // namespace edagl