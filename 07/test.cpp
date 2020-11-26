#include <iostream>
#include <sstream>
#include "vector.h"

void Test1() {
    vector<int> data1 = { 9, 8, 1, 3, 6, 5, 6 };
    assert(data1.size() == 7);
    assert(data1.capacity() == 7);
    data1.reserve(60);
    assert(data1.size() == 7);
    assert(data1.capacity() == 60);
    data1.resize(100);
    assert(data1.size() == 100);
    assert(data1.capacity() == 100);
    data1.clear();
    assert(data1.empty() == true);
}

void Test2() {
    vector<int> data2 = { 9, 8, 1, 3, 6, 5, 6 };
    assert(data2[3] == 3);
    int a = 10;
    data2.push_back(a);
    assert(data2[7] == 10);
    data2.emplace_back(95);
    assert(data2[8] == 95);
}

void Test3() {
    vector<int> data1 = { 9, 8, 1, 3, 6, 5, 6 };
    std::stringstream ss;
    for(vector<int>::iterator it = data1.begin(); it != data1.end(); ++it) {
        ss << *it << " ";
    }
    std::string str;
    getline(ss, str);
    assert(str == "9 8 1 3 6 5 6 ");
    
    std::stringstream ss2;
     for(vector<int>::reverse_iterator it = data1.rbegin(); it != data1.rend(); ++it) {
           ss2 << *it << " ";
       }
    std::string str2;
    getline(ss2, str2);
    assert(str2 == "6 5 6 3 1 8 9 ");
}

int main()
{
    Test1();
    Test2();
    Test3();
    
    std::cout << "Success!\n";
    return 0;
}
