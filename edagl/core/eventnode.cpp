#include "eventnode.h"
#include "core/edgenode.h"

namespace edagl {
namespace core {

EventNode::EventNode(Edge* edge)
    : mPosition(), mPoint(nullptr), mEdge(edge), mAnotherEdge(nullptr) {}

EventNode::EventNode(const EventNode& rhs) = default;

bool EventNode::operator<(const EventNode& rhs) const {
    /**
     * 先比较x，x越小，优先级越高
     * 如果x相等，比较y，y越大，优先级越高
     * 如果y相等，比较当前点是否左端点，左端点优先级高于右端点
     * 不会出现三个纬度相等的情况
     * // TODO: 交点等退化情况还没有考虑
     */
    if (mPoint->x < rhs.mPoint->x) {
        return false;  // false 表示当前事件的优先级更高
    } else if (mPoint->x == rhs.mPoint->x) {
        if (mPoint->y > rhs.mPoint->y) {
            return false;
        } else if (mPoint->y < rhs.mPoint->y) {
            return true;
        } else {  // x，y都相等，比较端点序
            return mPosition != EventPosition::LEFT;
        }
    }
    return true;  // 如果当前点的x坐标大于另一个点的x坐标，则当前点在优先队列中的优先级更低。
}

const Point* determineEventPoint(Edge* edge, bool isLeft) {
    const Point& start = edge->getStart();
    const Point& end = edge->getEnd();
    /**
     * 这里的比较主要用于优先队列的排序
     * x小的优先级高
     * 如果x相等，y越大优先级越高
     */
    if (start.x < end.x || (start.x == end.x && start.y > end.y)) {
        return isLeft ? &start : &end;
    } else {
        return isLeft ? &end : &start;
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

}  // namespace core
}  // namespace edagl