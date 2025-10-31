#ifndef BOARD_H_
#define BOARD_H_

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ROWS 9
#define COLS 9
#define MINES 10
#define MINE 1

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
    Cell grid[ROWS][COLS];
    int total_mines;
    int rows;
    int cols;
} Board;

void init_grid(Board *board);
void place_mines(Board *board, int x, int y);
void calc_mines(Board *board);

#endif
