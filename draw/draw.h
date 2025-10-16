#ifndef DRAW_H_
#define DRAW_H_

#include "SDL.h"
#include "SDL_rect.h"
#include "SDL_surface.h"
#include "SDL_error.h"
#include <time.h>

#include "board.h"
#include "../utils/load_asset.h"

void draw_grid(SDL_Window *, int, int);
void draw_cell(SDL_Window *, Cell *);
void port_board_sdl(SDL_Window *, Board *);

#endif
