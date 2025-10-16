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

void place_mines(Board *board)
{
    int placed_mines = 0;
    srand((unsigned) time(NULL)); // Initialize a random seed based on int time value

    while (placed_mines < board->total_mines) {
        int row_mine = rand() % board->rows;
        int col_mine = rand() % board->cols;

        if (!board->grid[row_mine][col_mine].is_mine) {
            board->grid[row_mine][col_mine].is_mine = 1;
            placed_mines++;
        }
    }
}
