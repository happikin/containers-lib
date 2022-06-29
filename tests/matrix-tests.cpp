#include "gtest/gtest.h"
#include "matrix.hpp"

using namespace ylib::math;

TEST(matrixTest, test1) {
    matrix<float> mat1(4,4);
    matrix<float> mat2 = mat1;

    EXPECT_EQ(mat1.row_size(), mat2.row_size());
    EXPECT_EQ(mat1.col_size(), mat2.col_size());
}

TEST(matrixTest, test2) {
    matrix<float> mat1(4,4,1);
    matrix<float> mat2(4,4,1);

    EXPECT_TRUE(mat1 == mat2);
}