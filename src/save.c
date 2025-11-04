#include "../include/save.h"

 Board *load_game(GameState *gs, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "load_game: failed to read last save file\n");
        exit(1);
    }

    int rows, cols, mines;
    fscanf(file, "%d %d %d", &rows, &cols, &mines); // Read dimension header

    Board *board = init_board(rows, cols, mines);

    for (int i = 0; i < board->rows * board->cols; i++) {
        int row = i / board->cols;
        int col = i % board->cols;

        char ch;
        if (fscanf(file, " %c", &ch) == EOF) {
            fprintf(stderr, "load_game: encountered unexpected EOF when loading last save file: (%d,%d)\n", row, col);
            exit(1);
        }

        Cell *cell = &board->grid[i];
        switch (ch) {
            case 'M': cell->is_mine = 1; break;
            case '.': cell->is_seen = 0; break;
            case '+': cell->is_seen = 1; break;
            case 'F': cell->is_flag = 1; break;
            case 'X':
                cell->is_mine = 1;
                cell->is_flag = 1;
                break;
            default:
                fprintf(stderr, "load_game: encountered unexpected char when loading last save file: (%d, %d)\n", row, col);
                exit(1);
        }
    }

    gs->should_continue = 1;
    gs->first_move = 0;
    gs->game_over = 0;
    gs->peek = 0;

    calc_mines(board);

    fclose(file);

    return board;
}

void save_game(GameState *gs, Board *board, const char *filename) {
    FILE *file = fopen(filename, "wb+");
    if (!file) {
        fprintf(stderr, "load_game: failed to read last save file\n");
        exit(1);
    }

    fprintf(file, "%d %d %d\n", board->rows, board->cols, board->total_mines);

    for (int i = 0; i < board->rows * board->cols; i++) {
        int row = i / board->cols;
        int col = i % board->cols;

        Cell *cell = &board->grid[i];
        char ch;

        if (cell->is_flag && cell->is_mine) ch = 'X';
        else if (cell->is_flag) ch = 'F';
        else if (cell->is_mine) ch = 'M';
        else if (cell->is_seen) ch = '+';
        else ch = '.';

        fputc(ch, file);

        if (row == board->rows) fputc('\n', file);
    }
    fclose(file);
}
