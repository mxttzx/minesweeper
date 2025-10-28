#include "../include/board.h"

void init_grid(Board *board)
{
    board->rows = ROWS;
    board->cols = COLS;
    board->total_mines = MINES;

    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            board->grid[i][j].is_mine = 0;
            board->grid[i][j].is_flag = 0;
            board->grid[i][j].is_seen = 0;
            board->grid[i][j].neig_mines = 0;
            board->grid[i][j].asset = IMAGE_COVERED; // Everything is covered by default
        }
    }
}

void calc_mines(Board *board) {
    // Can still be optimized, but good enough for now
    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLS; y++) {
            if (!board->grid[x][y].is_mine) continue;

            for (int dx = -1; dx <= 1; dx++){
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue;

                    int mrow = dx + x;
                    int mcol = dy + y;
                    if (mrow >= 0 && mrow < ROWS &&
                        mcol >= 0 && mcol < COLS) {
                        if (!board->grid[mrow][mcol].is_mine)
                            board->grid[mrow][mcol].neig_mines++; // For each mine, we increment its neighbors
                    };
                }
            }
        }
    }
}

void place_mines(Board *board)
{
    int placed_mines = 0;
    srand((unsigned) time(NULL)); // Initialize a random seed based on int time value

    while (placed_mines < board->total_mines) {
        int row_mine = rand() % board->rows;
        int col_mine = rand() % board->cols;

        if (!board->grid[row_mine][col_mine].is_mine) {
            board->grid[row_mine][col_mine].is_mine = 1;
            board->grid[row_mine][col_mine].asset = IMAGE_MINE;
            placed_mines++;
        }
    }
}
