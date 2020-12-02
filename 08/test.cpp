#include <iostream>
#include <vector>
#include <mutex>
#include <future>
#include <queue>
#include <condition_variable>
#include <unistd.h>
#include "ThreadPool.h"


struct A {};

void foo(const A&) {}

void Test1() {

    ThreadPool pool(8);

    auto task1 = pool.exec(foo, A());
    task1.get();
    
    auto task2 = pool.exec([]() { return 1; });
    assert(task2.get() == 1);
}

int a = 0;
void foo2() {
    a += 10;
}

void foo3(int b, int c) {
    a += b % c;
}
void Test2() {
    ThreadPool pool(3);

    auto task1 = pool.exec(foo2);
    task1.get();
    auto task2 = pool.exec(foo2);
    task2.get();
    auto task3 = pool.exec(foo3, 30, 4);
    task3.get();
    auto task4 = pool.exec(foo2);
    task4.get();
    assert(a == 32);
}

std::string foo4(std::string s1, std::string s2) {
    return s1 + s2;
}

void Test3() {
    ThreadPool pool(3);
    auto task1 = pool.exec(foo4, "str1", "str2");
    auto task2 = pool.exec(foo4, "str3", "str4");
    auto task3 = pool.exec(foo4, task1.get(), task2.get());
    assert(task3.get() =="str1str2str3str4");
}

int main()
{
    Test1();
    Test2();
    Test3();

    std::cout << "Success!\n";

    return 0;
}
