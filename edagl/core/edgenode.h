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
    EdgeNode(const Edge& aEdge, const std::pair<double, double>& aLocation,
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
     * @brief Get the Location object
     * 
     * @return std::pair<double, double>& 
     */
    std::pair<double, double>& getLocation();

    /**
     * @brief Get the Arc Mark object
     * 
     * @return short int 
     */
    short int getArcMark() const;

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool isFromFirst() const;

    /**
     * @brief Get the Id object
     * 
     * @return int 
     */
    int getId() const;

    /* endregion */

    /* region Setters */

    /**
     * @brief Set the Is From First object
     * 
     * @param aFirst 
     */
    void setIsFromFirst(bool aFirst);

    /**
     * @brief Set the Id object
     * 
     * @param aId 
     */
    void setId(int aId);

    /* endregion */

   private:
    Edge mRelatedEdge;                    ///< 相关边
    std::pair<double, double> mLocation;  ///< 交点位置信息
    short int mArcMark;                   ///< 三值开关
    bool mIsFromFirst;                    ///< 是否第一个多边形
    int mId;                              ///< 序号
};

}  // namespace core
}  // namespace edagl

#endif  //EDA_GL_EDGENODE_H
