#ifndef BOARD_H_
#define BOARD_H_

#define ROWS 9
#define COLS 9
#define MINES 10
#define MINE 1

#include <time.h>
#include "cell.h"
#include "../utils/load_asset.h"

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
