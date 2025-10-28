#ifndef GAME_H_
#define GAME_H_

#include <stdlib.h>
#include "../include/board.h"
#include "../include/state.h"
#include "../include/assets.h"

Board* new_board();
void new_game(GameState *gs, Board *board);
void update_game(GameState *gs, InputState *input, Board *board);
void render_game(GameState *gs, Board *board, Assets *assets);

#endif
