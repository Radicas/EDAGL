#ifndef EDA_GL_EDGENODE_H
#define EDA_GL_EDGENODE_H

#include "core/edge.h"

namespace core {
class EdgeNode {
   public:
    /* region Constructors / Destructor */
    EdgeNode();

    EdgeNode(const Edge& aEdge, const std::pair<double, double>& aLocation,
             short int aArcMark);

    EdgeNode(const EdgeNode& aRhs);

    EdgeNode& operator=(const EdgeNode& aRhs);

    ~EdgeNode();

    /* endregion */

    /* region Getters */
    Edge& getRelatedEdge();

    std::pair<double, double>& getLocation();

    short int getArcMark() const;
    /* endregion */

   private:
    Edge mRelatedEdge;                    ///< 相关边
    std::pair<double, double> mLocation;  ///< 交点位置信息
    short int mArcMark;                   ///< 三值开关
};

}  // namespace core

#endif  //EDA_GL_EDGENODE_H
