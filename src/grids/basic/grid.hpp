#pragma once

#include <vector>

#include "common/types.hpp"

namespace gol::grids::basic {

using index_t = gol::types::index_t;

class grid {
   public:
    using cell_t = gol::types::basic_cell_t;

    grid(index_t width, index_t height)
        : x_size_(width), y_size_(height), cells_(width * height, 0) {}

    cell_t& at(index_t x, index_t y) {
        return cells_[y * x_size_ + x];
    }

    index_t x_size() const {
        return x_size_;
    }

    index_t y_size() const {
        return y_size_;
    }

   private:
    index_t x_size_;
    index_t y_size_;
    std::vector<cell_t> cells_;
};

}  // namespace gol::grids::basic