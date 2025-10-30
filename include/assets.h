#ifndef ASSETS_H_
#define ASSETS_H_

#include "SDL.h"
#include "SDL_render.h"
#include "SDL_surface.h"

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
