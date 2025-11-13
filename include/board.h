#ifndef BOARD_H_
#define BOARD_H_

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define CELL_WIDTH 50
#define CELL_HEIGHT 50

typedef struct {
    int x, y;
    int w, h;
    int neig_mines;
    int is_mine;
    int is_flag;
    int is_seen;
} Cell;

typedef struct {
    Cell *grid;
    bool *peek_mask;
    bool *flag_mask;
    int total_mines;
    int rows;
    int cols;
} Board;


Board *init_board(int rows, int cols, int mines);
void free_board(Board *board);
void place_mines(Board *board, int x, int y);
void calc_mines(Board *board);

#endif
