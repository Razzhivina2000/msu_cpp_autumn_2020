CC=g++
FLAGS=-std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable
all: my_prog
test: my_prog
	./my_prog

my_prog: test.o alloc.o
	$(CC) $(FLAGS) -o my_prog test.o alloc.o

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

alloc.o: alloc.cpp
	$(CC) $(FLAGS) -c alloc.cpp 
clean:
	rm -rf *.o my_prog