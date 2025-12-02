#pragma once

#include <vector>

#include "common/device.hpp"

namespace gol::grids::common {

using device = gol::common::device;

template <typename item_t, device device_type>
class memory_wrapper;

template <typename item_t>
class memory_wrapper<item_t, device::CPU> {
   public:
    memory_wrapper(std::size_t size, item_t initial_value) : data_(size, initial_value) {}
    ~memory_wrapper() = default;  // TODO: why explicit destructor needed?

    item_t& at(std::size_t index) {
        return data_.at(index);  // TODO: why at?
    }

    const item_t& at(std::size_t index) const {
        return data_.at(index);  // TODO: why at?
    }

   private:
    std::vector<item_t> data_;
};
}  // namespace gol::grids::common
