//
// Created by Radica on 2024/1/16.
//

#ifndef EDA_GL_TIMER_H
#define EDA_GL_TIMER_H

#include <chrono>
#include <iostream>

namespace edagl {
class Timer {
   public:
    explicit Timer(const char* aEvent, bool aSwitch) {
        mStart = std::chrono::steady_clock::now();
        mEvent = aEvent;
        mSwitch = aSwitch;
    }

    ~Timer() {
        if (!mSwitch)
            return;
        mEnd = std::chrono::steady_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::nanoseconds>(mEnd - mStart)
                .count();
        std::cout << mEvent << " 耗时: " << duration << " 纳秒" << std::endl;
    }

   private:
    std::chrono::steady_clock::time_point mStart;
    std::chrono::steady_clock::time_point mEnd;
    const char* mEvent;
    bool mSwitch;
};

}  // namespace edagl

#endif  //EDA_GL_TIMER_H
