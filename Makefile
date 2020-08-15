# Personal Makefile for One Time Pad.
CXX := g++ -std=c++17
CXX_FLAGS := -Wall -Werror -Wextra -Wconversion -pedantic -Wfloat-equal -Wduplicated-branches -Wduplicated-cond -Wshadow -Wdouble-promotion -Wundef 
OPT := -O3 -DNDEBUG
DEBUG := -g3 -DDEBUG

EXECUTABLE := scrabble

# Build optimized executable.
scrabble : $(EXECUTABLE).cpp
	$(CXX) $(CXX_FLAGS) $(OPT) $(EXECUTABLE).cpp -o $(EXECUTABLE)

# Build with debug features.
debug : $(EXECUTABLE).cpp
	$(CXX) $(CXX_FLAGS) $(DEBUG) $(EXECUTABLE).cpp -o $(EXECUTABLE)


# Remove executable and all runtime outputs.
.PHONY : clean
clean : 
	rm -f $(EXECUTABLE)
