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

namespace core
{
    class Edge
    {
    public:
    };

    class EdgeDomain
    {
    public:
        Edge relatedEdge;
        std::vector<float> location;
        short int arcMark;
    };
} // namespace core

#endif // EDA_GL_EDGE_H
