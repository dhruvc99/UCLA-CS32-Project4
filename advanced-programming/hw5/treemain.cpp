#include <iostream>
#include "tree.h"
namespace HW5 =  UCLA_Spring2021_PIC10C_HW5;

int main()
{
    // test empty tree
    HW5::BinarySearchTree<int> t;
    std::cout << "**************************" << std::endl;
    t.ascending_print();
    std::cout << "**************************" << std::endl;
    try {
        t.largest();
    } catch (std::logic_error& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "**************************" << std::endl;
    try {
        t.second_largest();
    } catch (std::logic_error& e) {
        std::cout << e.what() << std::endl;
    }
    
    // test one-element tree
    std::cout << "**************************" << std::endl;
    t.insert(1);
    try {
        t.second_largest();
    } catch (std::logic_error& e) {
        std::cout << e.what() << std::endl;
    }
    
    // add elements
    std::cout << "**************************" << std::endl;
    t.insert(1);
    t.insert(2);
    t.insert(0);
    t.insert(0); // makes no effect to a tree
    t.insert(3);
    std::cout << t.largest() << " " << t.second_largest() << std::endl;
    
    // remove elements
    std::cout << "**************************" << std::endl;
    t.descending_print();
    std::cout << "**************************" << std::endl;
    t.erase(0); // Removing leaf
    t.erase(10); // Removing element with one child
    t.ascending_print();
    return 0;
}
