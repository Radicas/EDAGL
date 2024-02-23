#include "edgenode.h"
#include "edge.h"

namespace edagl {
namespace core {

/* region Constructors / Destructor */
EdgeNode::EdgeNode() : mRelatedEdge(), mIntersectPts(), mTriValue(0) {}

EdgeNode::EdgeNode(const Edge& aEdge, const std::vector<Point>& intersectPts,
                   short int aArcMark)
    : mRelatedEdge(aEdge), mIntersectPts(intersectPts), mTriValue(aArcMark) {}

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

std::vector<Point>& EdgeNode::getIntersectPts() {
    return mIntersectPts;
}

short int EdgeNode::getTriValue() const {
    return mTriValue;
}

/* endregion */

/* region Setters */
void EdgeNode::setTriValue(short int triValue) {
    mTriValue = triValue;
}
/* endregion */

/* region General Methods */
std::ostream& operator<<(std::ostream& os, const EdgeNode& en) {
    os << "边:" << en.mRelatedEdge << " 交点:"
       << "三值:" << en.mTriValue << std::endl;
    return os;
}
/* endregion */

}  // namespace core
}  // namespace edagl
