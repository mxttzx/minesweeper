#include "board.h"

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

void calc_mines(Board *board, Cell *cell) {
    int count = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            int mrow = i + cell->x;
            int mcol = j + cell->y;
            if (mrow >= 0 && mrow < ROWS &&
                mcol >= 0 && mcol < COLS) {
                if (board->grid[mrow][mcol].is_mine) count++;
            }
        }
    }
    cell->neig_mines = count;
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
