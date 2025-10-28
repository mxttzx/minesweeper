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

void render_game(GameState *gs, Board *b) {
    SDL_Surface *gScreenSurface = SDL_GetWindowSurface(gs->window);

    SDL_SetRenderDrawColor(gs->renderer, 255, 255, 255, 255);
    SDL_RenderClear(gs->renderer);

    for (int i = 0; i < b->rows; i++) {
        for (int j = 0; i< b->cols; j++) {
            SDL_Rect dest;

            SDL_RenderCopy(gs->renderer, img, NULL, &texr);
        }
    }
    SDL_RenderPresent(gs->renderer);
}
