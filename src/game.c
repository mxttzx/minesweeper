#include "../include/game.h"

Board *new_game(GameState *gs, int rows, int cols, int mines) {
    Board *board = init_board(rows, cols, mines);
    gs->game_over = 0;
    gs->first_move = 1;

    return board;
}

void update_game(GameState *gs, Board *board, InputState *input) {
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

    if (game_won(board)) {
        gs->game_over = 1;
        gs->should_continue = 0;
        SDL_SetWindowTitle(gs->window, WON);
    }
}

void reveal_board(Board *board) {
    for (int r = 0; r < board->rows; r++) {
        for (int c = 0; c < board->cols; c++) {
            board->grid[r][c].is_seen = 1;
            board->grid[r][c].is_flag = 0;
        }
    }
}

int game_won(Board *board) {
    for (int r = 0; r < board->rows; r++) {
        for (int c = 0; c < board->cols; c++) {
            Cell *cell = &board->grid[r][c];
            if (!cell->is_mine && !cell->is_seen) return 0;
            if (cell->is_mine && !cell->is_flag) return 0;
        }
    }
    return 1;
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

    if (gs->first_move) {
        place_mines(board, row, col);
        calc_mines(board);
        gs->first_move = 0;
    }

    Cell *cell = &board->grid[row][col];

    if (cell->is_seen || cell->is_flag) return;

    if (cell->is_mine) {
        SDL_SetWindowTitle(gs->window, LOST);
        reveal_board(board);
        gs->game_over = 1;
        return;
    }

    cell->is_seen = 1;

    if (cell->neig_mines > 0) return;

    // Recursively reveal for all cells with zero neighbors
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
