CXX=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable
all: my_prog
test: my_prog
	./my_prog

my_prog: test.o vector.o
	$(CXX) $(CXXFLAGS) -o my_prog test.o vector.o

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp 

vector.o: vector.cpp
	$(CXX) $(CXXFLAGS) -c vector.cpp
clean:
	rm -rf *.o my_prog