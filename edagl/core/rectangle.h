/**
 * @file rectangle.h
 * @author Radica
 * @brief
 * @version 0.1
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef EDA_GL_RECTANGLE_H
#define EDA_GL_RECTANGLE_H

namespace edagl {
namespace core {

class Point;

/**
 * @brief 
 * 
 */
class Rectangle {
   public:
    /* region Constructors / Destructor */
    /**
     * @brief Construct a new Rectangle object
     * 
     */
    Rectangle();

    /**
     * @brief Construct a new Rectangle object
     * 
     * @param x 
     * @param y 
     * @param h 
     * @param w 
     * @param angle 
     */
    Rectangle(double x, double y, double h, double w, double angle);

    /**
     * @brief Construct a new Rectangle object
     * 
     * @param other 
     */
    Rectangle(const Rectangle& other);

    /**
     * @brief 
     * 
     * @param other 
     * @return Rectangle& 
     */
    Rectangle& operator=(const Rectangle& other);

    /**
     * @brief 
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator==(const Rectangle& other) const;
    /* endregion */

    /* region General Methods */
    /**
     * @brief 
     * 
     * @return Point 
     */
    Point topLeft() const;

    /**
     * @brief 
     * 
     * @return Point 
     */
    Point topRight() const;

    /**
     * @brief 
     * 
     * @return Point 
     */
    Point bottomLeft() const;

    /**
     * @brief 
     * 
     * @return Point 
     */
    Point bottomRight() const;
    /* endregion */

   private:
    double x;      // 左上角x
    double y;      // 左上角y
    double h;      // 高度
    double w;      // 宽度
    double angle;  // 旋转角度 [0,2PI)
};

}  // namespace core
}  // namespace edagl

#endif  // EDA_GL_RECTANGLE_H
