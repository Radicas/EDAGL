/**
 * @file polygon_with_holes.h
 * @author Radica
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef EDA_GL_POLYGON_WITH_HOLES_H
#define EDA_GL_POLYGON_WITH_HOLES_H

#include "core/arcpolygon.h"

namespace edagl {
namespace core {

/**
 * @brief 带孔多边形
 * 
 */
class PolygonWithHoles {
   public:
    std::vector<ArcPolygon> mData;
};

}  // namespace core
}  // namespace edagl

#endif  //EDA_GL_POLYGON_WITH_HOLES_H
