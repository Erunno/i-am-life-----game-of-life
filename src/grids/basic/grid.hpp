#pragma once

#include <vector>

#include "common/device.hpp"
#include "grids/common/memory_wrapper.hpp"
#include "grids/common/types.hpp"

namespace gol::grids::basic {

using index_t = gol::grids::common::index_t;
using grid_size = gol::grids::common::grid_size;
using device = gol::common::device;

template <typename item_t, device device_type>
using memory_wrapper = gol::grids::common::memory_wrapper<item_t, device_type>;

template <device device_type, typename border_policy>
class grid {
   public:
    using cell_t = gol::grids::common::basic_cell_t;

    grid(index_t width, index_t height)
        : x_size_(width), y_size_(height), cells_(width * height, 0) {}

    cell_t& at(index_t x, index_t y) {
        return cells_.at(y * x_size_ + x);
    }

    cell_t get(index_t x, index_t y) const {
        return cells_.at(y * x_size_ + x);
    }

    void set(index_t x, index_t y, cell_t value) {
        cells_.at(y * x_size_ + x) = value;
    }

    grid_size logical() const {
        return {x_size_, y_size_};
    }

    grid_size physical() const {
        return {x_size_, y_size_};
    }

    cell_t get_physical(index_t x, index_t y) const {
        return get(x, y);
    }

    cell_t& physical_at(index_t x, index_t y) {
        return at(x, y);
    }

    void set_physical(index_t x, index_t y, cell_t value) {
        set(x, y, value);
    }

   private:
    index_t x_size_;
    index_t y_size_;
    memory_wrapper<cell_t, device_type> cells_;
};

}  // namespace gol::grids::basic