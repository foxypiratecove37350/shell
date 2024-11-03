CC ?= gcc
CFLAGS := -Wall -g

SRC_DIR := src/
OBJ_DIR := obj/
BIN_DIR := bin/

SRC_FILES := $(wildcard $(SRC_DIR)*.c)
HDR_FILES := $(wildcard $(SRC_DIR)*.h)
OBJ_FILES := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%$(SUFFIX).o,$(SRC_FILES))

SUFFIX ?= 

BIN_NAME := shell

ifeq ($(OS),Windows_NT)
	BIN_NAME := $(BIN_NAME).exe
	SUFFIX := _win
endif

ifneq ($(SUFFIX),_win)
	BIN_NAME := $(BIN_NAME)$(SUFFIX)
endif

.PHONY: all clean run

all: $(BIN_DIR)$(BIN_NAME)

$(BIN_DIR)$(BIN_NAME): $(OBJ_FILES)
	@if [ ! -d $(BIN_DIR) ]; then mkdir -p $(BIN_DIR); fi
	$(CC) $(CFLAGS) -o $@ $^ $(CXX_SUFFIX_FLAGS)

$(OBJ_DIR)%$(SUFFIX).o: $(SRC_DIR)%.c $(SRC_FILES) $(HDR_FILES)
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi
	$(CC) $(CFLAGS) -c -o $@ $< $(CXX_SUFFIX_FLAGS)

clean:
	rm -f $(OBJ_DIR)* $(BIN_DIR)*

run: all
	@echo -n "Args: "
	@read args; \
	$(BIN_DIR)$(BIN_NAME) $$args

