#ifndef DRAW_H_
#define DRAW_H_

#include "SDL.h"
#include "SDL_rect.h"
#include "SDL_surface.h"
#include "SDL_error.h"

#define IMAGE_DIR "../gui/Images/"

SDL_Surface *load_image(const char *);

void draw_image(SDL_Surface *, SDL_Window *, const char *, SDL_Rect *);
void draw_grid(int *, int *);

void destory_image();
void destroy_grid();

#endif
