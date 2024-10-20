# Variables
CC := gcc
CFLAGS := -Iinclude -I/usr/local/include/artic -Wall -Wextra -O2
LDFLAGS := -L/usr/local/lib -lartic

SRCDIR := src
INCLUDEDIR := include
BUILDDIR := build
BINDIR := bin
TARGET := $(BINDIR)/main

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Build successful: $(TARGET)"

# Compile source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

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
