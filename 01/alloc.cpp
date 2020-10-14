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

Allocator::Allocator() {
    max_size = 0;
    offset = 0;
    pointer = nullptr;
}

void Allocator::makeAllocator(size_t maxSize) {
    if(!pointer) {
        pointer = new char[maxSize];
        max_size = maxSize;
    } else {
        std::cout << "MakeAllocator already been called!" << std::endl;
    }
}

char* Allocator::alloc(size_t size) {
    if(max_size - offset < size) {
        return nullptr;
    }
    offset += size;
    return pointer + offset;
}

void Allocator::reset() {
    offset = 0;
}

Allocator::~Allocator() {
    delete [] pointer;
}
