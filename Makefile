# Compiler settings
CC = g++
CFLAGS = -Wall -std=c++17 -g 
LIBS = -lSDL2 -lSDL2_image

# Directories
SRC_DIR = src
BIN_DIR = bin

# Executable name
EXEC_NAME = main

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Binary name
TARGET = $(BIN_DIR)/$(EXEC_NAME)

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(BIN_DIR)/*