#include "gtest/gtest.h"
#include "matrix.hpp"

using namespace ylib::math;

TEST(matrixTest, allocator_test) {
    const int allocator = 10;
    matrix<int> mat1(4,4,allocator);

    for(size_t i{}; i < mat1.row_size(); i++) {
        for(size_t j{}; j < mat1.col_size(); j++) {
            EXPECT_EQ(mat1(i,j), allocator);
        }
    }
}

TEST(matrixTest, copy_ctor_test) {
    matrix<float> mat1(4,4,13);
    matrix<float> mat2 = mat1;

    EXPECT_EQ(mat1.row_size(), mat2.row_size());
    EXPECT_EQ(mat1.col_size(), mat2.col_size());
    EXPECT_EQ(
        memcmp(mat1.get_data(), mat2.get_data(), mat1.size()*sizeof(float)),
        0
    );

}

TEST(matrixTest, overloaded_equality_test) {
    matrix<float> mat1(4,4,1);
    matrix<float> mat2(4,4,1);
    
    EXPECT_TRUE(mat1 == mat2);
}

TEST(matrixTest, get_data_test) {
    matrix<float> mat1(10,10,99);
    auto data =  mat1.get_data();   
}

TEST(matrixTest, resize_test) {
    
    long default_value = 45;
    bool preserve{};

    ///// with preserve set to true
    matrix<long> mat1(2000,2000,default_value);
    size_t old_row_size = mat1.row_size();
    size_t old_col_size = mat1.col_size();

    preserve = true;
    mat1.resize(3,3,preserve);
    size_t new_row_size = mat1.row_size();
    size_t new_col_size = mat1.col_size();

    for(size_t i{};i<new_row_size;i++) {
        for(size_t j{};j<new_col_size;j++) {
            if(i < old_row_size && j < old_col_size) {
                EXPECT_EQ(mat1(i,j), default_value);
            } else EXPECT_EQ(mat1(i,j), long{});
        }
    }
    
    ///// with preserve set to false
    matrix<long> mat2(2000,2000,default_value);
    old_row_size = mat2.row_size();
    old_col_size = mat2.col_size();

    preserve = false;
    mat2.resize(1920,1080,preserve);
    new_row_size = mat2.row_size();
    new_col_size = mat2.col_size();

    for(size_t i{};i<new_row_size;i++) {
        for(size_t j{};j<new_col_size;j++) {
            EXPECT_EQ(mat2(i,j), long{});
        }
    }

    // std::function<void()> func = [&]{
    //     for(size_t i{};i<mat1.row_size();i++) {
    //         for(size_t j{};j<mat1.col_size();j++) {
    //             std::cout << mat1(i,j) << " ";
    //         } std::cout << "\n";
    //     } std::cout << std::endl;
    // };

}

TEST(matrixTest, nonsquare_matrix_test) {
    matrix<uint8_t> mat1(100,80);

    // for(size_t i{};i<mat1.row_size();i++) {
    //     for(size_t j{};j<mat1.col_size();j++) {
    //         std::cout << mat1(i,j) << " ";
    //     } std::cout << "\n";
    // } std::cout << "\n";

    mat1.resize(80,100);
}