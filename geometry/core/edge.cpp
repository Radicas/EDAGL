#include "edge.h"

namespace core {

/* region Constructors / Destructor */
Edge::Edge()
    : mStart(0.0, 0.0), mEnd(0.0, 0.0), mAppendix(0.0, 0.0), mIsArc(false) {}

Edge::Edge(const Point& aStart, const Point& aEnd, const Point& aAppendix,
           bool aIsArc)
    : mStart(aStart), mEnd(aEnd), mAppendix(aAppendix), mIsArc(aIsArc) {}

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
/* endregion */

/* region Setters */

/* endregion */

/* region Private Methods */

/* endregion */

}  // namespace core
