#include <iostream>
#include "matrix.hpp"
using namespace ylib::math;

int main(int argc, char *argv[]) {
    // matrix<int> mat1(2,2,2029);
    matrix<int> mat2 = std::move(matrix<int>(2,2,23));

    matrix<int> mat3(1000,1000,10);
    mat3.resize(1920,1080,true);
    return 0;
}
