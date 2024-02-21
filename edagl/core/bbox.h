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

#include <ostream>
#include <vector>

namespace edagl {
namespace core {
class BBox {

   public:
    /* region Constructors / Destructor */
    /**
     * @brief 
     * 
     */
    BBox(/* args */);

    /**
     * @brief Construct a new BBox object
     * 
     * @param aMinX 
     * @param aMaxX 
     * @param aMinY 
     * @param aMaxY 
     */
    BBox(double aMinX, double aMaxX, double aMinY, double aMaxY);

    /**
     * @brief Destroy the BBox object
     * 
     */
    ~BBox();

    /* endregion */

    /* region General Methods */

    /**
     * @brief 
     * 
     * @param aMinX 
     * @param aMaxX 
     * @param aMinY 
     * @param aMaxY 
     */
    void reShape(double aMinX, double aMaxX, double aMinY, double aMaxY);

    /**
     * @brief 
     * 
     * @param aBoxes 
     */
    void merge(const std::vector<BBox>& aBoxes);

    /* endregion */

    /* region Getters */

    /**
     * @brief Get the Min X object
     * 
     * @return double 
     */
    double getMinX() const;

    /**
     * @brief Get the Min Y object
     * 
     * @return double 
     */
    double getMinY() const;

    /**
     * @brief Get the Max X object
     * 
     * @return double 
     */
    double getMaxX() const;

    /**
     * @brief Get the Max Y object
     * 
     * @return double 
     */
    double getMaxY() const;

    /* endregion */

    /* region Setters */

    /**
     * @brief Set the Min X object
     * 
     * @param v 
     */
    void setMinX(double v);

    /**
     * @brief Set the Min Y object
     * 
     * @param v 
     */
    void setMinY(double v);

    /**
     * @brief Set the Max X object
     * 
     * @param v 
     */
    void setMaxX(double v);

    /**
     * @brief Set the Max Y object
     * 
     * @param v 
     */
    void setMaxY(double v);

    /* endregion */

    /**
     * @brief 
     * 
     * @param os 
     * @param box 
     * @return std::ostream& 
     */
    friend std::ostream& operator<<(std::ostream& os, const BBox& box) {
        os << "minX: " << box.getMinX() << "\n"
           << "maxX: " << box.getMaxX() << "\n"
           << "minY: " << box.getMinY() << "\n"
           << "maxY: " << box.getMaxY();
        return os;
    }

   private:
    double mMinX;
    double mMaxX;
    double mMinY;
    double mMaxY;
};
}  // namespace core
}  // namespace edagl

#endif  // EDA_GL_BBOX_H
