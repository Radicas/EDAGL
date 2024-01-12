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

namespace core
{
    class LinkedNode;

    class BBox;

    class ArcPolygon
    {
    public:
        /* region Constructors / Destructor */

        explicit ArcPolygon(LinkedNode* aHeadNode);

        ~ArcPolygon();

        /* endregion */

        /* region Getters */

        BBox* getBBox() const;

        LinkedNode* getHeadNode() const;

        /* endregion */

    private:
        /* region Private Methods */

        /**
         * @brief 生成包围盒
         */
        void generateBBox() const;

        /* endregion */

        LinkedNode* mHeadNode; ///< 头节点
        BBox* mBBox;           ///< 包围盒
    };

} // namespace core

#endif // EDA_GL_ARCPOLYGON_H
