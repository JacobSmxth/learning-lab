# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -O2
LDFLAGS =

# Directories
SRC_DIR = src
OBJ_DIR = obj
OUT_DIR = bin

# Files
SRC = $(SRC_DIR)/main.c
OBJ = $(OBJ_DIR)/main.o
OUT = $(OUT_DIR)/task

# Dependency files
DEPS = $(OBJ:.o=.d)

# Default target
all: $(OUT)

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(OUT)

# Release build
release: CFLAGS += $(RELEASE_FLAGS)
release: $(OUT)

# Link object files to create executable
$(OUT): $(OBJ) | $(OUT_DIR)
	@$(CC) $(OBJ) $(LDFLAGS) -o $@
	@echo "Built $@"

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
	@echo "Compiled $<"

# Create directories if they don't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

# Include dependency files
-include $(DEPS)

# Run the program
run: $(OUT)
	@./$(OUT)

# Debug with GDB
gdb: debug
	@gdb --quiet --args $(OUT)

# Run Valgrind for memory checking
valgrind: debug
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(OUT)

# Static analysis with cppcheck
cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem $(SRC_DIR) --quiet

# Format code with clang-format
format:
	@clang-format -i $(SRC)
	@echo "Formatted source files"

# Edit source file
edit:
	@nvim $(SRC)

# Clean build artifacts
clean:
	@rm -rf $(OBJ_DIR) $(OUT_DIR)
	@echo "Cleaned build artifacts"

# Phony targets
.PHONY: all debug release run gdb valgrind cppcheck format edit clean
