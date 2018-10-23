TARGET_EXEC ?= wasp8.js
BUILD_DIR ?= src/web/build
SRC_DIRS ?= src/emulator

SRCS := $(shell find $(SRC_DIRS) -name *.c)
COMPILER := emcc

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

FLAGS ?= -s WASM=1 -O3

wasp8: $(SRCS)
	@echo "Building..." 
	$(COMPILER) $(SRC_DIRS)/main.c -o $(BUILD_DIR)/$(TARGET_EXEC) $(FLAGS)

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

debug: $(SRCS)
	@echo "Building Debug..."
	@echo "STUB"