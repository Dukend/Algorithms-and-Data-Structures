CXX=g++
CXXFLAGS=-std=c++17 -pedantic -Wall -O2
all:solution
solution: main.o TAvl.o TAvlFile.o TData.o
	$(CXX) $(CXXFLAGS) -o solution main.cpp TAvl.cpp TAvlFile.cpp TData.cpp
main.o: TAvl.hpp TAvlFile.hpp TData.hpp
TAvl.o: TAvl.hpp TData.hpp
TAvlFile.o: TAvl.hpp TAvlFile.hpp TData.hpp
TData.o: TData.hpp
clean: 
	rm -f *.o solution