#pragma once

#include <cstddef>

#include "grids/common/types.hpp"

namespace gol::grids::common {

struct padded_with_zeros_policy {
    static constexpr std::size_t memory_size(index_t x_size, index_t y_size) {
        return (x_size + 2) * (y_size + 2);
    }

    padded_with_zeros_policy(index_t x_size, index_t y_size) : x_size_(x_size), y_size_(y_size) {}

    index_t idx(index_t x, index_t y) {
        return (y + 1) * (x_size_ + 2) + (x + 1);
    }

   private:
    std::size_t x_size_;
    std::size_t y_size_;
};

struct wrapped_around_policy {
    static constexpr std::size_t memory_size(index_t x_size, index_t y_size) {
        return x_size * y_size;
    }

    wrapped_around_policy(index_t x_size, index_t y_size) : x_size_(x_size), y_size_(y_size) {}

    index_t idx(index_t x, index_t y) {
        index_t wrapped_x = (x + x_size_) % x_size_;
        index_t wrapped_y = (y + y_size_) % y_size_;
        return wrapped_y * x_size_ + wrapped_x;
    }

   private:
    std::size_t x_size_;
    std::size_t y_size_;
};

}  // namespace gol::grids::common