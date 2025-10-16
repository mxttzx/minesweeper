#ifndef DRAW_H_
#define DRAW_H_

#include "SDL.h"
#include "SDL_rect.h"
#include "SDL_surface.h"
#include "SDL_error.h"

#include "cell.h"
#include "../gui/GUI.h"

#define IMAGE_DIR "../gui/Images/"

SDL_Surface *load_image(const char *);

void draw_cell(SDL_Surface *, SDL_Window *, struct cell *);
void draw_grid(SDL_Surface *, SDL_Window *, int, int);

void destroy_cell();
void destroy_grid();

#endif
