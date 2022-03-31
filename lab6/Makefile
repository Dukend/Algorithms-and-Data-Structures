CXX=g++
CXXFLAGS=-Wall -std=c++11 -O2 -lm -Werror -Wno-sign-compare -pedantic
all:solution
solution: main.o bigint.o
	$(CXX) $(CXXFLAGS) -o solution main.cpp bigint.cpp
main.o: bigint.hpp
bigint.o: bigint.hpp
clean: 
	rm -f *.o solution