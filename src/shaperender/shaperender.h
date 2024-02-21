/**
 * @file shaperender.h
 * @author your name (you@domain.com)
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
}  // namespace core
}  // namespace edagl

namespace shaperender {

void drawRectangle(const edagl::core::Rectangle& rect);

void drawArc(double cx, double cy, double radius, double startAngle,
             double endAngle, int numSegments);

void drawSimpleArcPolygon();

void drawComplexArcPolygon();

void drawArcPolygons(const std::vector<edagl::core::ArcPolygon>& polygons);

};  // namespace shaperender

#endif  // EDA_GL_SHAPERENDER_H
