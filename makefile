CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Wfatal-errors -Werror
LDFLAGS = -g
LDLIBS =

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:%.cpp=%.o)

# default target
all: compile se1.out

# link everything together for executable
se1.out: $(OBJ)
	$(CXX) -o se1.out $(LDFLAGS) $(OBJ) $(LDLIBS)

# target for regenerating doxygen
.PHONY: docs
docs:
	rm -rf docs/html
	doxygen doxygen_config

compile: $(OBJ)

clean:
	rm -rf $(OBJ)
	rm -rf se1.out

deps:
	$(CXX) -MM $(CXXFLAGS) $(SRC) > makefile.dependencies

include makefile.dependencies