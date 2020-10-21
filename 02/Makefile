CC=g++
FLAGS=-std=c++11 -Wall -pedantic -Wextra -Wno-unused-variable
all: my_prog
test: my_prog
	./my_prog

my_prog: test.o parser.o
	$(CC) $(FLAGS) -o my_prog test.o parser.o

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

alloc.o: parser.cpp
	$(CC) $(FLAGS) -c parser.cpp 
clean:
	rm -rf *.o my_prog