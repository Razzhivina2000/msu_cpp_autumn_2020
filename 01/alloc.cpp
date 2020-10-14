#include <iostream>
#include <cstdio>
#include "alloc.h"

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
    if(!pointer) {
        std::cout << "Need to call MakeAllocator first!" << std::endl;
        return nullptr;
    }
    if(max_size - offset < size) {
        return nullptr;
    }
    offset += size;
    return pointer + offset - size;
}

void Allocator::reset() {
    offset = 0;
}

Allocator::~Allocator() {
    delete [] pointer;
}


