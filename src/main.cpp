#include <iostream>

#include "common/device.hpp"
#include "grids/basic/grid.hpp"
#include "grids/bit_packed/grid.hpp"
#include "grids/common/border_policy.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    gol::grids::basic::grid<gol::common::device::CPU, gol::grids::common::wrapped_around_policy>
        myGrid(100, 100);
    std::cout << "Grid size: " << myGrid.logical().x_size << "x" << myGrid.logical().y_size
              << std::endl;

    return 0;
}