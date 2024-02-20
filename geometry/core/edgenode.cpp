#include "edgenode.h"
#include "edge.h"

namespace edagl {
namespace core {
/* region Constructors / Destructor */
EdgeNode::EdgeNode()
    : mRelatedEdge(), mLocation(), mArcMark(0), mIsFromFirst(true), mId(-1) {}

EdgeNode::EdgeNode(const Edge& aEdge,
                   const std::pair<double, double>& aLocation,
                   short int aArcMark)
    : mRelatedEdge(aEdge),
      mLocation(aLocation),
      mArcMark(aArcMark),
      mIsFromFirst(true),
      mId(-1) {}

EdgeNode::EdgeNode(const EdgeNode& aRhs) = default;

EdgeNode& EdgeNode::operator=(const EdgeNode& aRhs) = default;

EdgeNode::~EdgeNode() = default;

bool EdgeNode::operator<(const EdgeNode& aRhs) const {
    return mRelatedEdge < aRhs.mRelatedEdge;
}
/* endregion */

/* region Getters */
Edge& EdgeNode::getRelatedEdge() {
    return mRelatedEdge;
}

std::pair<double, double>& EdgeNode::getLocation() {
    return mLocation;
}

short int EdgeNode::getArcMark() const {
    return mArcMark;
}

bool EdgeNode::isFromFirst() const {
    return mIsFromFirst;
}

int EdgeNode::getId() const {
    return mId;
}
/* endregion */

/* region Setters */
void EdgeNode::setIsFromFirst(bool aFirst) {
    mIsFromFirst = aFirst;
}

void EdgeNode::setId(int aId) {
    mId = aId;
}
/* endregion */

/* region General Methods */

/* endregion */

}  // namespace core
}  // namespace edagl
