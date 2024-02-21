#include "cgal_boolean_op.h"
#include <CGAL/Boolean_set_operations_2.h>

namespace cgal {
std::vector<Polygon_with_holes_2> computeUnion(const Polygon_2& polygon1,
                                               const Polygon_2& polygon2) {
    CGAL::Polygon_set_2<Kernel> unionSet;
    unionSet.join(polygon1);  // 将第一个多边形添加到集合中
    unionSet.join(polygon2);  // 将第二个多边形与当前集合做并集操作

    std::vector<Polygon_with_holes_2> result;
    unionSet.polygons_with_holes(std::back_inserter(result));  // 获取并集结果

    return result;  // 返回并集多边形的向量
}

std::vector<Polygon_with_holes_2> computeIntersection(
    const Polygon_2& polygon1, const Polygon_2& polygon2) {
    std::vector<Polygon_with_holes_2> result;
    CGAL::intersection(polygon1, polygon2, std::back_inserter(result));
    return result;
}

std::vector<Polygon_with_holes_2> computeDifference(const Polygon_2& polygon1,
                                                    const Polygon_2& polygon2) {
    std::vector<Polygon_with_holes_2> result;
    CGAL::difference(polygon1, polygon2, std::back_inserter(result));
    return result;
}

}  // namespace cgal
