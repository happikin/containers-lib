#include <iostream>
#include <algorithm>
#include "matrix.hpp"

int main(int argc, char *argv[]) {
    // matrix<int> mat1(2,2,2029);
    ycontainer::matrix<int> mat2 = std::move(ycontainer::matrix<int>(2,2,23));

    ycontainer::matrix<int> mat3(1000,1000,10);
    mat3.resize(1920,1080,true);

    std::vector<int> nums{2,4,1,6,3,4,5,8};

    return 0;
}
