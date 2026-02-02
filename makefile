TARGET = text-editor

CC = g++

CFLAGS = -Wall -Wextra -std=c++17 -g

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

EXEC = $(BIN_DIR)/$(TARGET)

all: $(EXEC)

$(EXEC): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

run: all
	./$(EXEC)

help:
	@echo "دستورات موجود:"
	@echo "  make          → بیلد پروژه"
	@echo "  make run      → بیلد + اجرا"
	@echo "  make clean    → پاک کردن فایل‌های ساخته‌شده"
	@echo "  make help     → این پیام"

.PHONY: all clean run help

clean:
ifeq ($(OS),Windows_NT)
	@if exist "$(BUILD_DIR)" ( \
		del /Q "$(BUILD_DIR)\*.o" "$(BUILD_DIR)\*.obj" 2>nul \
	)
	@if exist "$(BIN_DIR)" ( \
		del /Q "$(BIN_DIR)\*.exe" "$(BIN_DIR)\$(TARGET)" "$(BIN_DIR)\$(TARGET).exe" 2>nul \
	)
else
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.obj
	rm -f $(BIN_DIR)/$(TARGET) $(BIN_DIR)/$(TARGET).exe
endif