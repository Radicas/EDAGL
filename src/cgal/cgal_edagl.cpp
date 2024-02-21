#include "cgal_edagl.h"
#include "core/linkednode.h"
#include "core/point.h"

namespace cgal {
using namespace edagl::core;

ArcPolygon cgalPolygon2ArcPolygon(const Polygon_2& cgalPolygon) {
    // 检查多边形是否为空
    if (cgalPolygon.is_empty()) {
        return ArcPolygon(nullptr);  // 返回一个空的ArcPolygon
    }

    // 构建ArcPolygon的链表
    LinkedNode* head = nullptr;
    LinkedNode* current = nullptr;
    for (auto vert = cgalPolygon.vertices_begin();
         vert != cgalPolygon.vertices_end(); ++vert) {
        // 将CGAL的点转换为我们的Point类型
        Point p(vert->x(), vert->y());

        // 创建新的链表节点
        auto* newNode = new LinkedNode(p);

        // 设置链表的头节点
        if (!head) {
            head = newNode;
            current = newNode;
        } else {
            // 链接当前节点与新节点
            current->mNext = newNode;
            newNode->mPrev = current;
            current = newNode;
        }
    }

    // 使链表成环（如果需要）
    if (head && current && head != current) {
        current->mNext = head;
        head->mPrev = current;
    }

    // 使用链表头节点创建ArcPolygon对象
    return ArcPolygon(head);
}

Polygon_2 arcPolygon2CgalPolygon(const ArcPolygon& arcPolygon) {
    Polygon_2 cgalPolygon;

    // 获取ArcPolygon的头节点
    LinkedNode* head = arcPolygon.getHeadNode();
    if (!head) {
        return cgalPolygon;  // 如果头节点为空，返回一个空的CGAL多边形
    }

    // 遍历ArcPolygon的链表
    LinkedNode* current = head;
    do {
        // 将ArcPolygon的点转换为CGAL的点
        CGAL_Point cgalPoint(current->mData.x, current->mData.y);

        // 将点添加到CGAL多边形中
        cgalPolygon.push_back(cgalPoint);

        // 移动到下一个节点
        current = current->mNext;
    } while (current && current != head);  // 如果链表是环形的，防止无限循环

    return cgalPolygon;
}

std::vector<ArcPolygon> cgalPolygonsWithHoles2ArcPolygons(
    const std::vector<Polygon_with_holes_2>& cgalPolygonsWithHoles) {
    std::vector<ArcPolygon> arcPolygons;

    for (const auto& polygonWithHoles : cgalPolygonsWithHoles) {
        // 转换外部边界
        ArcPolygon outerBoundary =
            cgalPolygon2ArcPolygon(polygonWithHoles.outer_boundary());
        arcPolygons.push_back(outerBoundary);

        // 转换每个洞
        for (auto hole = polygonWithHoles.holes_begin();
             hole != polygonWithHoles.holes_end(); ++hole) {
            ArcPolygon holePolygon = cgalPolygon2ArcPolygon(*hole);
            arcPolygons.push_back(holePolygon);  // 或者以其他方式处理洞
        }
    }

    return arcPolygons;
}

std::vector<Polygon_with_holes_2> arcPolygons2CgalPolygonsWithHoles(
    const std::vector<ArcPolygon>& arcPolygons) {
    std::vector<CGAL::Polygon_with_holes_2<CGAL::Simple_cartesian<double>>>
        cgalPolygonsWithHoles;

    // 假设 arcPolygons 的第一个元素是外部边界，其余的是洞
    if (!arcPolygons.empty()) {
        Polygon_2 outerBoundary = arcPolygon2CgalPolygon(arcPolygons[0]);
        CGAL::Polygon_with_holes_2<CGAL::Simple_cartesian<double>>
            polygonWithHoles(outerBoundary);

        for (size_t i = 1; i < arcPolygons.size(); ++i) {
            Polygon_2 hole = arcPolygon2CgalPolygon(arcPolygons[i]);
            polygonWithHoles.add_hole(hole);
        }

        cgalPolygonsWithHoles.push_back(polygonWithHoles);
    }

    return cgalPolygonsWithHoles;
}

}  // namespace cgal