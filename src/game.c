#include "../include/game.h"

Board *new_game(GameState *gs, int rows, int cols, int mines) {
    printf("Starting a new game: (%dx%d), %d mines\n", rows, cols, mines);

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
    }

    if (input->keys[SDLK_p] && !gs->first_move) {
        toggle_peek(gs, board);
    }

    if (check_win(board)) {
        SDL_SetWindowTitle(gs->window, GAME_WON);
        reveal_board(board);
        gs->game_over = 1;
        return;
    }

    reset_input(input);
}

void toggle_peek(GameState *gs, Board *board) {
    // If we are not peeking, we save the needed state of the current board to masks
    if (!gs->peek) {
        for (int i = 0; i < board->rows * board->cols; i++) {
            // Save values into masks
            board->peek_mask[i] = !board->grid[i].is_seen;
            board->flag_mask[i] = board->grid[i].is_flag;

            // Show all cell values ("peeking")
            if (board->peek_mask[i]) {
                board->grid[i].is_seen = 1;
                board->grid[i].is_flag = 0;
            }
        }
    } else {
        // If we are peeking, we restore the state of the game
        for (int i = 0; i < board->cols * board->rows; i++) {
            if (board->peek_mask[i]) {
                board->grid[i].is_seen = 0; // Stop peeking
            }

            board->grid[i].is_flag = board->flag_mask[i]; // Restore the flags
        }
    }
    gs->peek = !gs->peek; // Switch the value on/off
}

void reveal_board(Board *board) {
    for (int i = 0; i < board->rows * board->cols; i++) {
        board->grid[i].is_seen = 1;
        board->grid[i].is_flag = 0;
    }
}

bool in_bounds(Board *board, int row, int col) {
    return (row >= 0 && row < board->rows &&
            col >= 0 && col < board->cols);
}

void toggle_flag(Board *board, int row, int col) {
    if (!in_bounds(board, row, col)) return;

    int idx = row * board->cols + col;
    Cell *cell = &board->grid[idx];

    if (cell->is_seen) return;

    if (cell->is_flag) {
        cell->is_flag = 0;
        board->flags++;
    } else {
        if (board->flags == 0) return;
        cell->is_flag = 1;
        board->flags--;
    }
}

void reveal_single(GameState *gs, Board *board, int row, int col) {
    if (!in_bounds(board, row, col)) return;

    // Place mines after the first move
    if (gs->first_move) {
        place_mines(board, row, col);
        calc_mines(board);
        gs->first_move = 0;
    }

    int idx = row * board->cols + col;
    Cell *cell = &board->grid[idx];

    if (cell->is_seen || cell->is_flag) return; // Do nothing

    // Stepped on a mine
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

// This function can be improved by not iterating over every cell for every input
// We can keep track of the flags placed and revealed cells while playing
int check_win(Board *board) {
    int flag = 0;
    int seen = 0;

    for (int i = 0; i < board->rows * board->cols; i++) {
        Cell *cell = &board->grid[i];
        if (!cell->is_mine && cell->is_flag) return 0;
        if (cell->is_mine && cell->is_flag) flag++; // Only win if all mines are flagged
        if (cell->is_seen) seen++; // Keep track of how many cells are seen
    }

    // If all flags are placed on mines -> win
    // If all cells have been revealed except for mines -> win
    return ((flag == board->mines) || (seen == (board->rows * board->cols) - board->mines));
}

void render_cell(GameState *gs, Assets *assets, Cell *cell) {
    SDL_Texture *text = NULL;

    if (cell->is_flag) text = assets->flagged;
    else if (!cell->is_seen) text = assets->covered;
    else if (cell->is_mine) text = assets->mine;
    else text = assets->numbers[cell->neig_mines];

    // Render the cell at correct cell dimension offset
    SDL_Rect dest = {
        cell->x * CELL_WIDTH,
        cell->y * CELL_HEIGHT,
        CELL_WIDTH,
        CELL_HEIGHT
    };

    SDL_RenderCopy(gs->renderer, text, NULL, &dest);
}

// Renders the board
void render_game(GameState *gs, Board *board, Assets *assets) {
    SDL_RenderClear(gs->renderer);
    for (int i = 0; i < board->rows * board->cols; i++) {
        render_cell(gs, assets, &board->grid[i]);
    }
    SDL_RenderPresent(gs->renderer);
}
