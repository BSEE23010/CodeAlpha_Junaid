# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17

# Target executable name
TARGET = r.out

# Source file
SRC = main.cpp

# Default target to build and run the program
run: $(TARGET)
	./$(TARGET)

# Compile target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean target to remove the compiled executable
clean:
	rm -f $(TARGET)
