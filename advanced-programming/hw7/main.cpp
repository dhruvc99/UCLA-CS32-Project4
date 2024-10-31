#include <iostream>
#include <functional>
#include "Safedeque.h"

using namespace std;

int main()
{
    cout << "********** print empty deque *********" << endl;
    Safedeque<int> sd;
    // sd.print();
    // cout << "********** add elements *********" << endl;
    // // add elements
    sd.push_front(1);
    sd.push_front(2);
    // sd.pop_back();
    sd.push_front(3);
    sd.push_back(4);
    sd.push_back(5);
    sd.push_front(6);
    // sd.push_back(7);
    // sd.print();
    // cout << "********* real array elements**********" << endl;
    // sd.real_print();
    // cout << "********** element squares *********" << endl;
    Safedeque<int>::Iterator iter1 = sd.begin();
    // for_each(sd.begin(), sd.end(), [](int &x){x=x*x;});
    // sd.print();
    sd.real_print();
    // cout << "********* work with iterators **********" << endl;
    // auto iter2 = sd.begin();
    // ++iter2;
    // cout << *iter2 << endl;
    // iter2 = sd.end();
    // --iter2;
    // *iter2 = 100;
    // sd[3] = 20;
    // sd.print();
    // cout << "********* copy control **********" << endl;
    Safedeque<int> sd2;
    auto sd3(sd); 
    sd2=sd3;
    
    // sd3.print();
    sd3.real_print();
    // sd2.print();
    sd2.real_print();
    // cout << "********* throw error **********" << endl;
    // auto myiter = sd2.end();
    // // ++myiter; // cause out-of-range error
    // // sd2[1000] = 10; // cause out-of-range error
    return 0;
}
