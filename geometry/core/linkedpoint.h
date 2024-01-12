/**
 * @file linkedpoint.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef EDA_GL_LINKEDPOINT_H
#define EDA_GL_LINKEDPOINT_H

#include "point.h"

namespace geometry
{
    struct LinkedPoint
    {
        Point data;      ///< 坐标
        bool tag;        ///< 是否附加点
        bool crossing;   ///< 是否交点
        bool ee;         ///< 是否进入点
        LinkedPoint *pp; ///< 前一个点
        LinkedPoint *np; ///< 后一点

        LinkedPoint(const Point &data, bool tag, bool crossing, bool ee, LinkedPoint *pp, LinkedPoint *np) : data(data),
                                                                                                             tag(tag),
                                                                                                             crossing(
                                                                                                                 crossing),
                                                                                                             ee(ee), pp(pp),
                                                                                                             np(np)
        {
        }

        LinkedPoint(const LinkedPoint &rhs)
        {
            data = rhs.data;
            tag = rhs.tag;
            crossing = rhs.crossing;
            ee = rhs.ee;
            pp = rhs.pp;
            np = rhs.np;
        }

        LinkedPoint &operator=(const LinkedPoint &rhs) = default;

        LinkedPoint(LinkedPoint &&rhs) noexcept
            : data(rhs.data),
              tag(rhs.tag),
              crossing(rhs.crossing),
              ee(rhs.ee),
              pp(rhs.pp),
              np(rhs.np)
        {

            rhs.pp = nullptr;
            rhs.np = nullptr;
        }

        LinkedPoint &operator=(LinkedPoint &&rhs) noexcept
        {
            data = rhs.data;
            tag = rhs.tag;
            crossing = rhs.crossing;
            ee = rhs.ee;
            pp = rhs.pp;
            np = rhs.np;

            rhs.pp = nullptr;
            rhs.np = nullptr;

            return *this;
        }

        bool operator==(const LinkedPoint &rhs) const
        {
            return data == rhs.data &&
                   tag == rhs.tag &&
                   crossing == rhs.crossing &&
                   ee == rhs.ee &&
                   pp == rhs.pp &&
                   np == rhs.np;
        }
    };
} // namespace geometry

#endif // EDA_GL_LINKEDPOINT_H
