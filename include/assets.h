#ifndef ASSETS_H_
#define ASSETS_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include <stdlib.h>

#define PATH_FLAGGED "../assets/flagged.bmp";
#define PATH_COVERED "../assets/covered.bmp";
#define PATH_MINE "../assets/mine.bmp";

typedef struct {
    SDL_Texture *flagged;
    SDL_Texture *mine;
    SDL_Texture *covered;
    SDL_Texture *numbers[9];
} Assets;

void load_assets(SDL_Renderer *renderer, Assets *assets);
void free_assets(Assets *assets);

#endif
