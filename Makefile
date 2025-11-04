CC = gcc
CFLAGS = -Wall -Wextra -g `sdl2-config --cflags` -I include
LDFLAGS = `sdl2-config --libs`

SRC_DIR = src
OBJ_DIR = obj
OUT = minesweeper

SRC := $(shell find $(SRC_DIR) -type f -name '*.c') main.c
OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

.PHONY: all clean

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(OUT)
	@echo "Compiled minesweeper successfully."

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(OUT)
