#include <iostream>
#include "format.h"

void Test1() {
    assert(format("{1}+{1} = {0}", 2, "one") == "one+one = 2");
    std::stringstream ss;
    ss << format("{0} + {1} + {0} = {2}", 1, 2, 4);
    std::string s;
    getline(ss, s);
    assert(s == "1 + 2 + 1 = 4");
}

void Test2() {
    std::string s;
    s = format("{0} {1} {2} {3} {4}", 1, 2, 3, 4);
    getline(ss_error, s);
    assert(s == "IndexError: index out of range");
    s = format("{0}{12", 1);
    getline(ss_error, s);
    assert(s == "FormatError: String is invalid");
    s = format("{11111111111111111111111111}", 1);
    getline(ss_error, s);
    assert(s == "IndexError: index out of range");
}

int main()
{
    Test1();
    Test2();

    std::cout << "Success!\n";

    return 0;
}
