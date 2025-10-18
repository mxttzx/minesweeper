#ifndef GAME_H_
#define GAME_H_

#include "board.h"
#include "draw.h"
#include "state.h"

Board* new_game(GameState *gs);
void update_game(GameState *gs, InputState *input, Board *board);
void render_game(GameState *gs, Board *board);

#endif
