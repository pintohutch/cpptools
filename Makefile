CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGET := bin/runner

SRCEXT := cpp
# Find all source code cpp files.
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
# Replace src/../filename.cpp with build/../filename.o
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g # -Wall
# -pthread - enable multithreading.
LIB := -pthread -L lib -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt
INC_DIRS := $(shell find . -type d -name include)
INC := -I $(INC_DIRS)

# $@ - target
# $^ dependencies
# $< first dependency

test:
	@echo 'SOURCES: "$(SOURCES)"'
	@echo 'OBJECTS: "$(OBJECTS)"'

# gcc -o <bin/outfile> <object.o> <object2.o> -L lib -l<lib1> -l<lib2>
$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

# g++ -g -I include -c -o <object.o> <infile.cpp>
# the -c flag compiles the cpp into object code (no linking).
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p `dirname $@`
	@echo $(INC_DIRS)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Phony target ensures clean target will always run regardless if there's a
# file named clean in the directory or not.
.PHONY: clean
