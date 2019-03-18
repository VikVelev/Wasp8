RECOMP_TARGET_EXEC ?= wasp8.recompiler.run
STD_TARGET_EXEC ?= wasp8.run



RECOMP_BUILD_DIR ?= src/recompiler/build
STD_BUILD_DIR ?= src/interpreter/build

SRC_DIRS ?= src/interpreter
SRC_RECOMP_DIRS ?= src/recompiler

SRCS := $(shell find $(SRC_DIRS) -name *.c)
SRCS_RECOMP := $(shell find $(SRC_RECOMP_DIRS) -name *.c)

RECOMP_COMPILER := clang
STD_COMPILER := gcc

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

STD_FLAGS ?= -MMD -MP -lm -lpthread `pkg-config --libs --cflags sdl2` -O3
RECOMP_FLAGS ?= -MMD -MP -lm -lpthread `pkg-config --libs --cflags sdl2` -O3

DEBUG_FLAGS = -g

interpreter: $(SRCS)
	@echo "Building standalone version."
	$(STD_COMPILER) $(SRC_DIRS)/main.c -o $(STD_BUILD_DIR)/$(STD_TARGET_EXEC) $(STD_FLAGS) $(DEBUG_FLAGS)
	@echo "Done"

recompiler: $(SRCS_RECOMP)
	@echo "Building a dynamic recompiler."
	$(RECOMP_COMPILER) $(SRC_RECOMP_DIRS)/main.c -o $(RECOMP_BUILD_DIR)/$(RECOMP_TARGET_EXEC) $(RECOMP_FLAGS) $(DEBUG_FLAGS)
	@echo "Done"

.PHONY: clean

clean:
	$(RM) -r $(STD_BUILD_DIR)
	$(RM) -r $(RECOMP_BUILD_DIR)
	

debug: $(SRCS)
	@echo "Building Debug..."
	@echo "STUB"