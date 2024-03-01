/**
 * @file edge.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef EDA_GL_EDGE_H
#define EDA_GL_EDGE_H

#include <vector>
#include "core/point.h"

namespace edagl {
namespace core {

class Edge {
   public:
    Point mStart;        ///< 起点
    Point mEnd;          ///< 终点
    Point mAppendix;     ///< 附加点
    bool mIsArc;         ///< 是否圆弧
    bool mIsXMonotone;   ///< 是否X单调
    Point mCenter;       ///< 圆心
    double mRadius;      ///< 半径
    double mStartAngle;  ///< 起始角度，(0, 2π]
    double mEndAngle;    ///< 终止角度，(0, 2π]
    double mSweepAngle;  ///< 扫过的角度，(0, 2π]
    bool mIsCW;          ///< true表示顺时针；false逆时针
    bool mIsFirst;       ///< 标签1，是否属于第一个多边形
    int mLocation;       ///< 标签2，序列边中的位置
    std::pair<double, double> mSlopIntercept;  ///< 线段所在直线斜截式
    double mYCoord;                            ///< 平衡树排序用的y坐标

    /* region Constructors / Destructor */
    /**
     * @brief Construct a new Edge object
     * 
     */
    Edge();

    /**
     * @brief Construct a new Edge object
     * 
     * @param aStart 
     * @param aEnd 
     * @param aCenter 
     * @param aIsArc 
     * @param aIsCW 
     */
    Edge(const Point& aStart, const Point& aEnd,
         const Point& aCenter = {0.0, 0.0}, bool aIsArc = false,
         bool aIsCW = false);

    /**
     * @brief Construct a new Edge object
     * 
     * @param aRhs 
     */
    Edge(const Edge& aRhs);

    /**
     * @brief 
     * 
     * @param aRhs 
     * @return Edge& 
     */
    Edge& operator=(const Edge& aRhs);

    /**
     * @brief Destroy the Edge object
     * 
     */
    ~Edge();

    /* endregion */

    /* region Getters */

    /**
     * @brief Get the Start object
     * 
     * @return const Point& 
     */
    const Point& getStart() const;

    /**
     * @brief Get the End object
     * 
     * @return const Point& 
     */
    const Point& getEnd() const;

    /**
     * @brief Get the Appendix object
     * 
     * @return const Point& 
     */
    const Point& getAppendix() const;

    /**
     * @brief Get the Center object
     * 
     * @return const Point& 
     */
    const Point& getCenter() const;

    /**
     * @brief Get the Radius object
     * 
     * @return double 
     */
    double getRadius() const;

    /**
     * @brief Get the Start Angle object
     * 
     * @return double 
     */
    double getStartAngle() const;

    /**
     * @brief Get the End Angle object
     * 
     * @return double 
     */
    double getEndAngle() const;

    /**
     * @brief Get the Sweep Angle object
     * 
     * @return double 
     */
    double getSweepAngle() const;

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool isArc() const;

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool isXMonotone() const;

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool isCW() const;

    /**
     *
     * @return
     */
    bool isFirst() const;

    /**
     *
     * @return
     */
    int getLocation() const;

    /* endregion */

    /* region Setters */
    /**
     *
     * @param isFirst
     */
    void setIsFirst(bool isFirst);

    /**
     *
     * @param location
     */
    void setLocation(int location);

    /* endregion */

    /* region General Methods */

    /**
     * @brief 
     * 
     * @param os 
     * @param edge 
     * @return std::ostream& 
     */
    friend std::ostream& operator<<(std::ostream& os, const Edge& edge);

    void calcYCoord(double xCoord);
    /* endregion */

   private:
    /* region Private Methods */
    /**
     * @brief
     */
    void initSegAttributes();

    /**
     * @brief 初始化圆弧属性
     */
    void initArcAttributes();

    void calcSegYCoord(double x);

    void calcArcYCoord(double x);

    /* endregion */
};

}  // namespace core
}  // namespace edagl

#endif  // EDA_GL_EDGE_H
