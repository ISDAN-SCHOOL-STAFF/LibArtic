# Variables
CC := gcc
CXX := g++
CFLAGS := -Iinclude -I/usr/local/include/artic -Wall -Wextra -O2
CXXFLAGS := -Iinclude -I/usr/local/include/artic -Wall -Wextra -O2
LDFLAGS := -L/usr/local/lib -lartic -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR := src
INCLUDEDIR := include
BUILDDIR := build
BINDIR := bin
TARGET := $(BINDIR)/main

SOURCES_C := $(wildcard $(SRCDIR)/*.c)
SOURCES_CPP := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS_C := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES_C))
OBJECTS_CPP := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES_CPP))
OBJECTS := $(OBJECTS_C) $(OBJECTS_CPP)

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Build successful: $(TARGET)"

# Compile C source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ source files (if any)
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -rf $(BUILDDIR)
	@echo "Cleaned object files."

# Clean object files and binaries
fclean: clean
	rm -rf $(BINDIR)
	@echo "Cleaned binaries."

# Rebuild the project
re: fclean all

.PHONY: all clean fclean re
