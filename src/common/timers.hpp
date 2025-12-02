#pragma once

#include <chrono>
#include <functional>
#include <ratio>
#include <utility>

namespace gol::common {

class cpu_timer {
   public:
    template <typename Func>
    static double measure(Func&& func) {
        const auto start_time_ = std::chrono::high_resolution_clock::now();
        std::invoke(std::forward<Func>(func));
        const auto end_time_ = std::chrono::high_resolution_clock::now();

        const std::chrono::duration<double, std::milli> duration = end_time_ - start_time_;
        return duration.count();
    }
};

}  // namespace gol::common
