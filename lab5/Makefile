CXX = g++
CXXFLAGS = -std=c++17 -O3 -pedantic -Wall -Wno-unused-variable
EXECUTABLE = solution

EXE_SRC = main.cpp suffix_tree.cpp suffix_array.cpp
EXE_OBJ = $(EXE_SRC:.cpp=.o)

all : $(EXECUTABLE)

$(EXECUTABLE) : $(EXE_OBJ)
	$(CXX) $(CXXFLAGS) $(EXE_OBJ) -o $(EXECUTABLE)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)