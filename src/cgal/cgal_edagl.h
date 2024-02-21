// 转换工具
#ifndef EDA_GL_CGAL_EDAGL_H
#define EDA_GL_CGAL_EDAGL_H

#include "core/arcpolygon.h"

#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <CGAL/Simple_cartesian.h>

namespace cgal {

using namespace edagl::core;

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 CGAL_Point;
typedef CGAL::Polygon_2<Kernel> Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel> Polygon_with_holes_2;

ArcPolygon cgalPolygon2ArcPolygon(const Polygon_2& cgalPolygon);

Polygon_2 arcPolygon2CgalPolygon(const ArcPolygon& arcPolygon);

std::vector<ArcPolygon> cgalPolygonsWithHoles2ArcPolygons(
    const std::vector<Polygon_with_holes_2>& cgalPolygonsWithHoles);

std::vector<Polygon_with_holes_2> arcPolygons2CgalPolygonsWithHoles(
    const std::vector<ArcPolygon>& arcPolygons);

}  // namespace cgal

#endif  //EDA_GL_CGAL_EDAGL_H
