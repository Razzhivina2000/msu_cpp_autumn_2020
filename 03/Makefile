CXX=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable
all: my_prog
test: my_prog
	./my_prog

my_prog: test.o matrix.o
	$(CXX) $(CXXFLAGS) -o my_prog test.o matrix.o

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

alloc.o: matrix.cpp
	$(CXX) $(CXXFLAGS) -c matrix.cpp 
clean:
	rm -rf *.o my_prog