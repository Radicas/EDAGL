/**
 * @file difference.h
 * @author Radica
 * @brief 
 * @version 0.1
 * @date 2024-02-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef EDA_GL_DIFFERENCE_H
#define EDA_GL_DIFFERENCE_H

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
std::vector<edaglPolygon> difference(const edaglPolygon& polygon1,
                                     const edaglPolygon& polygon2);

}  // namespace edagl
#endif  //EDA_GL_DIFFERENCE_H
