#ifndef GAME_H_
#define GAME_H_

#include <stdlib.h>
#include <stdbool.h>
#include "../include/board.h"
#include "../include/state.h"
#include "../include/assets.h"
#include "../include/save.h"

Board *new_game(GameState *gs, int rows, int cols, int mines);
void update_game(GameState *gs, Board *board, InputState *input);
void render_game(GameState *gs, Board *board, Assets *assets);
void reveal_single(GameState *gs, Board *board, int x, int y);
void reveal_board(Board *board);
void reveal_mines(Board *board);
void toggle_flag(Board *board, int x, int y);
int game_won(Board *board);


#endif
