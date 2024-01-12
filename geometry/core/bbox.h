/**
 * @file bbox.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef EDA_GL_BBOX_H
#define EDA_GL_BBOX_H

#include <vector>

namespace core
{
    class BBox
    {

    public:
        /* region Constructors / Destructor */
        BBox(/* args */);

        BBox(double aMinX, double aMaxX, double aMinY, double aMaxY);

        ~BBox();

        /* endregion */

        /* region General Methods */
        void reShape(double aMinX, double aMaxX, double aMinY, double aMaxY);

        static int intersectionBBox(const BBox& aBBox1, const BBox& aBBox2,
                                    BBox& aResult);

        static bool detached(const BBox& aBBox1, const BBox& aBBox2);

        static bool contains(const BBox& aBBox1, const BBox& aBBox2);

        void merge(const std::vector<BBox>& aBoxes);
        /* endregion */

        /* region Getters */

        double getMinX() const;

        double getMinY() const;

        double getMaxX() const;

        double getMaxY() const;
        /* endregion */

        /* region Setters */
        void setMinX(double v);

        void setMinY(double v);

        void setMaxX(double v);

        void setMaxY(double v);
        /* endregion */

    private:
        double mMinX;
        double mMaxX;
        double mMinY;
        double mMaxY;
    };
} // namespace core

#endif // EDA_GL_BBOX_H
