#include "cgal_edagl.h"
#include "core/linkednode.h"
#include "core/point.h"
#include "core/polygon_with_holes.h"

namespace cgal {
using namespace edagl::core;

ArcPolygon cgalPolygon2ArcPolygon(const Polygon_2& cgalPolygon) {
    if (cgalPolygon.is_empty()) {
        return ArcPolygon(nullptr);
    }
    LinkedNode* head = nullptr;
    LinkedNode* tail = nullptr;
    for (auto vert = cgalPolygon.vertices_begin();
         vert != cgalPolygon.vertices_end(); ++vert) {
        Point p(CGAL::to_double(vert->x()), CGAL::to_double(vert->y()));
        auto* newNode = new LinkedNode(p);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->mNext = newNode;
            newNode->mPrev = tail;
            tail = newNode;
        }
    }
    if (head && tail && head != tail) {
        tail->mNext = head;
        head->mPrev = tail;
    }
    return ArcPolygon(head);
}

Polygon_2 arcPolygon2CgalPolygon(const ArcPolygon& arcPolygon) {
    Polygon_2 cgalPolygon;
    LinkedNode* head = arcPolygon.getHeadNode();
    if (!head) {
        return cgalPolygon;
    }
    LinkedNode* current = head;
    do {
        Point_2 cgalPoint(current->mData.x, current->mData.y);
        cgalPolygon.push_back(cgalPoint);
        current = current->mNext;
    } while (current && current != head);
    return cgalPolygon;
}

PolygonWithHoles cgalPolygonWithHoles2CustomType(
    const Polygon_with_holes_2& cgalPolygonWithHoles) {
    PolygonWithHoles customPolygonWithHoles;
    ArcPolygon outerBoundary =
        cgalPolygon2ArcPolygon(cgalPolygonWithHoles.outer_boundary());
    customPolygonWithHoles.mData.push_back(outerBoundary);
    for (auto holeIt = cgalPolygonWithHoles.holes_begin();
         holeIt != cgalPolygonWithHoles.holes_end(); ++holeIt) {
        ArcPolygon holeBoundary = cgalPolygon2ArcPolygon(*holeIt);
        customPolygonWithHoles.mData.push_back(holeBoundary);
    }

    return customPolygonWithHoles;
}

Polygon_with_holes_2 customPolygonWithHoles2Cgal(
    const PolygonWithHoles& customPolygonWithHoles) {
    if (customPolygonWithHoles.mData.empty()) {
        return {};
    }
    Polygon_2 outerBoundary =
        arcPolygon2CgalPolygon(customPolygonWithHoles.mData.front());
    std::vector<Polygon_2> holes;
    for (size_t i = 1; i < customPolygonWithHoles.mData.size(); ++i) {
        holes.push_back(
            arcPolygon2CgalPolygon(customPolygonWithHoles.mData[i]));
    }
    return {outerBoundary, holes.begin(), holes.end()};
}

std::vector<PolygonWithHoles> cgal2EdaglPolygonWithHoles(
    const std::vector<Polygon_with_holes_2>& cgalPolygonsWithHoles) {
    std::vector<PolygonWithHoles> edaglPolygonsWithHoles;
    for (const auto& cgalPolygonWithHoles : cgalPolygonsWithHoles) {
        PolygonWithHoles customPolygonWithHoles =
            cgalPolygonWithHoles2CustomType(cgalPolygonWithHoles);
        edaglPolygonsWithHoles.push_back(customPolygonWithHoles);
    }
    return edaglPolygonsWithHoles;
}

std::vector<Polygon_with_holes_2> edagl2CgalPolygonWithHoles(
    const std::vector<PolygonWithHoles>& edaglPolygonWithHoles) {
    std::vector<Polygon_with_holes_2> cgalPolygonsWithHoles;
    for (const auto& customPolygonWithHoles : edaglPolygonWithHoles) {
        Polygon_with_holes_2 cgalPolygonWithHoles =
            customPolygonWithHoles2Cgal(customPolygonWithHoles);
        cgalPolygonsWithHoles.push_back(cgalPolygonWithHoles);
    }
    return cgalPolygonsWithHoles;
}

}  // namespace cgal