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

    if (input->keys[SDLK_p] && !gs->first_move) {
        toggle_peek(gs, board);
    }

    if (game_won(board)) {
        SDL_SetWindowTitle(gs->window, GAME_WON);
        reveal_board(board);
        gs->game_over = 1;
    }

    reset_input(input);
}

void toggle_peek(GameState *gs, Board *board) {
    if (!gs->peek) {
        for (int i = 0; i < board->rows * board->cols; i++) {
            board->peek_mask[i] = !board->grid[i].is_seen;
            board->flag_mask[i] = board->grid[i].is_flag;
            if (board->peek_mask[i]) {
                board->grid[i].is_seen = 1;
                board->grid[i].is_flag = 0;
            }
        }
        gs->peek = 1;
    } else {
        for (int i = 0; i < board->cols * board->rows; i++) {
            if (board->peek_mask[i]) {
                board->grid[i].is_seen = 0;
            }
            board->grid[i].is_flag = board->flag_mask[i];
        }
        gs->peek = 0;
    }
}

void reveal_board(Board *board) {
    for (int i = 0; i < board->rows * board->cols; i++) {
        board->grid[i].is_seen = 1;
        board->grid[i].is_flag = 0;
    }
}

void toggle_flag(Board *board, int row, int col) {
    if (board->flags <= 0) return;

    int idx = row * board->cols + col;
    Cell *cell = &board->grid[idx];

    if (cell->is_seen) return;
    cell->is_flag ? board->flags++ : board->flags--;
    cell->is_flag = !cell->is_flag;
}

void reveal_single(GameState *gs, Board *board, int row, int col) {
    if (row < 0 || row >= board->rows ||
        col < 0 || col >= board->cols) return;

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
        game_lost(cell);
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

unsigned int handle_win(unsigned int s, void *param) {
    TempWin *temp = (TempWin *)param;

    for (int i = 0; i < temp->amount; i++) {
        Cell *cell = temp->cells[i];
        cell->is_seen = !cell->is_seen;
    }

    temp->count--;

    if (temp->count <= 0) {
        temp->done = 1;
        free(temp->cells);
        free(temp);
        return 0;
    }
    return s;
}

int game_won(Board *board) {
    for (int i = 0; i < board->rows * board->cols; i++) {
        Cell *cell = &board->grid[i];
        if (!cell->is_mine && !cell->is_seen) return 0;
        if (cell->is_mine && !cell->is_flag && cell->is_seen) return 0;
    }

    Cell **mines = malloc(board->mines * sizeof(Cell *));

    int count = 0;
    for (int i = 0; i < board->rows * board->cols; i++) {
        if (board->grid[i].is_mine) {
            mines[count++] = &board->grid[i];
        }
    }

    TempWin *t = malloc(board->mines * sizeof(TempWin));
    t->cells = mines;
    t->amount = board->mines;
    t->done = 0;
    t->count = 6;

    SDL_AddTimer(500, handle_win, t);
    return 1;
}

// flicker_cell + animate_loss: https://www.studyplan.dev/sdl2/sdl2-timers
unsigned int handle_loss(unsigned int s, void* param) {
    TempLoss *temp = (TempLoss *)param;
    Cell *cell = temp->cell;

    cell->is_seen = !cell->is_seen;
    temp->count--;

    if (temp->count <= 0) {
        temp->done = 1;
        free(temp);
        return 0;
    }
    return s;
}

void game_lost(Cell *cell) {
    TempLoss *t = malloc(sizeof(TempLoss));
    t->cell = cell;
    t->done = 0;
    t->count = 6; // Set to even so it ends up as mine bmp when finished

    SDL_AddTimer(500, handle_loss, t);
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
