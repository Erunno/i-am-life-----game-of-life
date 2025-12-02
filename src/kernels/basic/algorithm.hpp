#pragma once

#include "common/device.hpp"
#include "grids/basic/grid.hpp"
#include "grids/common/types.hpp"

namespace gol::kernels::cpu::basic {

template <typename grid_t>
class algorithm {
    using basic_cell_t = gol::grids::common::basic_cell_t;
    using index_t = gol::grids::common::index_t;

   public:
    static basic_cell_t process_cell(const grid_t& grid, index_t x, index_t y) {
        const basic_cell_t current_value = grid.get(x, y);
        index_t live_neighbors = 0;

        for (index_t offset_y = -1; offset_y <= 1; ++offset_y) {
            for (index_t offset_x = -1; offset_x <= 1; ++offset_x) {
                if (offset_x == 0 && offset_y == 0) {
                    continue;
                }

                const basic_cell_t neighbor_value = grid.get(x + offset_x, y + offset_y);
                live_neighbors += neighbor_value;
            }
        }

        if (current_value == 1) {
            if (live_neighbors < 2 || live_neighbors > 3) {
                return basic_cell_t(0);  // Cell dies
            } else {
                return basic_cell_t(1);  // Cell lives
            }
        } else {
            if (live_neighbors == 3) {
                return basic_cell_t(1);  // Cell becomes alive
            } else {
                return basic_cell_t(0);  // Cell remains dead
            }
        }
    }
};

};  // namespace gol::kernels::cpu::basic
