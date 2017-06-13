CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Wfatal-errors -I.
LDFLAGS = -g
LDLIBS =

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:%.cpp=%.o)

TEST_SRC = $(wildcard test/*.cpp)
TEST_OBJ = $(TEST_SRC:%.cpp=%.o)

# default target
all: compile se1.out

# test
test: compile compile_test se1_unit_test.out se1_fsm_test.out

# link everything together for executable
se1.out: $(OBJ)
	$(CXX) -o se1.out $(LDFLAGS) $^ $(LDLIBS)

# link everything together for unit test executable
se1_unit_test.out: $(filter-out src/main.o, $(OBJ)) $(filter-out test/fsm_test_main.o, $(TEST_OBJ))
	$(CXX) -o se1_unit_test.out $(LDFLAGS) $^ $(LDLIBS)

# link everything together for fsm test executable
se1_fsm_test.out: $(filter-out src/main.o, $(OBJ)) $(filter-out test/unit_test_main.o, $(TEST_OBJ))
	$(CXX) -o se1_fsm_test.out $(LDFLAGS) $^ $(LDLIBS)

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
	rm -rf output.log
	rm -rf *.out

deps:
	$(foreach file, $(SRC) $(TEST_SRC), $(CXX) -MM $(CXXFLAGS) -MT $(file:%.cpp=%.o) -MF $(file:%.cpp=%.d) $(file);)

# Dependencies
-include $(SRC:%.cpp=%.d)
-include $(TEST_SRC:%.cpp=%.d)