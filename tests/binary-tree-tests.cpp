#include "gtest/gtest.h"
#include "binary_tree.hpp"

TEST(BinaryTreeTest, default_ctor_test) {
    ycontainer::binary_tree<int> b(
    ycontainer::traversal_e::default_order);
    
    b.insert(100);
    b.insert(150);
    b.insert(125);
    b.insert(120);
    b.insert(130);
    b.insert(175);
    b.insert(155);
    b.insert(180);

    b.insert(50);
    b.insert(75);
    b.insert(85);
    b.insert(70);
    b.insert(25);
    b.insert(35);
    b.insert(15);

    ycontainer::binary_tree<int>::node* tree_node_ptr = nullptr;
    if((tree_node_ptr = b.find(100)) == nullptr) {
        std::cout << "could not find\n";
    } else {
        std::cout << "found\n";
    }

    b.erase(100);
}