#ifndef GAME_H_
#define GAME_H_

#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "state.h"
#include "assets.h"
#include "save.h"

Board *new_game(GameState *gs, int rows, int cols, int mines);
void update_game(GameState *gs, Board *board, InputState *input);
void render_game(GameState *gs, Board *board, Assets *assets);
void reveal_single(GameState *gs, Board *board, int x, int y);
void reveal_board(Board *board);
void toggle_flag(Board *board, int x, int y);
void toggle_peek(GameState *gs, Board *board);
int check_win(Board *board);


#endif
