#include <iostream>
#include <cstdio>
#include "alloc.h"

void Test1()
{
    Allocator Alloc;
    Alloc.makeAllocator(10);
    char *tmp = Alloc.alloc(5);
    for(int i = 0; i < 5; i++) {
        tmp[i] = i;
    }
    char *tmp2 = Alloc.alloc(5);
    for(int i = 0; i < 5; i++) {
        tmp2[i] = i + 5;
    }
    assert(*tmp == 0);
    assert(tmp[9] == 9);
}

void Test2()
{
    Allocator Alloc;
    Alloc.makeAllocator(10);
    char *tmp = Alloc.alloc(5);
    for(int i = 0; i < 5; i++) {
        tmp[i] = i;
    }
    Alloc.reset();
    char *tmp2 = Alloc.alloc(5);
    assert(tmp[4] == 4);
    assert(tmp2[4] == 4);
}

void Test3()
{
    Allocator Alloc;
    Alloc.makeAllocator(10);
    char *tmp = Alloc.alloc(5);
    tmp = Alloc.alloc(6);
    assert(tmp == nullptr);
    Alloc.reset();
    tmp = Alloc.alloc(6);
    assert(tmp != nullptr);
}

void Test4()
{
    Allocator Alloc;
    Alloc.makeAllocator(10);
    Alloc.makeAllocator(10);
}

void Test5()
{
    Allocator Alloc;
    char *tmp = Alloc.alloc(6);
    assert(tmp == nullptr);
}

int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    
    std::cout << "Success!\n";

    return 0;
}
