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
LIB := -pthread -L lib -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt
INC := -I include

test:
	@echo 'SOURCES: "$(SOURCES)"'
	@echo 'OBJECTS: "$(OBJECTS)"'

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	# $@ and $^ are the target and dependencies, respectively.
	# gcc -o <bin/outfile> <object.o> <object2.o> -L lib -l<lib1> -l<lib2>
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	# $@ and $< are the target and the first dependency, respectively.
	# g++ -g -I include -c -o <object.o> <infile.cpp>
	# the -c flag compiles the cpp into object code (no linking).
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
