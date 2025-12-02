#pragma once

namespace gol::common {

constexpr int bits_in_byte = 8;

template <typename int_t>
constexpr int bits() {
    return sizeof(int_t) * bits_in_byte;
}

}  // namespace gol::common
