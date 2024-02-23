#include "union.h"

#include "boolean_kernel.h"
#include "core/polygon_with_holes.h"

namespace edagl {
namespace algorithm {

PolygonsWithHoles union_(const ArcPolygon& polygon1,
                         const ArcPolygon& polygon2) {
    return booleanOperation(polygon1, polygon2, Traits::UNION);
}

}  // namespace algorithm
}  // namespace edagl