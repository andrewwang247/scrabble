# Personal Makefile for One Time Pad.
CXX = g++
CXX_FLAGS = -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic
OPT = -O3 -DNDEBUG
DEBUG = -g3 -DDEBUG
EXECUTABLE = scrabble
OBJECTS = dictionary

# Build optimized executable.
scrabble : $(EXECUTABLE).cpp $(OBJECTS).cpp
	$(CXX) $(CXX_FLAGS) $(OPT) $(OBJECTS).cpp $(EXECUTABLE).cpp -o $(EXECUTABLE)

# Build with debug features.
debug : $(EXECUTABLE).cpp $(OBJECTS).cpp
	$(CXX) $(CXX_FLAGS) $(DEBUG) $(OBJECTS).cpp $(EXECUTABLE).cpp -o $(EXECUTABLE)_debug


# Remove executable and all runtime outputs.
.PHONY : clean
clean : 
	rm -f $(EXECUTABLE) $(EXECUTABLE)_debug *.o
