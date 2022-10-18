#include "binary_tree.hpp"

int main(int argc, char const *argv[]) {
    ycontainer::binary_tree<int> b;
    b.insert(10);
    b.insert(12);
    b.insert(12);
    b.insert(7);
    b.insert(9);

    return 0;
}
