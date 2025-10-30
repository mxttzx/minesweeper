#ifndef GAME_H_
#define GAME_H_

#include <stdlib.h>
#include "../include/board.h"
#include "../include/state.h"
#include "../include/assets.h"

Board* new_board();

void new_game(GameState *gs, Board *board);
void update_game(GameState *gs, Board *board, InputState *input);
void render_game(GameState *gs, Board *board, Assets *assets);
void reveal_single(GameState *gs, Board *board, int x, int y);
void flag_single(Board *board, int x, int y);
void reveal_board(Board *board);
int game_won(Board *board);

#endif
