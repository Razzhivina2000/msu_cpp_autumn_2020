#include <iostream>
#include <sstream>
#include "serializers.h"

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

struct Data2
{
    bool a;
    bool b;
    uint64_t c;
    bool d;
    uint64_t f;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d, f);
    }
};

void Test1() {
    Data x { 1, true, 2 };

    std::stringstream stream;
    
    Serializer serializer(stream);
    serializer.save(x);
    Data y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void Test2() {
    Data2 x { false, true, 200, true, 20 };

    std::stringstream stream;
    
    Serializer serializer(stream);
    serializer.save(x);
    Data2 y {false, false, 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void Test3() {
    Data x { 1, true, 2 };

    std::stringstream stream;
    
    Serializer serializer(stream);
    serializer.save(x);
    stream << "2 av";
    Data y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    const Error err2 = deserializer.load(y);
    assert(err2 != Error::NoError);
}

int main()
{
    Test1();
    Test2();
    Test3();
    
    std::cout << "Success!\n";
    return 0;
}
