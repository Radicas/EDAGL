#include "linkednode.h"
#include "point.h"

namespace edagl {
namespace core {

LinkedNode::LinkedNode()
    : mData(0.0, 0.0),
      mIsAppendix(false),
      mIsCrossing(false),
      mEE{false},
      mPrev(nullptr),
      mNext(nullptr) {}

LinkedNode::LinkedNode(const Point& data)
    : mData(data),
      mIsAppendix(false),
      mIsCrossing(false),
      mEE(false),
      mPrev(nullptr),
      mNext(nullptr) {}

LinkedNode::LinkedNode(const Point& data, bool tag, bool crossing, bool ee,
                       LinkedNode* pp, LinkedNode* np)
    : mData(data),
      mIsAppendix(tag),
      mIsCrossing(crossing),
      mEE(ee),
      mPrev(pp),
      mNext(np) {}
LinkedNode::LinkedNode(const LinkedNode& rhs) {
    mData = rhs.mData;
    mIsAppendix = rhs.mIsAppendix;
    mIsCrossing = rhs.mIsCrossing;
    mEE = rhs.mEE;
    mPrev = rhs.mPrev;
    mNext = rhs.mNext;
}

LinkedNode::LinkedNode(LinkedNode&& rhs) noexcept
    : mData(rhs.mData),
      mIsAppendix(rhs.mIsAppendix),
      mIsCrossing(rhs.mIsCrossing),
      mEE(rhs.mEE),
      mPrev(rhs.mPrev),
      mNext(rhs.mNext) {

    rhs.mPrev = nullptr;
    rhs.mNext = nullptr;
}

LinkedNode& LinkedNode::operator=(LinkedNode&& rhs) noexcept {
    mData = rhs.mData;
    mIsAppendix = rhs.mIsAppendix;
    mIsCrossing = rhs.mIsCrossing;
    mEE = rhs.mEE;
    mPrev = rhs.mPrev;
    mNext = rhs.mNext;

    rhs.mPrev = nullptr;
    rhs.mNext = nullptr;

    return *this;
}

bool LinkedNode::operator==(const LinkedNode& rhs) const {
    return mData == rhs.mData && mIsAppendix == rhs.mIsAppendix &&
           mIsCrossing == rhs.mIsCrossing && mEE == rhs.mEE &&
           mPrev == rhs.mPrev && mNext == rhs.mNext;
}

LinkedNode* LinkedNode::constructLinkedNodes(const std::vector<Point>& aPath) {
    // 空路径直接返回空
    if (aPath.empty()) {
        return nullptr;
    }
    // 路径大小
    size_t pathSize = aPath.size();
    // 是否环形
    bool circular = aPath[0] == aPath[aPath.size() - 1];
    // 环形的话大小减一，将最后一个节点丢弃
    if (circular) {
        --pathSize;
    }
    // 构建首尾指针
    auto* head = new LinkedNode(aPath[0]);
    LinkedNode* tail = head;

    for (size_t i = 1; i < pathSize; ++i) {
        auto* newNode = new LinkedNode(aPath[i]);
        tail->mNext = newNode;
        newNode->mPrev = tail;
        tail = newNode;
    }

    // 环形双向链
    if (circular) {
        tail->mNext = head;
        head->mPrev = tail;
    }

    return head;
}
}  // namespace core
}  // namespace edagl
