#include <iostream>
#include <sstream>
#include <ctype.h>
#include <functional>
#include "parser.h"

std::stringstream ss;
std::stringstream ss2;

void foo1(long long i)
{
    ss << " digit " << i;
}

void foo2(const std::string &i)
{
    ss << " string " << i;
}

void foo3()
{
    ss << "start";
}

void foo4()
{
    ss << " end";
}

void foo5(long long i)
{
    ss2 << i * i << " ";
}

void foo6(const std::string &i)
{
    ss2 << i + "a ";
}


void Test1()
{
    Parser parser;
    std::string text("123   abc 12ab\n145 54\t678f   ");
    parser.SetDigitTokenCallback(foo1);
    parser.SetStringTokenCallback(foo2);
    parser.SetStartCallback(foo3);
    parser.SetEndCallback(foo4);
    parser.TokenParser(text);
    std::string result;
    getline(ss, result);
    assert(result == "start digit 123 string abc string 12ab digit 145 digit 54 string 678f end");
}

void Test2()
{
    Parser parser;
    std::string text("12 abc 12ab  25");
    parser.SetDigitTokenCallback(foo5);
    parser.SetStringTokenCallback(foo6);
    parser.TokenParser(text);
    std::string result;
    getline(ss2, result);
    assert(result == "144 abca 12aba 625 ");
}

void Test3()
{
    Parser parser;
    std::string text("12 dkd");
    parser.TokenParser(text);
}


int main()
{
    Test1();
    Test2();
    Test3();

    std::cout << "Success!\n";

    return 0;
}
