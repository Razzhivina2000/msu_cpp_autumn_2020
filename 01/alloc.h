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
