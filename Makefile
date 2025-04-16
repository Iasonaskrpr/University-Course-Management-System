# Compiler
CXX = g++

# Compile options
CXXFLAGS = -Wall -Werror -g -std=c++17

# Source files
SRCS = main.cpp file1.cpp

# Object files (auto-generate from SRCS)
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = main

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile individual .cpp files to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Run with valgrind
valgrind: $(TARGET)
	valgrind ./$(TARGET)

# Clean object files and binary
clean:
	rm -f $(OBJS) $(TARGET)

# Release build without debug symbols
release: CXXFLAGS := -O2 -Wall -std=c++17
release: clean all

.PHONY: all run valgrind clean release
