#ifndef SAVE_H_
#define SAVE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "state.h"

#define DEFAULT_FILE "lsave.bat"

Board *load_game(GameState *gs, const char *filename);
void save_game(GameState *gs, Board *board, const char *filename);

#endif
