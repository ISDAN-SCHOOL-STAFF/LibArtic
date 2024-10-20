# Variables
CXX := g++
CXXFLAGS := -Iinclude -I/usr/local/include/artic -Wall -Wextra -O2
LDFLAGS := -L/usr/local/lib -lartic

SRCDIR := src
INCLUDEDIR := include
BUILDDIR := build
BINDIR := bin
TARGET := $(BINDIR)/main

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Build successful: $(TARGET)"

# Compile source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
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
