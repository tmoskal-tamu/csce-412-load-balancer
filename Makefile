# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Executable name
TARGET = load_balancer_simulation

# Source files
SRC = main.cpp LoadBalancer.cpp WebServer.cpp Request.cpp RequestQueue.cpp

# Default rule to build the program
all: $(TARGET)

# Rule to compile all source files and link into an executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Rule to clean up the compiled files
clean:
	rm -f $(TARGET)
