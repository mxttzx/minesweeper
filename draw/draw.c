#include "draw.h"
#include <string.h>


char *_build_asset_path(const char *file)
{
    size_t path_len = strlen(IMAGE_DIR) + strlen(file) + 2; // Seperator (/) and null terminator
    char *path = malloc(path_len);

    if(!path) {
        printf("Unable to allocate memory for asset path.\n");
        exit(1);
    }

    snprintf(path, path_len, "%s%s", IMAGE_DIR, file);

    return path;
}

SDL_Surface *load_image(const char *file)
{
    char *image = _build_asset_path(file);
    SDL_Surface *gImage = SDL_LoadBMP(image);

    if (gImage == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", image, SDL_GetError());
        exit(1);
    }

    free(image);

    return gImage;
}

void draw_image(SDL_Surface *gScreenSurface, SDL_Window *gWindow, const char *file, SDL_Rect *position)
{
    SDL_Surface *image = load_image(file);
    SDL_BlitSurface(image, NULL, gScreenSurface, position);
    SDL_UpdateWindowSurface(gWindow);
}
