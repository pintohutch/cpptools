# Source build variables.
SRCDIR := src
INCDIR := include
LIBDIR := lib
BUILDDIR := build
BINDIR := bin
TESTDIR := test
TARGET := $(BINDIR)/runner

# Googletest build variables.
GTEST_DIR := vendor/googletest/googletest
GTEST_INC := -I $(GTEST_DIR) -I $(GTEST_DIR)/include
GTEST_BUILD_OBJ := $(BUILDDIR)/gtest-all.o
GTEST_BUILD_LIB := $(LIBDIR)/libgtest.a

# Compiler variables.
CC := g++ # This is the main compiler
SRCEXT := cpp
# Find all source code cpp files.
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
TESTS := $(shell find $(TESTDIR) -type f -name *.$(SRCEXT))
# Replace src/../filename.cpp with build/../filename.o
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g # -Wall
# -pthread - enable multithreading.
LIB := -pthread -L $(LIBDIR)
INC := -I $(INCDIR)

# $@ - target
# $^ dependencies
# $< first dependency

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(CC) -o $(TARGET) $(LIB) $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	$(RM) -r $(BUILDDIR) $(TARGET)

# Tests
$(GTEST_BUILD_OBJ): $(GTEST_DIR)/src/gtest-all.cc
	@echo "Building googletest..."
	@mkdir -p `dirname $@`
	$(CC) $(INC) $(GTEST_INC) -c -o $@ $<

$(GTEST_BUILD_LIB): $(GTEST_BUILD_OBJ)
	ar -rv $@ $^

$(BINDIR)/test_all: $(TESTS) $(GTEST_BUILD_LIB)
	$(CC) $(INC) $(GTEST_INC) -o $@ $^

# Phony target ensures clean target will always run regardless if there's a
# file named clean in the directory or not.
.PHONY: clean
