#include<vector>
#include<iostream>
#include"colortree.h"
using namespace std;
int main()
{
    vector<vector<int> > map =
          { { 0, 1, 2, 3},
            { 0, 0, 1, 0},
            { 0, 0, 0, 0},
            { 0, 0, 0, 0}};
      
      // find path from node0 to node2
      int shortest1 = dijkstra(map, 0, 2);

      // find path from node2 to node0
      int shortest2 = dijkstra(map, 2, 0);
    
      cout << "Shortest path from 0 to 2 is " << shortest1 << endl;
      cout << "Shortest path from 2 to 0 is " << shortest2 << endl;
    
    // ColorBST<int> t;
    // std::cout << "**************************" << std::endl;
    // t.ascending_print();
    // std::cout << "**************************" << std::endl;
    // try {
    //     t.largest();
    // } catch (std::logic_error& e) {
    //     std::cout << e.what() << std::endl;
    // }
    // std::cout << "**************************" << std::endl;
    // try {
    //     t.second_largest();
    // } catch (std::logic_error& e) {
    //     std::cout << e.what() << std::endl;
    // }
    
    // // test one-element tree
    // std::cout << "**************************" << std::endl;
    // t.insert(1, 'b');
    // try {
    //     t.second_largest();
    // } catch (std::logic_error& e) {
    //     std::cout << e.what() << std::endl;
    // }
    
    // // add elements
    // std::cout << "**************************" << std::endl;
    // t.insert(1, 'b');
    // t.insert(2, 'b');
    // t.insert(0, 'b');
    // t.insert(0, 'b'); // makes no effect to a tree
    // t.insert(3, 'r');
    // std::cout << t.largest() << " " << t.second_largest() << std::endl;

    // std::cout << t.BlackRoot() << std::endl;
    // std::cout << t.NoDoubleRed() << std::endl;
    // std::cout << t.BlackDepth() << std::endl;
    
    // // remove elements
    // std::cout << "**************************" << std::endl;
    // t.descending_print();
    // std::cout << "**************************" << std::endl;
    // t.erase(0); // Removing leaf
    // t.erase(1); // Removing element with one child
    // t.ascending_print();

    // std::cout << t.BlackRoot() << std::endl;
    // std::cout << t.NoDoubleRed() << std::endl;
    // std::cout << t.BlackDepth() << std::endl;

    return 0;
} 
