#include "../include/assets.h"


// Need to optimize, but will work for now
void load_assets(SDL_Renderer *renderer, Assets *assets) {
    SDL_Surface *surface;

    surface = SDL_LoadBMP("./assets/flagged.bmp");
    if (!surface) {
        fprintf(stderr, "Failed to load flagged.bmp: %s\n", SDL_GetError());
    } else {
        assets->flagged = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (!assets->flagged)
            fprintf(stderr, "Failed to create texture from flagged.bmp: %s\n", SDL_GetError());
    }

    surface = SDL_LoadBMP("./assets/covered.bmp");
    if (!surface) {
        fprintf(stderr, "Failed to load covered.bmp: %s\n", SDL_GetError());
    } else {
        assets->covered = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (!assets->covered)
            fprintf(stderr, "Failed to create texture from covered.bmp: %s\n", SDL_GetError());
    }

    surface = SDL_LoadBMP("./assets/mine.bmp");
    if (!surface) {
        fprintf(stderr, "Failed to load mine.bmp: %s\n", SDL_GetError());
    } else {
        assets->mine = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (!assets->mine)
            fprintf(stderr, "Failed to create texture from mine.bmp: %s\n", SDL_GetError());
    }

    for (int i = 0; i <= 8; i++) {
        char path[64];
        snprintf(path, sizeof(path), "./assets/%d.bmp", i);
        surface = SDL_LoadBMP(path);
        assets->numbers[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}

void free_assets(Assets *assets) {
    SDL_DestroyTexture(assets->flagged);
    SDL_DestroyTexture(assets->mine);
    SDL_DestroyTexture(assets->covered);
    for (int i = 0; i <= 8; i++) SDL_DestroyTexture(assets->numbers[i]);
}
