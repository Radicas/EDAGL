/**
 * @file cgal_edagl.h
 * @author Radica
 * @brief CGAL元素转换工具
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef EDA_GL_CGAL_EDAGL_H
#define EDA_GL_CGAL_EDAGL_H

#include "core/polygon_with_holes.h"

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/General_polygon_set_2.h>
#include <CGAL/General_polygon_with_holes_2.h>
#include <CGAL/Gps_segment_traits_2.h>
#include <CGAL/Polygon_2.h>

namespace cgal {

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point_2;
typedef CGAL::Polygon_2<Kernel> Polygon_2;
typedef CGAL::Gps_segment_traits_2<Kernel> Traits;
typedef CGAL::General_polygon_set_2<Traits> General_polygon_set_2;
typedef CGAL::General_polygon_with_holes_2<Polygon_2> Polygon_with_holes_2;

typedef edagl::core::ArcPolygon ArcPolygon;
typedef edagl::core::PolygonWithHoles PolygonWithHoles;

/**
 * @brief CGAL多边形转换成EDAGL多边形
 * 
 * @param cgalPolygon 
 * @return ArcPolygon 
 */
ArcPolygon cgalPolygon2ArcPolygon(const Polygon_2& cgalPolygon);

/**
 * @brief EDAGL多边形转换成CGAL多边形
 * 
 * @param arcPolygon 
 * @return Polygon_2 
 */
Polygon_2 arcPolygon2CgalPolygon(const ArcPolygon& arcPolygon);

/**
 * @brief CGAL带孔多边形转换成EDAGL带孔多边形
 * 
 * @param cgalPolygonWithHoles 
 * @return PolygonWithHoles 
 */
PolygonWithHoles cgalPolygonWithHoles2CustomType(
    const Polygon_with_holes_2& cgalPolygonWithHoles);

/**
 * @brief EDAGL带孔多边形转换成CGAL带孔多边形
 * 
 * @param customPolygonWithHoles 
 * @return Polygon_with_holes_2 
 */
Polygon_with_holes_2 customPolygonWithHoles2Cgal(
    const PolygonWithHoles& customPolygonWithHoles);

/**
 * @brief CGAL带孔多边形组转换成EDAGL带孔多边形组
 * 
 * @param cgalPolygonsWithHoles 
 * @return std::vector<PolygonWithHoles> 
 */
std::vector<PolygonWithHoles> cgal2EdaglPolygonWithHoles(
    const std::vector<Polygon_with_holes_2>& cgalPolygonsWithHoles);

/**
 * @brief EDAGL带孔多边形组转换成CGAL带孔多边形组
 * 
 * @param edaglPolygonWithHoles 
 * @return std::vector<Polygon_with_holes_2> 
 */
std::vector<Polygon_with_holes_2> edagl2CgalPolygonWithHoles(
    const std::vector<PolygonWithHoles>& edaglPolygonWithHoles);

}  // namespace cgal

#endif  //EDA_GL_CGAL_EDAGL_H
