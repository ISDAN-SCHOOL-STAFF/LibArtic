# Variables
CC := gcc
CFLAGS := -I/usr/local/include/artic -Wall -Wextra -O2
LDFLAGS := -L/usr/local/lib -lartic

# Default target
all: main

# Build the test executable
main: main.o
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "C test project built successfully."

# Compile the main.c file
main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f main main.o
	@echo "Cleaned C test project."

.PHONY: all clean
