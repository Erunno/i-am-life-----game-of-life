#include <cstdlib>
#include <ctime>
#include <iostream>

#include "common/device.hpp"
#include "grids/basic/grid.hpp"
#include "grids/bit_packed/grid.hpp"
#include "grids/common/border_policy.hpp"
#include "kernels/basic/algorithm.hpp"
#include "traverseres/cpu/basic.hpp"

using grid_t =
    gol::grids::basic::grid<gol::common::device::CPU, gol::grids::common::wrapped_around_policy>;

using algorithm_t = gol::kernels::cpu::basic::algorithm<grid_t>;

using traverser_t = gol::traverseres::cpu::basic::traverser<grid_t, algorithm_t>;

int main() {
    std::cout << "Hello, World!" << std::endl;

    int dim_x = 10, dim_y = 10;
    int iters = 10;

    grid_t myGrid(dim_x, dim_y);

    // random initialization use random values
    std::srand(std::time(nullptr));

    for (int y = 0; y < dim_y; ++y) {
        for (int x = 0; x < dim_x; ++x) {
            myGrid.set(x, y, std::rand() % 2);  // Random pattern
        }
    }

    // traverser

    traverser_t traverser;
    traverser.initialize(myGrid, iters);
    traverser.run();

    auto resultGrid = traverser.fetch_result_to_cpu();

    // print
    for (int y = 0; y < dim_y; ++y) {
        for (int x = 0; x < dim_x; ++x) {
            std::cout << resultGrid->get(x, y) << " ";
        }
        std::cout << std::endl;
    }
}
