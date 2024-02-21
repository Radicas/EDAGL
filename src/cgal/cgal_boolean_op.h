#ifndef CGAL_BOOLEAN_OP_H
#define CGAL_BOOLEAN_OP_H

#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <CGAL/Simple_cartesian.h>
#include <vector>
namespace cgal {

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef CGAL::Polygon_2<Kernel> Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel> Polygon_with_holes_2;

// 计算两个多边形的并集
std::vector<Polygon_with_holes_2> computeUnion(const Polygon_2& polygon1,
                                               const Polygon_2& polygon2);

// 计算两个多边形的交集
std::vector<Polygon_with_holes_2> computeIntersection(
    const Polygon_2& polygon1, const Polygon_2& polygon2);

// 计算两个多边形的差集（polygon1 - polygon2）
std::vector<Polygon_with_holes_2> computeDifference(const Polygon_2& polygon1,
                                                    const Polygon_2& polygon2);
}  // namespace cgal
#endif  // CGAL_BOOLEAN_OP_H
