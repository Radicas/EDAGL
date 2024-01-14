/**
 * @file boolean.h
 * @author your name (you@domain.com)
 * @brief 多边形(带圆弧)布尔运算
 * @version 0.1
 * @date 2024-01-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef EDA_GL_BOOLEAN_H
#define EDA_GL_BOOLEAN_H

#include <vector>

namespace core {
class LinkedNode;

class Edge;

class EdgeDomain;

class ArcPolygon;
}  // namespace core
namespace algorithm {
/**
 * @brief 圆弧多边形链表前处理
 * @note 此接口只处理圆弧多边形相交的情况
 * @param AP1 圆弧多边形1
 * @param AP2 圆弧多边形2
 * @param S1 相关边域1
 * @param S2 相关边域2
 * @param R1 相关边1
 * @param R2 相关边1
 * @return 0 处理正常
 */
int arcPolyPretreatment(core::ArcPolygon* AP1, core::ArcPolygon* AP2,
                        std::vector<core::EdgeDomain>& S1,
                        std::vector<core::EdgeDomain>& S2,
                        std::vector<core::Edge>& R1,
                        std::vector<core::Edge>& R2);

int initializeSequenceList(std::vector<core::EdgeDomain>& S,
                           std::vector<core::Edge>& R);

int decomposeArc();

int constructNewLinkedLists();

}  // namespace algorithm

#endif  // EDA_GL_BOOLEAN_H
