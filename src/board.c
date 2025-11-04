#include "../include/board.h"

Board *init_board(int rows, int cols, int mines) {
    Board *board = malloc(sizeof(Board));
    if (!board) {
        fprintf(stderr, "new_board: failed to initialize empty board");
        exit(1);
    }

    board->rows = rows;
    board->cols = cols;
    board->total_mines = mines;

    board->grid = calloc(rows * cols, sizeof(Cell));
    if (!board->grid) {
        fprintf(stderr, "new_board: failed to initialize empty grid");
        exit(1);
    }

    board->peek_mask = calloc(rows * cols, sizeof(bool));
    if (!board->peek_mask) {
        fprintf(stderr, "new_board: failed to initialize empty peek mask");
        exit(1);
    }

    board->flag_mask = calloc(rows * cols, sizeof(bool));
    if (!board->flag_mask) {
        fprintf(stderr, "new_board: failed to initialize empty flag mask");
        exit(1);
    }

    for (int i = 0; i < board->rows * board->cols; i++) {
        int row = i / board->cols;
        int col = i % board->cols;

        board->grid[i].y = row;
        board->grid[i].x = col;
    }

    return board;
}

void free_board(Board *board) {
    free(board->grid);
    free(board);
}

void calc_mines(Board *board) {
    for (int i = 0; i < board->rows * board->cols; i++) {
        if (!board->grid[i].is_mine) continue;

        int x = i / board->cols;
        int y = i % board->cols;

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;

                int mrow = dx + x;
                int mcol = dy + y;
                int idx = mrow * board->cols + mcol;

                if (mrow >= 0 && mrow < board->rows &&
                    mcol >= 0 && mcol < board->cols &&
                    !board->grid[idx].is_mine) {
                        board->grid[idx].neig_mines++;
                }
            }
        }
    }
}

void place_mines(Board *board, int sx, int sy) {
    if (board->total_mines <= 0) return;
    if (board->total_mines >= board->rows * board->cols){
        fprintf(stderr, "place_mines: invalid total mines (%d) >= grid cells (%d)\n",
            board->total_mines, board->rows * board->cols);
        exit(1);
    }

    int placed = 0;
    while (placed < board->total_mines) {
        int mrow = rand() % board->rows;
        int mcol = rand() % board->cols;
        int idx = mrow * board->cols + mcol;

        if (abs(mrow - sx) <= 1 && abs(mcol - sy) <= 1)
            continue;

        if (!board->grid[idx].is_mine) {
            board->grid[idx].is_mine = 1;
            placed++;
        }
    }
}
