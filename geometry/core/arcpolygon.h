/**
 * @file arcpolygon.h
 * @author your name (you@domain.com)
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

class BBox;

class ArcPolygon {
   public:
    /* region Constructors / Destructor */

    explicit ArcPolygon(LinkedNode* aHeadNode);

    ~ArcPolygon();

    /* endregion */

    /* region Getters */

    BBox* getBBox() const;

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
