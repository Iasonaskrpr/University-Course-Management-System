# Compiler
CXX = g++

# Compile options
CXXFLAGS = -Wall -Werror -g -std=c++17 -ISource

# Source files
SRCS = Main/main.cpp Source/file1.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = main

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile .cpp to .o
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
release: CXXFLAGS := -O2 -Wall -std=c++17 -ISource
release: clean all

.PHONY: all run valgrind clean release
