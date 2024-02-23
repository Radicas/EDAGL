#include "difference.h"

#include "boolean_kernel.h"
#include "core/polygon_with_holes.h"

namespace edagl {
namespace algorithm {

PolygonsWithHoles difference(const ArcPolygon& polygon1,
                             const ArcPolygon& polygon2) {
    return booleanOperation(polygon1, polygon2, Traits::DIFFERENCE);
}

}  // namespace algorithm
}  // namespace edagl