TARGET_EXEC ?= wasp8.js
STD_TARGET_EXEC ?= wasp8.run

BUILD_DIR ?= src/web/build
STD_BUILD_DIR ?= src/emulator/build

SRC_DIRS ?= src/emulator

SRCS := $(shell find $(SRC_DIRS) -name *.c)

COMPILER := emcc
STD_COMPILER := gcc

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

FLAGS ?= -s WASM=1 -O3
STD_FLAGS ?= -MMD -MP -lm `pkg-config --libs --cflags sdl`

standalone: $(SRCS)
	@echo "Building standalone version."
	@web=0
	$(STD_COMPILER) $(SRC_DIRS)/main.c -o $(STD_BUILD_DIR)/$(STD_TARGET_EXEC) $(STD_FLAGS) -g

wasp8: $(SRCS)
	@echo "Building WASM module..." 
	@web=1
	$(COMPILER) $(SRC_DIRS)/main.c -o $(BUILD_DIR)/$(TARGET_EXEC) $(FLAGS)

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

debug: $(SRCS)
	@echo "Building Debug..."
	@echo "STUB"