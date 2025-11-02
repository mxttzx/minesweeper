#include "../include/save.h"


// https://stackoverflow.com/a/9840678
Board *load_game(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "load_game: failed to read file to load game\n");
        exit(1);
    }

    int rows, cols, mines;
    fread(&rows, sizeof(int), 1, file);
    fread(&cols, sizeof(int), 1, file);
    fread(&mines, sizeof(int), 1, file);

    Board *board = init_board(rows, cols, mines);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fread(&board->grid[i][j].neig_mines, sizeof(int), 1, file);
            fread(&board->grid[i][j].is_mine, sizeof(int), 1, file);
            fread(&board->grid[i][j].is_flag, sizeof(int), 1, file);
            fread(&board->grid[i][j].is_seen, sizeof(int), 1, file);
        }
    }

    for (int i = 0; i < rows; i++) {
        fread(board->mask[i], sizeof(bool), cols, file);
    }

    fclose(file);
    return board;
}

void save_game(Board *board, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "save_game: failed to open file to save game\n");
        exit(1);
    }

    fwrite(&board->rows, sizeof(int), 1, file);
    fwrite(&board->cols, sizeof(int), 1, file);
    fwrite(&board->total_mines, sizeof(int), 1, file);

    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            fwrite(&board->grid[i][j].neig_mines, sizeof(int), 1, file);
            fwrite(&board->grid[i][j].is_mine, sizeof(int), 1, file);
            fwrite(&board->grid[i][j].is_flag, sizeof(int), 1, file);
            fwrite(&board->grid[i][j].is_seen, sizeof(int), 1, file);
        }
    }

    for (int i = 0; i < board->rows; i++) {
        fwrite(board->mask[i], sizeof(bool), board->cols, file);
    }

    fclose(file);
}
