# -----------------------------
# Project Settings
# -----------------------------

TARGET = game
BUILD_DIR = build
SRC_DIR = src

CXX = g++
CC = gcc

CXXFLAGS = -std=c++17 -Wall -Winvalid-pch -Winvalid-offsetof -MMD -MP
CXXFLAGS += -Iinclude
CXXFLAGS += -Ibuild
CXXFLAGS += -Iexternal/imgui
CXXFLAGS += -Iexternal/raylib/include
CXXFLAGS += -Iexternal/json

CFLAGS = -Wall -MMD -MP
CFLAGS += -Iinclude
CFLAGS += -Iexternal/raylib/include

LDFLAGS = -Lexternal/raylib/lib
LDLIBS = -lraylib -lgdi32 -lwinmm

# Debug flags
DEBUG_FLAGS = -g

# -----------------------------
# Source Files
# -----------------------------

SRC = $(shell find $(SRC_DIR) -name "*.cpp")
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

CSRC = $(shell find $(SRC_DIR) -name "*.c")
COBJ = $(CSRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# -----------------------------
# Build Rules
# -----------------------------

all: $(BUILD_DIR)/$(TARGET).exe

$(BUILD_DIR)/$(TARGET).exe: $(OBJ) $(COBJ)
	$(CXX) $(OBJ) $(COBJ) -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# -----------------------------
# Clean
# -----------------------------

clean:
	rm -rf $(BUILD_DIR)

# -----------------------------
# Run
# -----------------------------

run: all
	./$(BUILD_DIR)/$(TARGET).exe

-include $(OBJ:.o=.d) $(COBJ:.o=.d)