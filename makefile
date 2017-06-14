# run "make clean deps" after commenting out/in
#COMPILE_FOR_HARDWARE = 1

# global compiler options
CXX = g++
LDFLAGS = -g

ifdef COMPILE_FOR_HARDWARE
CXXFLAGS = -std=c++11 -g -Wall -Wfatal-errors -I. -IC:\Festo\lib
LDLIBS = -LC:\Festo\lib -lcbw32
else
CXXFLAGS = -std=c++11 -g -Wall -Wfatal-errors -I. -DSIL
LDLIBS = 
endif

# which files are used in the project
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:%.cpp=%.o)

TEST_SRC = $(wildcard test/*.cpp)
TEST_OBJ = $(TEST_SRC:%.cpp=%.o)

# default target
all: se1.out

# test target
test: se1_unit_test.out se1_fsm_test.out

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

# remove object code, executables and test output
clean:
	rm -rf $(OBJ)
	rm -rf $(TEST_OBJ)
	rm -rf output.log
	rm -rf *.out

# update dependencies
.PHONY: deps
deps:
	$(foreach file, $(SRC) $(TEST_SRC), $(CXX) -MM $(CXXFLAGS) -MT $(file:%.cpp=%.o) -MF $(file:%.cpp=%.d) $(file);)

# include dependencies
-include $(OBJ:%.o=%.d)
-include $(TEST_OBJ:%.o=%.d)
