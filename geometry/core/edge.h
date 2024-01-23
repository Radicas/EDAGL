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

namespace core {
class Edge {
   public:
    /* region Constructors / Destructor */
    Edge();

    Edge(const Point& aStart, const Point& aEnd,
         const Point& aCenter = {0.0, 0.0}, bool aIsArc = false,
         bool aIsCW = false);

    Edge(const Edge& aRhs);

    Edge& operator=(const Edge& aRhs);

    ~Edge();

    /* endregion */

    /* region Getters */
    const Point& getStart() const;

    const Point& getEnd() const;

    const Point& getAppendix() const;

    const Point& getCenter() const;

    double getRadius() const;

    double getStartAngle() const;

    double getEndAngle() const;

    double getSweepAngle() const;

    bool isArc() const;

    bool isXMonotone() const;

    bool isCW() const;
    /* endregion */

    /* region Setters */

    /* endregion */

    /* region General Methods */

    friend std::ostream& operator<<(std::ostream& os, const Edge& edge) {
        os << "********** edge info **********\n"
           << "is Arc: " << edge.isArc() << "\n"
           << "is X Monotone: " << edge.isXMonotone() << "\n"
           << "is CW: " << edge.isCW() << "\n"
           << "start: " << edge.getStart() << "\n"
           << "end: " << edge.getEnd() << "\n"
           << "center: " << edge.getCenter() << "\n"
           << "radius: " << edge.getRadius() << "\n"
           << "startAngle: " << edge.getStartAngle() << "\n"
           << "endAngle: " << edge.getEndAngle() << "\n"
           << "sweepAngle: " << edge.getSweepAngle() << "\n";
        return os;
    }

    /* endregion */

   private:
    /* region Private Methods */
    /**
     * @brief 初始化圆弧属性
     */
    void initArcValues();
    /* endregion */

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
};

}  // namespace core

#endif  // EDA_GL_EDGE_H
