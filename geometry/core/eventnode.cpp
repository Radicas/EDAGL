#include "eventnode.h"

namespace edagl {
namespace core {

EventNode::EventNode()
    : mPoint(), mPosition(), mEdgeNode(nullptr), mAnotherNode(nullptr) {}

bool EventNode::operator<(const EventNode& rhs) const {
    // < 从右往左，从上往下
    // > 从左往右，从下往上
    if (mPoint.x > rhs.mPoint.x) {
        return true;
    } else if (mPoint.x == rhs.mPoint.x) {
        return mPoint.y > rhs.mPoint.y;
    }
    return false;
}

}  // namespace core
}  // namespace edagl