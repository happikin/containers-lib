#include <iostream>
#include <thread>
#include <vector>
#include "list.hpp"

using namespace std;
using namespace chrono;

void show(List<int>& list) {
    for(auto& item:list) {
        std::cout << item << std::endl;
    }
}

int main(int argc, char const *argv[]) {

    List<int> list;

    for(int i=0;i<5;i++) {
        list.append(i*2);
    }

    try {
        list.insert(1301);
    } catch(const char* e) {
        std::cout << e << std::endl;

    }

    show(list);
    std::cout << "Size: " << list.length() << std::endl;

    list.erase(3);
    std::cout << "---------------\n";
    show(list);

    for(ulong i=0;i<list.length();i++) {
        std::cout << list.at(i) << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    show(list);
    std::cout << "-----------\n";
    list.popBack();
    show(list);

    List<int>::Iterator it = list.begin();
    for(ulong i=0;i<list.length()-1;i++) {
        it++;
    }

    std::cout << "Data to del: " << *it << std::endl;
    list.erase(it);
    show(list);

    return 0;
}
