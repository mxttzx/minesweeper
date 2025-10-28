#include "../include/game.h"

Board* new_board() {
    Board *board = malloc(sizeof(Board));

    if (!board) {
        perror("Failed to initialize empty board");
        exit(1);
    }

    return board;
}

void new_game(GameState *gs, Board *board) {
    init_grid(board);
    place_mines(board);
    calc_mines(board);
}

void update_game(GameState *gs, InputState *input, Board *board) {

}

void render_cell(GameState *gs, Assets *assets, Cell *cell) {
    SDL_Texture *text = NULL;

    if (cell->is_flag) text = assets->flagged;
    else if (cell->is_mine) text = assets->mine;
    else if (!cell->is_seen) text = assets->covered;
    else text = assets->numbers[cell->neig_mines];

    SDL_Rect dest = { cell->x * 50, cell->y * 50, 50, 50 };
    SDL_RenderCopy(gs->renderer, text, NULL, &dest);
}

void render_game(GameState *gs, Board *board, Assets *assets) {
    SDL_RenderClear(gs->renderer);
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            render_cell(gs, assets, &board->grid[i][j]);
        }
    }
    SDL_RenderPresent(gs->renderer);
}
