/**
 * @file cgal_boolean_op.h
 * @author Radica
 * @brief CGAL布尔运算接口
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef CGAL_BOOLEAN_OP_H
#define CGAL_BOOLEAN_OP_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/General_polygon_set_2.h>
#include <CGAL/General_polygon_with_holes_2.h>
#include <CGAL/Gps_segment_traits_2.h>
#include <CGAL/Polygon_2.h>

#include <vector>

namespace cgal {

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Polygon_2<Kernel> Polygon_2;
typedef CGAL::Gps_segment_traits_2<Kernel> Traits;
typedef CGAL::General_polygon_set_2<Traits> General_polygon_set_2;
typedef CGAL::General_polygon_with_holes_2<Polygon_2> Polygon_with_holes_2;

/**
 * @brief 计算交集
 * @param polygon1
 * @param polygon2
 * @return
 */
std::vector<Polygon_with_holes_2> computeIntersection(
    const Polygon_2& polygon1, const Polygon_2& polygon2);

/**
 * @brief 计算并集
 * @param polygon1
 * @param polygon2
 * @return
 */
std::vector<Polygon_with_holes_2> computeUnion(const Polygon_2& polygon1,
                                               const Polygon_2& polygon2);

/**
 * @brief 计算差集 A - B
 * @param polygon1
 * @param polygon2
 * @return
 */
std::vector<Polygon_with_holes_2> computeDifference(const Polygon_2& polygon1,
                                                    const Polygon_2& polygon2);
}  // namespace cgal
#endif  // CGAL_BOOLEAN_OP_H
