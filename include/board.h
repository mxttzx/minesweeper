#ifndef BOARD_H_
#define BOARD_H_

#define ROWS 9
#define COLS 9
#define MINES 10
#define MINE 1

#include <time.h>
#include <stdlib.h>

#define IMAGE_MINE "../assets/mine.bmp"
#define IMAGE_COVERED "../assets/covered.bmp"

typedef struct {
    char *asset;
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

void init_grid(Board *);
void place_mines(Board *);
void calc_mines(Board *);

#endif
