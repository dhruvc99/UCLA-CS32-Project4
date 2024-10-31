#include <iostream>
#include <iomanip>
#include <vector>
#include "Employee.h"
#include "Heap.h"

int main()
{
    // Case 1: empty heap 
    std::cout<< "**************** Case 1: test an empty heap **********" << std::endl;
    Heap<char> eh;
    eh.pop();
    print(eh);

    // Case2: test constructor 
    std::cout<< "**************** Case 2: constructor **********" << std::endl;
    Heap<string> sh; // empty min-heap of strings
    std::vector<int> v={1,2,3,2,1,0};
    Heap<int, std::greater<int> > ih(v); // max-heap of integers
    Heap<Employee, CompareBySalary> ITgroup;


    // Case3: push 
    std::cout<< "**************** Case 3: push function **********" << std::endl;
    sh.push("B","A", "C");
    sh.push("D");
    
    Employee tom("Tom", 100);
    Employee jim("Jim", 200);
    Employee jerry("Jerry", 101);
    ITgroup.push(tom);
    ITgroup.push(jerry);
    ITgroup.push(jim);

    ih.push(10); ih.push(10,20);
    print(ih, sh, ITgroup);

    // Case4: top and pop
    std::cout<< "**************** Case 4: top and pop  ****" << std::endl;
    std::cout << sh.top() << std::endl;
    sh.pop();
    print(sh);
    std::cout << sh.top() << std::endl;
    sh.pop();
    sh.pop();
    print(sh);

    return 0;
}
