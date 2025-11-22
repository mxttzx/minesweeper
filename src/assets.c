#include "../include/assets.h"

static SDL_Texture* load_asset(SDL_Renderer *renderer, char const *path) {
    SDL_Surface *surface = SDL_LoadBMP(path);
    if (!surface) {
        fprintf(stderr, "load_asset: failed to load %s: %s\n", path, SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        fprintf(stderr, "load_asset: failed to create texture from %s: %s\n", path, SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return texture;
}

// Need to optimize, but will work for now
void load_assets(SDL_Renderer *renderer, Assets *assets) {
    assets->flagged = load_asset(renderer, "assets/flagged.bmp");
    assets->covered = load_asset(renderer, "assets/covered.bmp");
    assets->mine = load_asset(renderer, "assets/mine.bmp");

    for (int i = 0; i <= 8; i++) {
        char path[64];
        snprintf(path, sizeof(path), "./assets/%d.bmp", i);
        assets->numbers[i] = load_asset(renderer, path);
    }
}

void free_assets(Assets *assets) {
    SDL_DestroyTexture(assets->flagged);
    SDL_DestroyTexture(assets->mine);
    SDL_DestroyTexture(assets->covered);
    for (int i = 0; i <= 8; i++)
        SDL_DestroyTexture(assets->numbers[i]);
}
