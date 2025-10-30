#include "../include/game.h"

Board* new_board() {
    Board *board = malloc(sizeof(Board));

    if (!board) {
        fprintf(stderr, "new_board: failed to initialize empty board");
        exit(1);
    }

    return board;
}

void new_game(GameState *gs, Board *board) {
    init_grid(board);
    place_mines(board);
    calc_mines(board);
    gs->game_over = 0;
}

void update_game(GameState *gs, InputState *input, Board *board) {
    if (input->keys[SDLK_g]) {
        new_game(gs, board);
        input->keys[SDLK_g] = 0;
        return;
    }
    if (input->keys[SDLK_x]) {
        gs->should_continue = 0;
        gs->game_over = 1;
        return;
    }

    int row = input->mouse_y / CELL_HEIGHT;
    int col = input->mouse_x / CELL_WIDTH;

    if (input->keys[SDLK_f]) {
        flag_single(board, row, col);
        input->keys[SDLK_f] = 0;
        return;
    }

    if (input->mouse_input) {
        reveal_single(gs, board, row, col);
        return;
    }
}

void reveal_board(Board *board) {
    for (int i = 0; i < board->rows * board->cols; i++) {
        ((Cell *)board->grid)[i].is_seen = 1;
        ((Cell *)board->grid)[i].is_flag = 0;
    }
}

void flag_single(Board *board, int row, int col) {
    Cell *cell = &board->grid[row][col];
    if (cell->is_seen) return;
    cell->is_flag = !cell->is_flag;
}

void reveal_single(GameState *gs, Board *board, int row, int col) {
    if (row < 0 || row >= board->rows ||
        col < 0 || col >= board->cols)
        return;

    Cell *cell = &board->grid[row][col];

    if (cell->is_seen || cell->is_flag) return;

    if (cell->is_mine) {
        reveal_board(board);
        gs->game_over = 1;
        return;
    }

    cell->is_seen = 1;

    if (cell->neig_mines > 0) return;

    if (cell->neig_mines == 0)
        for (int dx = -1; dx <= 1; dx++)
            for (int dy = -1; dy <= 1; dy++)
                reveal_single(gs, board, row + dx, col + dy);
}

void render_cell(GameState *gs, Assets *assets, Cell *cell) {
    SDL_Texture *text = NULL;

    if (cell->is_flag) text = assets->flagged;
    else if (!cell->is_seen) text = assets->covered;
    else if (cell->is_mine) text = assets->mine;
    else text = assets->numbers[cell->neig_mines];

    SDL_Rect dest = {
        cell->x * CELL_WIDTH,
        cell->y * CELL_HEIGHT,
        CELL_WIDTH,
        CELL_HEIGHT
    };

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
