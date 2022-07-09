#include "gtest/gtest.h"
#include "list.hpp"
#include <list>
#include <chrono>
TEST(ListTest, length_test) {
    ycontainer::list<int> l{1,2,3,4};
    EXPECT_EQ (l.length(),4);
}

TEST(ListTest, iterator_test) {
    ycontainer::list<int> list{1,2,3,4,5};
    ycontainer::list<int>::iterator it = list.begin();
    EXPECT_EQ((*it), list.at(0));
}

TEST(ListTest, overloaded_addition_test1) {

    ycontainer::list<int> list1{2,1,44,5,768,45};
    ycontainer::list<int> list2{23,66,41,656};
    ycontainer::list<int> list3;

    list3 = list1 + list2;

    EXPECT_EQ(list3.length(), list1.length() + list2.length());
}

TEST(ListTest, range_loop_test) {
    ycontainer::list<std::string> names{"Yashesvi","Arshi","Ajay","Chitralekha"};
    unsigned int i{0};
    for(auto& item:names)
        EXPECT_EQ(item, names.at(i++));
}

TEST(ListTest, overloaded_addition_test2) {
    ycontainer::list<int> list1,list2;
    for(int i=0;i<10000;i++) {
        list1.append(i*2);
        list2.append(i*3);
    }
    ycontainer::list<int> list3;
    list3 = list1 + list2;
    
    EXPECT_EQ(list3.length(), list1.length() + list2.length());
}

TEST(ListTest,sort_test) {
    ycontainer::list<int> list{1,3,2,6,4,34,65,65,7,4,65,87,98,78,67,58,64,63,6,63,63,2552,53,25545,43252,5523,52,52,2555,45,45355,57357,34,5,3,34,4353,45345,3544,3545,64545,645,456,45645,645,645,6,46,45,6456,45,4,47,3735,8282,4,4455,645,6456,45,645,656,756,65,88,678,7623,432,4324,324,325,45,34,534,34,645,645,645,76,457,76,456,3,452,43,24,31,42,342,3,325,346,45,76,765,6556,8};
    list.sort();
    for(auto i{0};i<list.length()-1;i++) {
        EXPECT_LE(list.at(i), list.at(i+1));
    }
    // for(auto& i:list) {
    //     std::cout << i << " ";
    // }
}

TEST(ListTest, extract_for_test) {
    ycontainer::list<int> list{1,2,3,4,5,6,7};
    //std::cout << list.count([&](int& dataItem){ return dataItem%2==0;}) << std::endl;
    ycontainer::list<int> outList;
    outList = list.extract_for([&](int& dataItem){ return dataItem%2==0;});
    // for(auto& item:outList)
    //     std::cout << item << std::endl;

    ycontainer::list<int> outList2 = list.extract_for([&](int& dataItem){ return dataItem<=5;},100);
    //for(auto& item:outList2) std::cout << item << std::endl;
}

TEST(ListTest, at_test) {
    ycontainer::list<int> list{1,2,3,4,5};
    list.at(1) = 22;
    EXPECT_NE(list.at(1), 2);
}

TEST(ListTest, pop_front_test) {
    ycontainer::list<int> list;
    int insertedValue = 1301;
    list.insert(insertedValue,0);
    uint oldSize = list.length();
    auto poppedValue = list.pop_front();
    uint newSize = list.length();

    EXPECT_EQ(oldSize, newSize+1);
    EXPECT_EQ(insertedValue, poppedValue);
}

TEST(ListTest, multithreaded_insert_test) {
    std::mutex _mutex;
    ycontainer::list<std::string> buffer;

    std::atomic<size_t> count{0};

    //std::list<std::string> buffer;
    std::function<void()> fun1 = [&]{
        while (true) {
            if(count >= 5) break;
            {
                std::lock_guard<std::mutex> guard(_mutex);
                buffer.append("A");
            }
            count++;
        }
    };
    std::function<void()> fun2 = [&]{
        while (true) {
            if(count >= 5) break;
            {
                std::lock_guard<std::mutex> guard(_mutex);
                buffer.append("B");
            }
            count++;
        }
    };
    
    std::thread t1(fun1);
    std::thread t2(fun2);


    t1.join();
    t2.join();

    for(auto& item:buffer) {
        std::cout << item << std::endl;
    }
}