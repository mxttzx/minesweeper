#include "../include/board.h"

void init_grid(Board *board)
{
    board->rows = ROWS;
    board->cols = COLS;
    board->total_mines = MINES;

    memset(board->grid, 0, sizeof(board->grid));

    int i, j;
    for (i = 0; i < board->rows; i++) {
        for (j = 0; j < board->cols; j++) {
            board->grid[i][j].x = j;
            board->grid[i][j].y = i;
        }
    }
}

void calc_mines(Board *board) {
    // Can still be optimized, but good enough for now
    for (int x = 0; x < board->rows; x++) {
        for (int y = 0; y < board->cols; y++) {
            if (!board->grid[x][y].is_mine) continue;

            for (int dx = -1; dx <= 1; dx++){
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue;

                    int mrow = dx + x;
                    int mcol = dy + y;
                    if (mrow >= 0 && mrow < board->rows &&
                        mcol >= 0 && mcol < board->cols) {
                        if (!board->grid[mrow][mcol].is_mine)
                            board->grid[mrow][mcol].neig_mines++; // For each mine, we increment its neighbors
                    }
                }
            }
        }
    }
}

void place_mines(Board *board, int safe_x, int safe_y)
{
    if (board->total_mines <= 0) return;
    if (board->total_mines >= board->rows * board->cols){
        fprintf(stderr, "place_mines: invalid total mines (%d) > grid cells (%d)\n",
            board->total_mines, board->rows * board->cols);
        exit(1);
    }

    int placed_mines = 0;
    while (placed_mines < board->total_mines) {
        int row_mine = rand() % board->rows;
        int col_mine = rand() % board->cols;

        if (abs(row_mine - safe_x) <= 1 && abs(col_mine - safe_y) <= 1)
            continue;

        if (!board->grid[row_mine][col_mine].is_mine) {
            board->grid[row_mine][col_mine].is_mine = 1;
            placed_mines++;
        }
    }
}
