#include "edgeNode.h"
namespace core {
/* region Constructors / Destructor */
EdgeNode::EdgeNode() : mRelatedEdge(), mLocation(), mArcMark(0) {}

EdgeNode::EdgeNode(const Edge& aEdge,
                   const std::pair<double, double>& aLocation,
                   short int aArcMark)
    : mRelatedEdge(aEdge), mLocation(aLocation), mArcMark(aArcMark) {}

EdgeNode::EdgeNode(const EdgeNode& aRhs) = default;

EdgeNode& EdgeNode::operator=(const EdgeNode& aRhs) = default;

EdgeNode::~EdgeNode() = default;
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
/* endregion */

/* region General Methods */

/* endregion */

}  // namespace core
