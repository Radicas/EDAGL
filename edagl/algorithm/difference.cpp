#include "difference.h"

#include "boolean_kernel.h"

namespace edagl {
namespace algorithm {

std::vector<ArcPolygon> difference(const ArcPolygon& polygon1,
                                   const ArcPolygon& polygon2) {
    return booleanOperation(polygon1, polygon2, Traits::DIFFERENCE);
}

}  // namespace algorithm
}  // namespace edagl