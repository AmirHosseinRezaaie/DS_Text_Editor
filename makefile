# ============================================
# Makefile for Text Editor Project
# Two versions: string-based and vector-based
# ============================================

# ----- Compiler Settings -----
CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -g -O2 -I./include
LDFLAGS = 

# ----- Directory Structure -----
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include

# ----- Version 1: String-based implementation -----
STRING_SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/trie.cpp
STRING_OBJECTS = $(STRING_SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
STRING_EXEC = $(BIN_DIR)/string.exe

# ----- Version 2: Vector-based implementation -----
VECTOR_SOURCES = $(SRC_DIR)/vector.cpp $(SRC_DIR)/trie.cpp
VECTOR_OBJECTS = $(VECTOR_SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
VECTOR_EXEC = $(BIN_DIR)/vector.exe

# ----- All executables -----
EXECUTABLES = $(STRING_EXEC) $(VECTOR_EXEC)

# ----- Default: build both versions -----
all: $(EXECUTABLES)

# ----- Build string version -----
$(STRING_EXEC): $(STRING_OBJECTS) | $(BIN_DIR)
	@echo "[LINK] Building string version..."
	$(CC) $(STRING_OBJECTS) $(LDFLAGS) -o $@
	@echo "[SUCCESS] String version: $(STRING_EXEC)"

# ----- Build vector version -----
$(VECTOR_EXEC): $(VECTOR_OBJECTS) | $(BIN_DIR)
	@echo "[LINK] Building vector version..."
	$(CC) $(VECTOR_OBJECTS) $(LDFLAGS) -o $@
	@echo "[SUCCESS] Vector version: $(VECTOR_EXEC)"

# ----- Compile .cpp files to .o files -----
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "[COMPILE] $(notdir $<)"
	$(CC) $(CFLAGS) -c $< -o $@

# ----- Create directories -----
$(BUILD_DIR):
	@echo "[MKDIR] Creating $(BUILD_DIR)"
	@mkdir -p $@

$(BIN_DIR):
	@echo "[MKDIR] Creating $(BIN_DIR)"
	@mkdir -p $@

# ----- Helper Targets -----

# Clean build files
clean:
	@echo "[CLEAN] Cleaning build files..."
	@if exist "$(BUILD_DIR)" del /Q "$(BUILD_DIR)\*.o" 2>nul
	@if exist "$(BIN_DIR)" del /Q "$(BIN_DIR)\*.exe" 2>nul
	@echo "[SUCCESS] Cleanup completed"

# Clean everything
clean-all:
	@echo "[CLEAN] Removing all build directories..."
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
	@if exist "$(BIN_DIR)" rmdir /S /Q "$(BIN_DIR)"
	@echo "[SUCCESS] Full cleanup completed"

# Run string version
run-string: $(STRING_EXEC)
	@echo "[RUN] Running string version..."
	@echo "========================================"
	$(STRING_EXEC)

# Run vector version  
run-vector: $(VECTOR_EXEC)
	@echo "[RUN] Running vector version..."
	@echo "========================================"
	$(VECTOR_EXEC)

# Run both versions
run: run-string run-vector

# Quick build and run string
quick-string: $(STRING_EXEC)
	$(STRING_EXEC)

# Quick build and run vector
quick-vector: $(VECTOR_EXEC)
	$(VECTOR_EXEC)

# Build only string version
build-string: $(STRING_EXEC)

# Build only vector version
build-vector: $(VECTOR_EXEC)

# Show help
help:
	@echo "[HELP] Available commands:"
	@echo ""
	@echo "Build commands:"
	@echo "  make                    - Build both versions (default)"
	@echo "  make build-string       - Build only string version"
	@echo "  make build-vector       - Build only vector version"
	@echo ""
	@echo "Run commands:"
	@echo "  make run-string         - Build and run string version"
	@echo "  make run-vector         - Build and run vector version"
	@echo "  make run                - Build and run both versions"
	@echo ""
	@echo "Quick run:"
	@echo "  make quick-string       - Quick run string version"
	@echo "  make quick-vector       - Quick run vector version"
	@echo ""
	@echo "Cleanup:"
	@echo "  make clean              - Clean object files and executables"
	@echo "  make clean-all          - Remove build directories"
	@echo ""
	@echo "Information:"
	@echo "  make help               - Show this help"
	@echo "  make info               - Show project info"
	@echo ""
	@echo "Executables will be created in: $(BIN_DIR)/"
	@echo "  - $(STRING_EXEC)"
	@echo "  - $(VECTOR_EXEC)"
	# Show project information
info:
	@echo "[INFO] Project Information:"
	@echo "  String version sources:"
	@for src in $(STRING_SOURCES); do echo "    - $$(basename $$src)"; done
	@echo "  Vector version sources:"
	@for src in $(VECTOR_SOURCES); do echo "    - $$(basename $$src)"; done
	@echo "  Common file: trie.cpp"
	@echo "  Header file: include/trie.h"
	@echo "  Build directory: $(BUILD_DIR)"
	@echo "  Output directory: $(BIN_DIR)"

# Phony targets
.PHONY: all clean clean-all run run-string run-vector quick-string quick-vector build-string build-vector help info

# Default goal
.DEFAULT_GOAL := help