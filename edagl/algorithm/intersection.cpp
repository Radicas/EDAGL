#include "intersection.h"
#include "boolean_kernel.h"

namespace edagl {
namespace algorithm {

std::vector<ArcPolygon> intersect(const ArcPolygon& polygon1,
                                  const ArcPolygon& polygon2) {
    return booleanOperation(polygon1, polygon2, Traits::INTERSECTION);
}
}  // namespace algorithm
}  // namespace edagl