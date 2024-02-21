/**
 * @file arcpolygon.h
 * @author Radica
 * @brief
 * @version 0.1
 * @date 2024-01-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef EDA_GL_ARCPOLYGON_H
#define EDA_GL_ARCPOLYGON_H

#include <iostream>

namespace edagl {
namespace core {
class LinkedNode;
class Point;
class BBox;

class ArcPolygon {
   public:
    /* region Constructors / Destructor */

    /**
     * @brief Construct a new Arc Polygon object
     * 
     * @param aHeadNode 
     */
    explicit ArcPolygon(LinkedNode* aHeadNode);

    /**
     * @brief Construct a new Arc Polygon object
     * 
     * @param points 
     */
    explicit ArcPolygon(const std::vector<edagl::core::Point>& points);

    /**
     * @brief Construct a new Arc Polygon object
     * 
     * @param other 
     */
    ArcPolygon(const ArcPolygon& other);

    /**
     * @brief 
     * 
     * @param other 
     * @return ArcPolygon& 
     */
    ArcPolygon& operator=(const ArcPolygon& other);

    /**
     * @brief Destroy the Arc Polygon object
     * 
     */
    ~ArcPolygon();

    /* endregion */

    /* region Getters */

    /**
     * @brief 
     * 
     * @return BBox* 
     */
    BBox* getBBox() const;

    /**
     * @brief Get the Head Node object
     * 
     * @return LinkedNode* 
     */
    LinkedNode* getHeadNode() const;

    /* endregion */

    /* region General Methods */
    /**
   * @brief 生成包围盒
   */
    void generateBBox() const;

    /**
     * @brief 输出顶点信息
     *
     * @param os
     * @param ap
     * @return
     */
    friend std::ostream& operator<<(std::ostream& os, ArcPolygon& ap);
    /* endregion */

   private:
    /* region Private Methods */

    /* endregion */

    LinkedNode* mHeadNode;  ///< 头节点
    BBox* mBBox;            ///< 包围盒
};

}  // namespace core
}  // namespace edagl

#endif  // EDA_GL_ARCPOLYGON_H
