#include <iostream>
#include <cstdio>

class Allocator
{
    size_t max_size;
    size_t offset;
    char *pointer;
public:
    Allocator();
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
};

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

int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    
    std::cout << "Success!\n";

    return 0;
}
