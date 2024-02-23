/**
 * @file edgenode.h
 * @author Radica
 * @brief 
 * @version 0.1
 * @date 2024-02-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef EDA_GL_EDGENODE_H
#define EDA_GL_EDGENODE_H

#include "core/edge.h"

namespace edagl {
namespace core {
class EdgeNode {
   public:
    /* region Constructors / Destructor */
    /**
     * @brief Construct a new Edge Node object
     * 
     */
    EdgeNode();

    /**
     * @brief Construct a new Edge Node object
     * 
     * @param aEdge 
     * @param aLocation 
     * @param aArcMark 
     */
    EdgeNode(const Edge& aEdge, const std::vector<Point>& intersectPts,
             short int aArcMark);

    /**
     * @brief Construct a new Edge Node object
     * 
     * @param aRhs 
     */
    EdgeNode(const EdgeNode& aRhs);

    /**
     * @brief 
     * 
     * @param aRhs 
     * @return EdgeNode& 
     */
    EdgeNode& operator=(const EdgeNode& aRhs);

    /**
     * @brief Destroy the Edge Node object
     * 
     */
    ~EdgeNode();

    /**
     * @brief 
     * 
     * @param aRhs 
     * @return true 
     * @return false 
     */
    bool operator<(const EdgeNode& aRhs) const;

    /* endregion */

    /* region Getters */
    /**
     * @brief Get the Related Edge object
     * 
     * @return Edge& 
     */
    Edge& getRelatedEdge();

    /**
     * @brief
     *
     * @return
     */
    std::vector<Point>& getIntersectPts();

    /**
     * @brief Get the Arc Mark object
     * 
     * @return short int 
     */
    short int getTriValue() const;

    /* endregion */

    /* region Setters */
    void setTriValue(short int triValue);
    /* endregion */

    friend std::ostream& operator<<(std::ostream& os, const EdgeNode& en);

   private:
    Edge mRelatedEdge;                 ///< 相关边
    std::vector<Point> mIntersectPts;  ///< 交点
    short int mTriValue;               ///< 三值开关
};

}  // namespace core
}  // namespace edagl

#endif  //EDA_GL_EDGENODE_H
