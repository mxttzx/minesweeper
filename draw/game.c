#include "game.h"
#include "board.h"
#include "draw.h"

void new_game(GameState *gs) {
    Board b;

    init_grid(&b);
    place_mines(&b);

    port_board_sdl(gWindow, &b);
}
