CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Wfatal-errors -I.
LDFLAGS = -g
LDLIBS =

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:%.cpp=%.o)

TEST_SRC = $(wildcard test/*.cpp)
TEST_OBJ = $(TEST_SRC:%.cpp=%.o)

# default target
all: compile se1.out

# test
test: compile compile_test se1_test.out

# link everything together for executable
se1.out: $(OBJ)
	$(CXX) -o se1.out $(LDFLAGS) $(OBJ) $(LDLIBS)

# link everything together for test executable
se1_test.out: $(TEST_OBJ) $(OBJ)
	$(CXX) -o se1_test.out $(LDFLAGS) $(filter-out src/main.o, $(OBJ)) $(TEST_OBJ) $(LDLIBS)

# target for regenerating doxygen
.PHONY: docs
docs:
	rm -rf docs/html
	doxygen doxygen_config

compile: $(OBJ)

compile_test: $(TEST_OBJ)

clean:
	rm -rf $(OBJ)
	rm -rf $(TEST_OBJ)
	rm -rf se1_test.out
	rm -rf se1.out

deps:
	$(CXX) -MM $(CXXFLAGS) $(SRC) $(TEST_SRC) > makefile.dependencies

include makefile.dependencies