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
    if (input->keys[SDLK_g]) {
        new_game(gs, board);
    }

    if (input->keys[SDLK_p]) {
        gs->should_continue = 0;
    }

    if (input->keys[SDLK_x]) {
        gs->should_continue = 0;
        gs->game_over = 1;
    }

    if (input->mouse_input) {
        handle_click(gs, board, input->mouse_x, input->mouse_y);
    }
}

void handle_click(GameState *gs, Board *board, int mouse_x, int mouse_y) {
    int row = mouse_y / CELL_HEIGHT;
    int col = mouse_x / CELL_WIDTH;

    if (row >= 0 && row <= board->rows &&
        col >= 0 && col <= board->cols) {
        Cell *cell = &board->grid[row][col];

        if (!cell->is_seen)
            cell->is_seen = 1;

        if (cell->is_mine)
            gs->game_over = 1;
    }
}

void render_cell(GameState *gs, Assets *assets, Cell *cell) {
    SDL_Texture *text = NULL;

    if (!cell->is_seen) text = assets->covered;
    else if (!cell->is_flag) text = assets->flagged;
    else if (cell->is_mine) text = assets->mine;
    else text = assets->numbers[cell->neig_mines];

    SDL_Rect dest = {
        cell->x * CELL_WIDTH,
        cell->y * CELL_HEIGHT,
        CELL_WIDTH, CELL_HEIGHT};
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
