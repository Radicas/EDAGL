#include "geometry.h"
#include "core/point.h"
#include <math.h>
#include <algorithm>

using namespace core;
namespace geometry
{
    /********************************* Vector *********************************/

    double dotProduct(const core::Point& aS, const core::Point& aE,
                      const core::Point& aO)
    {
        return (aS.x - aO.x) * (aE.x - aO.x) + (aS.y - aO.y) * (aE.y - aO.y);
    }

    double dotProduct(const core::Vector2D& aVec1, const core::Vector2D& aVec2)
    {
        return aVec1.x * aVec2.x + aVec1.y * aVec2.y;
    }

    double crossProduct(const core::Point& aS, const core::Point& aE,
                        const core::Point& aO)
    {
        return (aS.x - aO.x) * (aE.y - aO.y) - (aE.x - aO.x) * (aS.y - aO.y);
    }

    double crossProduct(const core::Vector2D& aVec1,
                        const core::Vector2D& aVec2)
    {
        return aVec1.x * aVec2.y - aVec1.y * aVec2.x;
    }
    /********************************** Point *********************************/

    bool isCollinear(const core::Point& aP1, const core::Point& aP2,
                     const core::Point& aP3)
    {
    }

    double pointsDistance(const core::Point& aP1, const core::Point& aP2)
    {
        return std::sqrt((aP1.x - aP2.x) * (aP1.x - aP2.x) +
                    (aP1.y - aP2.y) * (aP1.y - aP2.y));
    }
    /****************************** Circle / Arc ******************************/

    void circleFrom3Points(const Point& aP1, const Point& aP2, const Point& aP3,
                           Point& aCenter, double& aRadius)
    {
        double x1 = aP1.x;
        double y1 = aP1.y;
        double x2 = aP2.x;
        double y2 = aP2.y;
        double x3 = aP3.x;
        double y3 = aP3.y;

        double A = x1 * (y2 - y3) - y1 * (x2 - x3) + x2 * y3 - x3 * y2;
        double B = (x1 * x1 + y1 * y1) * (y3 - y2) +
                   (x2 * x2 + y2 * y2) * (y1 - y3) +
                   (x3 * x3 + y3 * y3) * (y2 - y1);
        double C = (x1 * x1 + y1 * y1) * (x2 - x3) +
                   (x2 * x2 + y2 * y2) * (x3 - x1) +
                   (x3 * x3 + y3 * y3) * (x1 - x2);
        double D = (x1 * x1 + y1 * y1) * (x3 * y2 - x2 * y3) +
                   (x2 * x2 + y2 * y2) * (x1 * y3 - x3 * y1) +
                   (x3 * x3 + y3 * y3) * (x2 * y1 - x1 * y2);

        double centerX = -B / (2 * A);
        double centerY = -C / (2 * A);
        double radius = std::sqrt((B * B + C * C - 4 * A * D) / (4 * A * A));

        aCenter.x = centerX;
        aCenter.y = centerY;
        aRadius = radius;
    }

    BBox bBoxOfArc(const Point& A, const Point& B, const Point& M)
    {
        BBox result;
        // 求圆心和半径
        Point center{};
        double radius{};
        circleFrom3Points(A, B, M, center, radius);

        // 初始化圆东北西南四个点
        Point E(center.x + radius, center.y);
        Point N(center.x, center.y + radius);
        Point W(center.x - radius, center.y);
        Point S(center.x, center.y - radius);

        // 计算三角形的有向面积
        double ABM =
            (A.x * (B.y - M.y) + B.x * (M.y - A.y) + M.x * (A.y - B.y)) * 0.5;
        double ABE =
            (A.x * (B.y - E.y) + B.x * (E.y - A.y) + E.x * (A.y - B.y)) * 0.5;
        double ABN =
            (A.x * (B.y - N.y) + B.x * (N.y - A.y) + N.x * (A.y - B.y)) * 0.5;
        double ABW =
            (A.x * (B.y - W.y) + B.x * (W.y - A.y) + W.x * (A.y - B.y)) * 0.5;
        double ABS =
            (A.x * (B.y - S.y) + B.x * (S.y - A.y) + S.x * (A.y - B.y)) * 0.5;

        if (ABM * ABE > 0)
        {
            result.setMaxX(E.x);
        }
        else
        {
            result.setMaxX(std::max(A.x, B.x));
        }

        if (ABM * ABN > 0)
        {
            result.setMaxY(N.y);
        }
        else
        {
            result.setMaxY(std::max(A.y, B.y));
        }

        if (ABM * ABW > 0)
        {
            result.setMinX(W.x);
        }
        else
        {
            result.setMinX(std::min(A.x, B.x));
        }

        if (ABM * ABS > 0)
        {
            result.setMinY(S.y);
        }
        else
        {
            result.setMinY(std::min(A.y, B.y));
        }
        return result;
    }
} // namespace geometry
