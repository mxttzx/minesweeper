#include "game.h"
#include "draw.h"

void new_game(GameState *gs) {
    Board b;

    init_grid(&b);
    place_mines(&b);
}

void update_game(GameState *gs, Board *b) {
    //
}

void render_game(GameState *gs, Board *b) {
    port_board_sdl(gs->window, b);
    SDL_Surface *gScreenSurface = SDL_GetWindowSurface(gs->window);
}
