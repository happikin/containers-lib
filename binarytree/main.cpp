#include "binary_tree.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {
    ycontainer::binary_tree<int> b;
    b.insert(10);
    b.insert(12);
    b.insert(12);
    b.insert(7);
    b.insert(9);

    ycontainer::binary_tree<int>::node* tree_node_ptr = nullptr;
    if((tree_node_ptr = b.find(10)) == nullptr) {
        std::cout << "could not find\n";
    } else {
        std::cout << "found\n";
        tree_node_ptr->data = 100;
    }

    if(b.find(10) == nullptr) {
        std::cout << "could not find\n";
    } else std::cout << "found\n";

    return 0;
}
