#include <iostream>
#include <sstream>
#include "bigint.h"

void Test1() {
    BigInt n;
    BigInt a(123);
    BigInt b("123456789012345678901234567890");
    BigInt c(-1234);
    BigInt d("-123451234512345");
    assert(a - a == 0);
    assert(a < b && c <= b && c > d && d >= d);
    assert(a + b == std::string("123456789012345678901234568013"));
    assert(c - a == - 123 - 1234);
    assert(c - d == std::string("123451234511111"));
    assert(b + d == std::string("123456789012345555450000055545"));
    assert(a * c == -151782);
    assert(b * d == std::string("-15240893012504183861455418386130300945602050"));
}
    

void Test2() {
    BigInt a(123);
    BigInt c(-1123);
    BigInt z = std::move(a);
    a = z + c;
    assert(a == -1000);
    assert(a != -a);
}

void Test3() {
    BigInt n;
    n = BigInt("-123451234512345");
    std::stringstream ss;
    ss << n << std::endl;
    std::string s;
    getline(ss, s);
    assert(s == "-123451234512345");
}

int main()
{
    Test1();
    Test2();
    Test3();
    
    std::cout << "Success!\n";
    return 0;
}
