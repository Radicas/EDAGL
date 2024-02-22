/**
 * @file shaperender.h
 * @author Radica
 * @brief
 * @version 0.1
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef EDA_GL_SHAPERENDER_H
#define EDA_GL_SHAPERENDER_H

#include "core/point.h"

namespace edagl {
namespace core {
struct Rectangle;
class ArcPolygon;
class PolygonWithHoles;
}  // namespace core
}  // namespace edagl

namespace shaperender {

/**
 * @brief 
 * 
 * @param rect 
 */
void drawRectangle(const edagl::core::Rectangle& rect);

/**
 * @brief 
 * 
 * @param cx 
 * @param cy 
 * @param radius 
 * @param startAngle 
 * @param endAngle 
 * @param numSegments 
 */
void drawArc(double cx, double cy, double radius, double startAngle,
             double endAngle, int numSegments);

/**
 * @brief 
 * 
 */
void drawSimpleArcPolygon();

/**
 * @brief 
 * 
 */
void drawComplexArcPolygon();

/**
 * @brief 
 * 
 * @param polygons 
 */
void drawArcPolygons(const std::vector<edagl::core::ArcPolygon>& polygons);

/**
 * @brief 
 * 
 * @param polygonsWithHoles 
 */
void drawPolygonsWithHoles(
    const std::vector<edagl::core::PolygonWithHoles>& polygonsWithHoles);

};  // namespace shaperender

#endif  // EDA_GL_SHAPERENDER_H
