#include "../include/assets.h"


// Need to optimize, but will work for now
void load_assets(SDL_Renderer *renderer, Assets *assets) {
    SDL_Surface *surface;

    surface = SDL_LoadBMP("../assets/flagged.bmp");
    assets->flagged = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("../assets/covered.bmp");
    assets->covered = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("../assets/mine.bmp");
    assets->mine = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    for (int i = 0; i <= 8; i++) {
        char path[64];
        snprintf(path, sizeof(path), "../assets/%d.bmp", i);
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
