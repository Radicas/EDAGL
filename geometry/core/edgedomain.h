#ifndef EDA_GL_EDGEDOMAIN_H
#define EDA_GL_EDGEDOMAIN_H

#include "core/edge.h"

namespace core {
class EdgeDomain {
   public:
    /* region Constructors / Destructor */
    EdgeDomain();

    EdgeDomain(const Edge& aEdge, const std::pair<double, double>& aLocation,
               short int aArcMark);

    EdgeDomain(const EdgeDomain& aRhs);

    EdgeDomain& operator=(const EdgeDomain& aRhs);

    ~EdgeDomain();

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

#endif  //EDA_GL_EDGEDOMAIN_H
