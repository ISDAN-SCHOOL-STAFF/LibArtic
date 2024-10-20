# Variables
CC := gcc
CXX := g++
AR := ar
ARFLAGS := rcs
CFLAGS := -Iinclude -Wall -Wextra -O2 $(shell pkg-config --cflags sfml-all)
CXXFLAGS := -Iinclude -Wall -Wextra -O2 $(shell pkg-config --cflags sfml-all)
LDFLAGS := $(shell pkg-config --libs sfml-all)

SRCDIR := src
BUILDDIR := build
INCLUDEDIR := include
LIBDIR := /usr/local/lib
INCDIR := /usr/local/include

SOURCES_C := $(shell find $(SRCDIR) -name '*.c')
SOURCES_CPP := $(shell find $(SRCDIR) -name '*.cpp' -o -name '*.cc' -o -name '*.cxx' -o -name '*.c++')
OBJECTS_C := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES_C))
OBJECTS_CPP := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES_CPP))
OBJECTS := $(OBJECTS_C) $(OBJECTS_CPP)
LIB := libartic.a

# Find test directories that contain a Makefile
TEST_DIRS := $(shell find test -mindepth 1 -maxdepth 1 -type d -exec test -e {}/Makefile \; -print)

# Default target
all: $(LIB)

# Build the static library
$(LIB): $(OBJECTS)
	@echo "Creating static library $(LIB)..."
	$(AR) $(ARFLAGS) $@ $(OBJECTS)
	@echo "Library $(LIB) created successfully."

# Compile C source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@echo "Cleaning build directories..."
	rm -rf $(BUILDDIR) $(LIB)
	@echo "Clean completed."

# Install the library and headers, and run tests
install: all
	@echo "Checking and installing dependencies..."
	./install_deps.sh
	@echo "Installing $(LIB) to $(LIBDIR)..."
	sudo install -d $(LIBDIR)
	sudo install -m 644 $(LIB) $(LIBDIR)
	@echo "Installing headers to $(INCDIR)/artic..."
	sudo install -d $(INCDIR)/artic
	sudo cp -r $(INCLUDEDIR)/* $(INCDIR)/artic/
	@echo "Running tests..."
	@set -e; \
	for dir in $(TEST_DIRS); do \
		echo "Running tests in $$dir..."; \
		$(MAKE) -C $$dir; \
	done
	@echo "Tests completed. Cleaning up test directories..."
	@set -e; \
	for dir in $(TEST_DIRS); do \
		echo "Cleaning $$dir..."; \
		$(MAKE) -C $$dir clean; \
	done
	@echo "LibArtic installed successfully."

# Uninstall the library and headers
uninstall:
	@echo "Uninstalling LibArtic..."
	sudo rm -f $(LIBDIR)/$(LIB)
	sudo rm -rf $(INCDIR)/artic
	@echo "Uninstall completed."

.PHONY: all clean install uninstall
