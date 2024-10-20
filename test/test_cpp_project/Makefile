# Variables
CXX := g++
CXXFLAGS := -I/usr/local/include/artic -Wall -Wextra -O2 $(shell pkg-config --cflags sfml-all)
LDFLAGS := -L/usr/local/lib -lartic $(shell pkg-config --libs sfml-all)


# Default target
all: main

# Build the test executable
main: main.o
	$(CXX) -o $@ $^ $(LDFLAGS)
	@echo "C++ test project built successfully."

# Compile the main.cpp file
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f main main.o
	@echo "Cleaned C++ test project."

.PHONY: all clean
