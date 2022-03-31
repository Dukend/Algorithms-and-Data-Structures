CC=g++
CFLAGS=-std=c++14 -pedantic -Wall -Wextra -O2
OUTPUT=solution

all: main.cpp corasik.o
	$(CC) $(CFLAGS) main.cpp corasik.o -o $(OUTPUT)
corasik.o: corasik.cpp corasik.hpp
	$(CC) $(CFLAGS) -c corasik.cpp -o corasik.o


clean:
	rm -f *.o $(OUTPUT) benchmark
