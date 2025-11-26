#pragma once

#include <vector>

#include "common/bits.hpp"
#include "grids/common/memory_wrapper.hpp"
#include "grids/common/types.hpp"

namespace gol::grids::bit_packed {

using namespace gol::common;
using index_t = gol::grids::common::index_t;
using device = gol::common::device;
using grid_size = gol::grids::common::grid_size;

template <typename item_t, device device_type>
using memory_wrapper = gol::grids::common::memory_wrapper<item_t, device_type>;

template <device device_type, typename border_policy, typename store_int_t,
          int tile_x_size = bits<store_int_t>(),
          int tile_y_size = bits<store_int_t>() / tile_x_size>
class grid {
   public:
    using cell_t = gol::grids::common::basic_cell_t;

    grid(index_t x_size_logical, index_t y_size_logical)
        : indexer_(x_size_logical / tile_x_size, y_size_logical / tile_y_size),
          tiles_of_cells_(
              indexer_.memory_size(x_size_logical / tile_x_size, y_size_logical / tile_y_size), 0) {
    }

    grid_size logical() const {
        auto [x_size_physical, y_size_physical] = indexer_.physical();
        return {x_size_physical * tile_x_size, y_size_physical * tile_y_size};
    }

    grid_size physical() const {
        return indexer_.physical();
    }

    cell_t get(index_t x, index_t y) {
        const index_t within_tile_x = x % tile_x_size;
        const index_t within_tile_y = y % tile_y_size;

        const index_t bit_index = within_tile_y * tile_x_size + within_tile_x;

        const store_int_t tile = physical_at__from_logical_coords(x, y);

        return (tile >> bit_index) & 1;
    }

    void set(index_t x, index_t y, cell_t value) {
        const index_t within_tile_x = x % tile_x_size;
        const index_t within_tile_y = y % tile_y_size;

        const index_t bit_index = within_tile_y * tile_x_size + within_tile_x;

        store_int_t& tile = physical_at__from_logical_coords(x, y);

        if (value) {
            tile |= (store_int_t(1) << bit_index);
        } else {
            tile &= ~(store_int_t(1) << bit_index);
        }
    }

    store_int_t get_physical(index_t tile_x, index_t tile_y) const {
        const index_t tile_index = indexer_.idx(tile_x, tile_y);
        return tiles_of_cells_.at(tile_index);
    }

    store_int_t& physical_at(index_t tile_x, index_t tile_y) {
        const index_t tile_index = indexer_.idx(tile_x, tile_y);
        return tiles_of_cells_.at(tile_index);
    }

    void set_physical(index_t tile_x, index_t tile_y, store_int_t value) {
        const index_t tile_index = indexer_.idx(tile_x, tile_y);
        tiles_of_cells_.at(tile_index) = value;
    }

   private:
    store_int_t& physical_at__from_logical_coords(index_t x, index_t y) {
        const index_t tile_x = x / tile_x_size;
        const index_t tile_y = y / tile_y_size;
        return physical_at(tile_x, tile_y);
    }

    border_policy indexer_;
    memory_wrapper<store_int_t, device_type> tiles_of_cells_;
};

}  // namespace gol::grids::bit_packed