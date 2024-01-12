#include "linkednode.h"

namespace core {

    LinkedNode::LinkedNode() : data(0.0, 0.0), tag(false), crossing(false), ee{false}, pp(nullptr), np(nullptr) {

    }


    LinkedNode::LinkedNode(const Point &data, bool tag, bool crossing, bool ee, LinkedNode *pp, LinkedNode *np)
            : data(data),
              tag(tag),
              crossing(crossing),
              ee(ee),
              pp(pp),
              np(np) {
    }

    LinkedNode::LinkedNode(const LinkedNode &rhs) {
        data = rhs.data;
        tag = rhs.tag;
        crossing = rhs.crossing;
        ee = rhs.ee;
        pp = rhs.pp;
        np = rhs.np;
    }

    LinkedNode::LinkedNode(LinkedNode &&rhs) noexcept
            : data(rhs.data),
              tag(rhs.tag),
              crossing(rhs.crossing),
              ee(rhs.ee),
              pp(rhs.pp),
              np(rhs.np) {

        rhs.pp = nullptr;
        rhs.np = nullptr;
    }

    LinkedNode &LinkedNode::operator=(LinkedNode &&rhs) noexcept {
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

    bool LinkedNode::operator==(const LinkedNode &rhs) const {
        return data == rhs.data &&
               tag == rhs.tag &&
               crossing == rhs.crossing &&
               ee == rhs.ee &&
               pp == rhs.pp &&
               np == rhs.np;
    }
}
