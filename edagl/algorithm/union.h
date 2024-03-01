/**
 * @file union.h
 * @author Radica
 * @brief 并集
 * @version 0.1
 * @date 2024-02-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef EDA_GL_UNION_H
#define EDA_GL_UNION_H

#include <core/arcpolygon.h>
#include <core/point.h>

#include <vector>

namespace edagl {
namespace core {
class ArcPolygon;
class PolygonWithHoles;
}  // namespace core
namespace algorithm {

typedef edagl::core::ArcPolygon ArcPolygon;
typedef edagl::core::PolygonWithHoles PolygonWithHoles;
typedef std::vector<PolygonWithHoles> PolygonsWithHoles;

/**
 * @brief 并集
 * @param polygon1
 * @param polygon2
 * @return
 */
PolygonsWithHoles union_(const ArcPolygon& polygon1,
                         const ArcPolygon& polygon2);

/**
 *
 * @param pwh1
 * @param pwh2
 * @return
 */
PolygonsWithHoles union_(const PolygonWithHoles& pwh1,
                         const PolygonWithHoles& pwh2);

}  // namespace algorithm
}  // namespace edagl
#endif  //EDA_GL_UNION_H