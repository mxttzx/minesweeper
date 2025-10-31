CC = gcc
CFLAGS = -Wall -Wextra -g `sdl2-config --cflags` -I include
LDFLAGS = `sdl2-config --libs`

SRC_DIR = src
OBJ_DIR = obj
OUT = minesweeper

SRC := $(shell find $(SRC_DIR) -type f -name '*.c' -print) main.c

OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

vpath %.c . $(SRC_DIR) $(shell find $(SRC_DIR) -type d -printf "%p ")

.PHONY: all clean
all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(OUT)
	@echo "Compiled minesweeper successfully."

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(OUT)
