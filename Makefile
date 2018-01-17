# Source build variables
SRCDIR := src
INCDIR := include
LIBDIR := lib
BUILDDIR := build
BINDIR := bin
TESTDIR := test

# Googletest build variables
GTEST_DIR := vendor/googletest/googletest
GTEST_INC := -I $(GTEST_DIR) -I $(GTEST_DIR)/include
GTEST_ALL_OBJ:= $(BUILDDIR)/gtest-all.o
GTEST_LIB_NAME := gtest
GTEST_BUILD_LIB := $(LIBDIR)/lib$(GTEST_LIB_NAME).a

# Compiler variables
CC := g++ # This is the main compiler
CFLAGS := -g -std=c++11 -Wc++11-extensions
COMPILE := $(CC) $(CFLAGS)
SRCEXT := cc

# Executables
MAIN_BIN := $(BINDIR)/main
MAIN_SRC := $(subst $(BINDIR)/,$(SRCDIR)/,$(MAIN_BIN)).$(SRCEXT)
MAIN_OBJ := $(subst $(BINDIR)/,$(BUILDDIR)/,$(MAIN_BIN)).o
TEST_ALL_BIN := $(BINDIR)/test_all
TEST_ALL_SRC := $(subst $(BINDIR)/,$(TESTDIR)/,$(TEST_ALL_BIN)).$(SRCEXT)
TEST_ALL_OBJ := $(subst $(BINDIR)/,$(BUILDDIR)/,$(TEST_ALL_BIN)).o

# Find all source code cpp files.
SRC_FILES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
TEST_SRC_FILES := $(shell find $(TESTDIR) -type f -name *.$(SRCEXT))

# Replace src/../filename.cpp with build/../filename.o.
# And omit the executable objects.
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRC_FILES:.$(SRCEXT)=.o))
OBJECTS := $(subst $(MAIN_OBJ),,${OBJECTS})
TEST_OBJECTS := $(patsubst $(TESTDIR)/%,$(BUILDDIR)/%,$(TEST_SRC_FILES:.$(SRCEXT)=.o))
TEST_OBJECTS := $(subst $(TEST_ALL_OBJ),,${TEST_OBJECTS})

LIB := -pthread -L $(LIBDIR)
INC := -I $(INCDIR)

HLINES := "--------------------------------"

# $@ - target
# $^ dependencies
# $< first dependency

# Phony target ensures clean target will always run regardless if there's a
# file named clean in the directory or not.
.PHONY: all clean test

all: $(MAIN_BIN) $(TEST_ALL_BIN)
	@echo "\nBuilding all..."
	@echo $(HLINES)
	@echo "\nRunning all tests: $<"
	@echo $(HLINES)
	$(word 2,$^)

$(MAIN_BIN): $(MAIN_SRC) $(OBJECTS)
	@echo "\nBuilding main target..."
	$(COMPILE) $(INC) $(LIB) -o $@ $(MAIN_SRC) $(OBJECTS)

clean:
	@echo "\nCleaning..."
	@echo $(HLINES)
	$(RM) -r $(BUILDDIR) $(TARGET)

# Source objects
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "\nBuilding individual src object files..."
	@mkdir -p `dirname $@`
	$(COMPILE) $(INC) -c -o $@ $^

# Tests
test: $(TEST_ALL_BIN)
	@echo "\nRunning all tests: $<"
	@echo $(HLINES)
	$<

$(BUILDDIR)/%.o: $(TESTDIR)/%.$(SRCEXT) $(GTEST_BUILD_LIB)
	@echo "\nBuilding individual test object files..."
	@mkdir -p `dirname $@`
	$(COMPILE) $(INC) $(GTEST_INC) -c -o $@ $<

$(GTEST_ALL_OBJ): $(GTEST_DIR)/src/gtest-all.cc
	@echo "\nBuilding googletest object files..."
	@mkdir -p `dirname $@`
	$(COMPILE) $(INC) $(GTEST_INC) -c -o $@ $<

$(GTEST_BUILD_LIB): $(GTEST_ALL_OBJ)
	@echo "\nArchiving googletest object files to lib..."
	ar -rv $@ $^

$(TEST_ALL_BIN): $(GTEST_BUILD_LIB) $(TEST_ALL_SRC) $(OBJECTS) $(TEST_OBJECTS)
	@echo "\nBuilding test_all target..."
	$(COMPILE) $(INC) $(GTEST_INC) $(LIB) -l$(GTEST_LIB_NAME) -o $@ \
		$(TEST_ALL_SRC) $(OBJECTS) $(TEST_OBJECTS)

