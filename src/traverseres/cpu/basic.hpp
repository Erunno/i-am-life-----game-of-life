#pragma once

#include <memory>
#include <utility>

#include "common/device.hpp"
#include "common/timers.hpp"
#include "grids/common/types.hpp"

namespace gol::traverseres::cpu::basic {

template <typename grid_t, typename algorithm_t>
class traverser {
   public:
    static_assert(grid_t::device_v == gol::common::device::CPU,
                  "CPU traverser can work only with CPU grids");

    using cpu_grid_t = typename grid_t::cpu_version_t;

    using cpu_grid_ptr = std::unique_ptr<cpu_grid_t>;
    using index_t = gol::grids::common::index_t;

    void initialize(const grid_t& input_grid, index_t iterations) {
        input_grid_ = input_grid.clone_to_cpu_memory();
        intermidiate_grid_ = input_grid.clone_to_cpu_memory();
        iterations_ = iterations;
    }

    void run() {
        run_time_ms_ = timer_cpu::measure([&]() {
            const auto [width, height] = input_grid_->physical();

            auto current = input_grid_.get();
            auto next = intermidiate_grid_.get();

            for (index_t iter = 0; iter < iterations_; ++iter) {
                for (index_t y = 0; y < height; ++y) {
                    for (index_t x = 0; x < width; ++x) {
                        auto value = algorithm_t::process_cell(*current, x, y);
                        next->set_physical(x, y, value);
                    }
                }

                std::swap(current, next);
            }
        });
    }

    cpu_grid_ptr fetch_result_to_cpu() {
        if (iterations_ % 2 == 1) {
            return std::move(intermidiate_grid_);
        } else {
            return std::move(input_grid_);
        }
    }

   private:
    using timer_cpu = gol::common::cpu_timer;

    double run_time_ms_ = 0.0;
    index_t iterations_ = 0;

    cpu_grid_ptr input_grid_ = nullptr;
    cpu_grid_ptr intermidiate_grid_ = nullptr;
};

}  // namespace gol::traverseres::cpu::basic
