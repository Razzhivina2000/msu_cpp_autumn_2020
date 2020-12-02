CXX=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable
all: my_prog
test: my_prog
	./my_prog

my_prog: test.o parser.o
	$(CXX) $(CXXFLAGS) -o my_prog test.o ThreadPool.o

ThreadPool.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

ThreadPool.o: ThreadPool.cpp
	$(CXX) $(CXXFLAGS) -c ThreadPool.cpp 
clean:
	rm -rf *.o my_prog