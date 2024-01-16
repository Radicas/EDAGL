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
         const Point& aAppendix = {0.0, 0.0}, bool aIsArc = false);

    Edge(const Edge& aRhs);

    Edge& operator=(const Edge& aRhs);

    ~Edge();

    /* endregion */

    /* region Getters */
    Point getStart();

    Point getEnd();

    Point getAppendix();

    bool isArc() const;
    /* endregion */

    /* region Setters */

    /* endregion */

    /* region General Methods */

    /* endregion */

   private:
    Point mStart;
    Point mEnd;
    Point mAppendix;
    bool mIsArc;
};

class EdgeDomain {
   public:
    Edge relatedEdge;
    std::vector<float> location;
    short int arcMark;
};
}  // namespace core

#endif  // EDA_GL_EDGE_H
