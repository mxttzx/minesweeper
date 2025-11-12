#include "../include/game.h"

Board *new_game(GameState *gs, int rows, int cols, int mines) {
    Board *board = init_board(rows, cols, mines);
    gs->should_continue = 1;
    gs->first_move = 1;
    gs->game_over = 0;
    gs->peek = 0;

    return board;
}

void update_game(GameState *gs, Board *board, InputState *input) {
    int row = input->mouse_y / CELL_HEIGHT;
    int col = input->mouse_x / CELL_WIDTH;

    if (input->keys[SDL_BUTTON_RIGHT]) {
        toggle_flag(board, row, col);
    }

    if (input->keys[SDL_BUTTON_LEFT]) {
        reveal_single(gs, board, row, col);
    }

    if (input->keys[SDLK_s]) {
        save_game(gs, board, DEFAULT_FILE);
        printf("Saving game to %s\n", DEFAULT_FILE);
    }

    if (input->keys[SDLK_p]) {
        reveal_mines(board);
    }

    if (game_won(board)) {
        SDL_SetWindowTitle(gs->window, GAME_WON);
        gs->game_over = 1;
    }

    reset_input(input);
}

void reveal_mines(Board *board) {
    for (int i = 0; i < board->rows * board->cols; i++) {
        if (board->grid[i].is_mine) {
            board->grid[i].is_seen = board->peek;
        }
    }
    board->peek = !board->peek;
}

void reveal_board(Board *board) {
    for (int i = 0; i < board->rows * board->cols; i++) {
        board->grid[i].is_seen = 1;
        board->grid[i].is_flag = 0;
    }
}

int game_won(Board *board) {
    for (int i = 0; i < board->rows * board->cols; i++) {
        Cell *cell = &board->grid[i];
        if (!cell->is_mine && !cell->is_seen) return 0;
        if (cell->is_mine && !cell->is_flag && cell->is_seen) return 0;
    }
    return 1;
}

void toggle_flag(Board *board, int row, int col) {
    int idx = row * board->cols + col;
    Cell *cell = &board->grid[idx];

    if (cell->is_seen) return;
    cell->is_flag = !cell->is_flag;
}

int n_bounds(Board *board, int row, int col) {
    return (row < 0 || row >= board->rows ||
            col < 0 || col >= board->cols);
}

void reveal_single(GameState *gs, Board *board, int row, int col) {
    if (n_bounds(board, row, col)) return;

    if (gs->first_move) {
        place_mines(board, row, col);
        calc_mines(board);
        gs->first_move = 0;
    }

    int idx = row * board->cols + col;
    Cell *cell = &board->grid[idx];

    if (cell->is_seen || cell->is_flag) return;

    if (cell->is_mine) {
        SDL_SetWindowTitle(gs->window, GAME_LOST);
        reveal_board(board);
        gs->game_over = 1;
        return;
    }

    cell->is_seen = 1;

    if (cell->neig_mines > 0) return;

    // Recursively reveal for all cells with zero neighbors
    if (cell->neig_mines == 0) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                reveal_single(gs, board, row + dx, col + dy);
            }
        }
    }
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
    for (int i = 0; i < board->rows * board->cols; i++) {
        render_cell(gs, assets, &board->grid[i]);
    }
    SDL_RenderPresent(gs->renderer);
}
