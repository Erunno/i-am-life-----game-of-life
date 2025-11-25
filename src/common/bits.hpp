#pragma once

namespace gol::common {

template <typename int_t>
constexpr int bits() {
    return sizeof(int_t) * 8;
}

}  // namespace gol::common