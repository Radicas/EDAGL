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
namespace algorithm {

typedef core::Point Point;
typedef core::ArcPolygon ArcPolygon;

/**
 * @brief 并集
 * @param polygon1
 * @param polygon2
 * @return
 */
std::vector<ArcPolygon> union_(const ArcPolygon& polygon1,
                               const ArcPolygon& polygon2);

}  // namespace algorithm
}  // namespace edagl
#endif  //EDA_GL_UNION_H
