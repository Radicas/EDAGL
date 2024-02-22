/**
 * @file intersection.h
 * @author Radica
 * @brief 
 * @version 0.1
 * @date 2024-02-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef EDA_GL_INTERSECTION_H
#define EDA_GL_INTERSECTION_H

#include <core/arcpolygon.h>
#include <core/point.h>
#include <vector>

namespace edagl {
namespace algorithm {

typedef core::Point Point;
typedef core::ArcPolygon ArcPolygon;

/**
 * @brief 交集
 * @param polygon1
 * @param polygon2
 * @return
 */
std::vector<ArcPolygon> intersect(const ArcPolygon& polygon1,
                                  const ArcPolygon& polygon2);

}  // namespace algorithm
}  // namespace edagl
#endif  //EDA_GL_INTERSECTION_H
