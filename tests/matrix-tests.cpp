#include "gtest/gtest.h"
#include "matrix.hpp"

TEST(MatrixTest, allocator_test) {
    const int allocator = 10;
    ycontainer::matrix<int> mat1(4,4,allocator);

    for(size_t i{}; i < mat1.row_size(); i++) {
        for(size_t j{}; j < mat1.col_size(); j++) {
            EXPECT_EQ(mat1(i,j), allocator);
        }
    }
}

TEST(MatrixTest, copy_ctor_test) {
    ycontainer::matrix<float> mat1(4,4,13);
    ycontainer::matrix<float> mat2 = mat1;

    EXPECT_EQ(mat1.row_size(), mat2.row_size());
    EXPECT_EQ(mat1.col_size(), mat2.col_size());
    EXPECT_EQ(
        memcmp(mat1.get_data(), mat2.get_data(), mat1.size()*sizeof(float)),
        0
    );

}

TEST(MatrixTest, overloaded_equality_test) {
    ycontainer::matrix<float> mat1(4,4,1);
    ycontainer::matrix<float> mat2(4,4,1);
    
    EXPECT_TRUE(mat1 == mat2);
}

TEST(MatrixTest, get_data_test) {
    ycontainer::matrix<float> mat1(10,10,99);
    auto data =  mat1.get_data();   
}

TEST(MatrixTest, resize_test) {
    
    long default_value = 45;
    bool preserve{};

    ///// with preserve set to true
    ycontainer::matrix<long> mat1(2000,2000,default_value);
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
    ycontainer::matrix<long> mat2(2000,2000,default_value);
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

TEST(MatrixTest, nonsquare_matrix_test) {
    ycontainer::matrix<uint8_t> mat1(100,80);

    // for(size_t i{};i<mat1.row_size();i++) {
    //     for(size_t j{};j<mat1.col_size();j++) {
    //         std::cout << mat1(i,j) << " ";
    //     } std::cout << "\n";
    // } std::cout << "\n";

    mat1.resize(80,100);
}

TEST(MatrixTest, reset_test) {
    ycontainer::matrix<std::string> mat1(2,2,"yashesvi");
    
    mat1.reset();

    EXPECT_EQ(mat1.get_data(), nullptr);
    EXPECT_EQ(mat1.row_size(), 0);
    EXPECT_EQ(mat1.col_size(), 0);
}

TEST(MatrixTest, identity_type_test) {
    ycontainer::matrix<int> mat1(5,5,ycontainer::matrix_type::identity);
    for(size_t i{}; i<mat1.row_size(); i++) {
        for(size_t j{}; j<mat1.col_size(); j++) {
            if(i == j) {
                EXPECT_EQ(1, mat1(i,j));
            } else EXPECT_EQ(0, mat1(i,j));
        }
    }
    // ycontainer::matrix<int>::print(mat1);
}

TEST(MatrixTest, square_matrix_test) {
    ycontainer::matrix<int> mat(5,5);
    EXPECT_EQ(mat.is_square_matrix(), true);
}

TEST(MatrixTest, symmetricity_test) {
    ycontainer::matrix<int> mat(50,50, ycontainer::matrix_type::identity);
    EXPECT_TRUE(mat.is_symmetric_matrix());
    mat(2,3) = 43;
    EXPECT_FALSE(mat.is_symmetric_matrix());
    // ycontainer::matrix<int>::print(mat);
}

TEST(MatrixTest, identity_check_test) {
    ycontainer::matrix<int> mat(5,5,ycontainer::matrix_type::identity);
    EXPECT_TRUE(mat.is_identity_matrix());
}

TEST(MatrixTest, get_first_index_test) {
    ycontainer::matrix<int> mat(5,5);
    size_t i=2;
    size_t j=3;
    mat(i,j) = 4;
    // ycontainer::matrix<int>::print(mat);
    std::pair<size_t,size_t> index_pair = mat.get_first_index(4);
    
    EXPECT_EQ(i,index_pair.first);
    EXPECT_EQ(j,index_pair.second);

}

TEST(MatrixTest, get_all_index_test1) {
    ycontainer::matrix<int> mat(5,5);
    
    size_t i1 = 1;
    size_t j1 = 3;
    mat(i1,j1) = 44;

    size_t i2 = 3;
    size_t j2 = 4;
    mat(i2,j2) = 44;

    auto indexes = mat.get_all_index(44);

    EXPECT_EQ(indexes[0].first,i1);
    EXPECT_EQ(indexes[0].second,j1);

    EXPECT_EQ(indexes[1].first,i2);
    EXPECT_EQ(indexes[1].second,j2);

    // for(auto& index:indexes) {
    //     std::cout << "(" << index.first << "," << index.second << ")\n";
    // }
}

TEST(MatrixTest, get_all_index_test2) {
    ycontainer::matrix<int> mat(5,5);
    
    size_t i1 = 1;
    size_t j1 = 3;
    mat(i1,j1) = 44;

    size_t i2 = 3;
    size_t j2 = 4;
    mat(i2,j2) = 44;

    std::vector<std::pair<size_t,size_t>> indexes;
    auto index_count = mat.get_all_index(44,indexes);

    EXPECT_EQ(indexes[0].first,i1);
    EXPECT_EQ(indexes[0].second,j1);

    EXPECT_EQ(indexes[1].first,i2);
    EXPECT_EQ(indexes[1].second,j2);

    // for(auto& index:indexes) {
    //     std::cout << "(" << index.first << "," << index.second << ")\n";
    // }
}

TEST(MatrixTest, snip_test) {
    ycontainer::matrix<int> src_matrix(6,6,0);
    ycontainer::matrix<int> dest_matrix;
    
    src_matrix(1,1) = 1;
    src_matrix(1,4) = 1;
    src_matrix(2,2) = 1;
    src_matrix(2,3) = 1;
    src_matrix(3,2) = 1;
    src_matrix(3,3) = 1;
    src_matrix(4,4) = 1;
    src_matrix(4,1) = 1;

    ycontainer::utils::print(src_matrix);

    std::cout << "test for snip_position::top_left\n";
    ycontainer::snip_setting setting{ycontainer::snip_position::top_left,1,1};

    try {
        ycontainer::utils::snip(dest_matrix,src_matrix,setting,2,2);
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    } ycontainer::utils::print(dest_matrix);

    std::cout << "test for snip_position::top_right\n";
    dest_matrix.reset();
    setting = {ycontainer::snip_position::top_right,1,4};

    try {
        ycontainer::utils::snip(dest_matrix,src_matrix,setting,2,2);
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    } ycontainer::utils::print(dest_matrix);
}