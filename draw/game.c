#include "game.h"

void new_game(GameState *gs) {
    Board b;

    init_grid(&b);
    place_mines(&b);
}

void update_game(GameState *gs) {
    //
}

void render_game(GameState *gs) {
    SDL_Surface *gScreenSurface = SDL_GetWindowSurface(gs->window);
}
