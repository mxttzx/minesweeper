# https://stackoverflow.com/a/79685650
CC = gcc
COMMON = -Wall -Wextra -g
CFLAGS = `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

SRC_DIR = src
OBJ_DIR = obj
OUT = minesweeper

SRC := $(shell find $(SRC_DIR) -type f -name '*.c') main.c
OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) $(COMMON) $(LDFLAGS) -o $(OUT)
	@echo "Compiled minesweeper successfully."

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(OUT)
