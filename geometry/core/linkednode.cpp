#include "linkednode.h"
#include "point.h"
namespace core
{

    LinkedNode::LinkedNode()
        : mData(0.0, 0.0), mIsAppendix(false), mIsCrossing(false), mEE{false},
          mPrev(nullptr), mNext(nullptr)
    {
    }

    LinkedNode::LinkedNode(const Point& data)
        : mData(data), mIsAppendix(false), mIsCrossing(false), mEE(false),
          mPrev(nullptr), mNext(nullptr)
    {
    }

    LinkedNode::LinkedNode(const Point& data, bool tag, bool crossing, bool ee,
                           LinkedNode* pp, LinkedNode* np)
        : mData(data), mIsAppendix(tag), mIsCrossing(crossing), mEE(ee),
          mPrev(pp), mNext(np)
    {
    }

    //    LinkedNode::LinkedNode(const std::vector<Point>& points)
    //        : data(points[0]), tag(false), crossing(false), ee(false),
    //        pp(nullptr),
    //          np(nullptr)
    //    {
    //        LinkedNode* tail = this;
    //        for (size_t i = 1; i < points.size(); ++i)
    //        {
    //            LinkedNode* newNode = new LinkedNode(points[i]);
    //            tail->np = newNode;
    //            newNode->pp = tail;
    //            tail = newNode;
    //        }
    //    }
    LinkedNode::LinkedNode(const LinkedNode& rhs)
    {
        mData = rhs.mData;
        mIsAppendix = rhs.mIsAppendix;
        mIsCrossing = rhs.mIsCrossing;
        mEE = rhs.mEE;
        mPrev = rhs.mPrev;
        mNext = rhs.mNext;
    }

    LinkedNode::LinkedNode(LinkedNode&& rhs) noexcept
        : mData(rhs.mData), mIsAppendix(rhs.mIsAppendix),
          mIsCrossing(rhs.mIsCrossing), mEE(rhs.mEE), mPrev(rhs.mPrev),
          mNext(rhs.mNext)
    {

        rhs.mPrev = nullptr;
        rhs.mNext = nullptr;
    }

    LinkedNode& LinkedNode::operator=(LinkedNode&& rhs) noexcept
    {
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

    bool LinkedNode::operator==(const LinkedNode& rhs) const
    {
        return mData == rhs.mData && mIsAppendix == rhs.mIsAppendix &&
               mIsCrossing == rhs.mIsCrossing && mEE == rhs.mEE &&
               mPrev == rhs.mPrev && mNext == rhs.mNext;
    }

    LinkedNode*
    LinkedNode::constructLinkedNodes(const std::vector<Point>& points)
    {
        if (points.empty())
        {
            return nullptr;
        }

        auto* head = new LinkedNode(points[0]);

        LinkedNode* tail = head;

        for (size_t i = 1; i < points.size(); ++i)
        {
            auto* newNode = new LinkedNode(points[i]);
            tail->mNext = newNode;
            newNode->mPrev = tail;
            tail = newNode;
        }

        return head;
    }
} // namespace core
