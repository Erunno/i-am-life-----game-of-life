#pragma once

namespace gol::grids::common {

using index_t = int;
using basic_cell_t = int;

struct grid_size {
    index_t x_size;
    index_t y_size;
};

}  // namespace gol::grids::common