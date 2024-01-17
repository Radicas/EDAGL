#include "edgedomain.h"
namespace core {
/* region Constructors / Destructor */
EdgeDomain::EdgeDomain() : mRelatedEdge(), mLocation(), mArcMark(0) {}

EdgeDomain::EdgeDomain(const Edge& aEdge,
                       const std::pair<double, double>& aLocation,
                       short int aArcMark)
    : mRelatedEdge(aEdge), mLocation(aLocation), mArcMark(aArcMark) {}

EdgeDomain::EdgeDomain(const EdgeDomain& aRhs) = default;

EdgeDomain& EdgeDomain::operator=(const EdgeDomain& aRhs) = default;

EdgeDomain::~EdgeDomain() = default;
/* endregion */

/* region Getters */
Edge& EdgeDomain::getRelatedEdge() {
    return mRelatedEdge;
}

std::pair<double, double>& EdgeDomain::getLocation() {
    return mLocation;
}

short int EdgeDomain::getArcMark() const {
    return mArcMark;
}
/* endregion */

/* region General Methods */

/* endregion */

}  // namespace core
