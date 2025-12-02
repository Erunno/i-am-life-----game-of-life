#pragma once

#include <memory>
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
    using cpu_version_t = grid<device::CPU, border_policy>;
    using cuda_version_t = grid<device::GPU, border_policy>;

    constexpr static device device_v = device_type;

    using cell_t = gol::grids::common::basic_cell_t;

    using cpu_grid_ptr = std::unique_ptr<cpu_version_t>;
    using cuda_grid_ptr = std::unique_ptr<cuda_version_t>;

    grid(index_t width, index_t height)
        : indexer_(width, height), cells_(indexer_.memory_size(width, height), 0) {}

    cell_t& at(index_t x, index_t y) {
        auto idx = indexer_.idx(x, y);
        return cells_.at(idx);
    }

    cell_t get(index_t x, index_t y) const {
        auto idx = indexer_.idx(x, y);
        return cells_.at(idx);
    }

    void set(index_t x, index_t y, cell_t value) {
        auto idx = indexer_.idx(x, y);
        cells_.at(idx) = value;
    }

    grid_size logical() const {
        return indexer_.logical();
    }

    grid_size physical() const {
        return indexer_.physical();
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

    cpu_grid_ptr clone_to_cpu_memory() const {
        auto [x_size_, y_size_] = logical();
        auto new_grid = std::make_unique<cpu_version_t>(x_size_, y_size_);

        for (index_t y = 0; y < y_size_; ++y) {
            for (index_t x = 0; x < x_size_; ++x) {
                new_grid->set_physical(x, y, get_physical(x, y));
            }
        }

        return new_grid;
    }

   private:
    border_policy indexer_;

    memory_wrapper<cell_t, device_type> cells_;
};

}  // namespace gol::grids::basic
