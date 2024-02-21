//
// Created by Radica on 2024/2/21.
//

#ifndef EDA_GL_INTERSECTION_H
#define EDA_GL_INTERSECTION_H

#include <core/arcpolygon.h>
#include <core/point.h>
#include <vector>
namespace edagl {
typedef core::Point Point;
typedef core::ArcPolygon edaglPolygon;

/**
 * @brief
 * @param polygon1
 * @param polygon2
 * @return
 */
std::vector<edaglPolygon> intersect(const edaglPolygon& polygon1,
                                    const edaglPolygon& polygon2);

}  // namespace edagl
#endif  //EDA_GL_INTERSECTION_H
