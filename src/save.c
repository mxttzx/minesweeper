#include "../include/save.h"

Board *load_game(GameState *gs, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "load_game: failed to read last save file\n");
        exit(EXIT_FAILURE);
    }

    char line[128];
    int rows, cols, mines;

    // Read game state
    if (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d %d %d", &gs->game_over, &gs->first_move, &gs->should_continue);
    }

    // Read board domensions
    if (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d %d %d", &rows, &cols, &mines);
    }

    Board *board = init_board(rows, cols, mines);

    for (int i = 0; i < board->rows * board->cols; i++) {
        int row = i / board->cols;
        int col = i % board->cols;

        char ch;
        if (fscanf(file, " %c", &ch) == EOF) {
            fprintf(stderr, "load_game: encountered unexpected EOF when loading last save file: (%d,%d)\n", row, col);
            exit(EXIT_FAILURE);
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
                exit(EXIT_FAILURE);
        }
    }

    calc_mines(board);
    fclose(file);

    return board;
}

void save_game(GameState *gs, Board *board, const char *filename) {
    FILE *file = fopen(filename, "wb+");
    if (!file) {
        fprintf(stderr, "load_game: failed to read last save file\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d %d %d\n", gs->game_over, gs->first_move, gs->should_continue);
    fprintf(file, "%d %d %d\n", board->rows, board->cols, board->mines);

    for (int i = 0; i < board->rows * board->cols; i++) {
        Cell *cell = &board->grid[i];
        char ch;

        if (cell->is_flag && cell->is_mine) ch = 'X';
        else if (cell->is_flag) ch = 'F';
        else if (cell->is_mine) ch = 'M';
        else if (cell->is_seen) ch = '+';
        else ch = '.';

        fputc(ch, file);

        if ((i + 1) % board->cols == 0) fputc('\n', file);
    }
    fclose(file);
}
