#include "cgal_boolean_op.h"

namespace cgal {

std::vector<Polygon_with_holes_2> computeIntersection(
    const Polygon_2& polygon1, const Polygon_2& polygon2) {
    General_polygon_set_2 gps;
    gps.insert(polygon1);
    gps.intersection(polygon2);
    std::vector<Polygon_with_holes_2> result;
    gps.polygons_with_holes(std::back_inserter(result));
    return result;
}

std::vector<Polygon_with_holes_2> computeUnion(const Polygon_2& polygon1,
                                               const Polygon_2& polygon2) {
    General_polygon_set_2 gps;
    gps.join(polygon1);
    gps.join(polygon2);
    std::vector<Polygon_with_holes_2> result;
    gps.polygons_with_holes(std::back_inserter(result));
    return result;
}

std::vector<Polygon_with_holes_2> computeDifference(const Polygon_2& polygon1,
                                                    const Polygon_2& polygon2) {
    General_polygon_set_2 gps;
    gps.insert(polygon1);
    gps.difference(polygon2);
    std::vector<Polygon_with_holes_2> result;
    gps.polygons_with_holes(std::back_inserter(result));
    return result;
}

}  // namespace cgal
