#include "gtest/gtest.h"
#include "list.hpp"

TEST(listTest, test1) {
    //arrange
    //act
    //assert
    List<int> l{1,2,3,4};
    EXPECT_EQ (l.length(),4);
}

TEST(listTest, test2) {
    List<int> list{1,2,3,4,5};
    List<int>::Iterator it = list.begin();
    EXPECT_EQ((*it), list.at(0));
}

TEST(listTest, test3) {

    List<int> list1{2,1,44,5,768,45};
    List<int> list2{23,66,41,656};
    List<int> list3;

    list3 = list1 + list2;

    EXPECT_EQ(list3.length(), list1.length() + list2.length());
}

TEST(listTest, test4) {
    List<std::string> names{"Yashesvi","Arshi","Ajay","Chitralekha"};
    // for(auto& item:names) {
    //     std::cout << item << std::endl;
    // }
}

TEST(listTest, test5) {
    List<int> list1,list2;
    for(int i=0;i<10000;i++) {
        list1.append(i*2);
        list2.append(i*3);
    }
    List<int> list3;
    list3 = list1 + list2;
    
    EXPECT_EQ(list3.length(), list1.length() + list2.length());
}

TEST(listTest,test6) {
    List<int> list{1,3,2,6,4,34,65,65,7,4,65,87,98,78,67,58,64,63,6,63,63,2552,53,25545,43252,5523,52,52,2555,45,45355,57357,34,5,3,34,4353,45345,3544,3545,64545,645,456,45645,645,645,6,46,45,6456,45,4,47,3735,8282,4,4455,645,6456,45,645,656,756,65,88,678,7623,432,4324,324,325,45,34,534,34,645,645,645,76,457,76,456,3,452,43,24,31,42,342,3,325,346,45,76,765,6556,8};
    list.sort();
    for(auto i{0};i<list.length()-1;i++) {
        EXPECT_LE(list.at(i), list.at(i+1));
    }
    // for(auto& i:list) {
    //     std::cout << i << " ";
    // }
}

TEST(listTest, test7) {
    List<int> list{1,2,3,4,5,6,7};
    //std::cout << list.count([&](int& dataItem){ return dataItem%2==0;}) << std::endl;
    List<int> outList;
    outList = list.extractFor([&](int& dataItem){ return dataItem%2==0;});
    // for(auto& item:outList)
    //     std::cout << item << std::endl;

    List<int> outList2 = list.extractFor([&](int& dataItem){ return dataItem<=5;},100);
    for(auto& item:outList2) std::cout << item << std::endl;
}

TEST(listTest, test8) {
    List<int> list{1,2,3,4,5};
    list.at(1) = 22;
    for(auto& item:list)
        std::cout << item << std::endl;
}

TEST(listTest, test9) {
    List<int> list{1,2,3,4,5};
    list.sort(true);
    for(auto& item: list)
        std::cout << item << std::endl;
}

TEST(randomTest, test1) {
    List<int> list;
    list.insert(1,0);
    std::cout << "Size: " << list.length() << std::endl;
    auto e = list.popFront();
    std::cout << "Size: " << list.length() << std::endl;
    std::cout << "Popped ele: " << e;
}