#include "binary_tree.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {

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

    // b.erase(100);

    std::cout << "inorder\n";
    ycontainer::util::print(b,ycontainer::traversal_e::inorder);

    // std::cout << "preorder\n";
    // ycontainer::util::print(b,ycontainer::traversal_e::preorder);

    // std::cout << "postorder\n";
    // ycontainer::util::print(b,ycontainer::traversal_e::postorder);

    ycontainer::util::mirror(b);
    std::cout << "inorder after mirror\n";
    ycontainer::util::print(b,ycontainer::traversal_e::inorder);
    return 0;
}
