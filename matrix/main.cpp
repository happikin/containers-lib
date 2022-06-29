#include <iostream>
#include "matrix.hpp"
using namespace ylib::math;

int main(int argc, char *argv[]) {
    // matrix<int> mat1(2,2,2029);
    matrix<int> mat2 = std::move(matrix<int>(2,2,23));

    std::cout << mat2(0,0) << std::endl;

    return 0;
}
