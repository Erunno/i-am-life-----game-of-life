#pragma once

#include <chrono>

namespace gol::common {

class cpu_timer {
   public:
    template <typename Func>
    static double measure(Func&& func) {
        auto start_time_ = std::chrono::high_resolution_clock::now();
        func();
        auto end_time_ = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration = end_time_ - start_time_;
        return duration.count();
    }
};

}  // namespace gol::common