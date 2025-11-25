#include <iostream>

#include "grids/basic/grid.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    gol::grids::basic::grid myGrid(10, 10);
    std::cout << "Grid size: " << myGrid.x_size() << "x" << myGrid.y_size() << std::endl;
    return 0;
}