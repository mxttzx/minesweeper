#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "load_asset.h"

char *_build_asset_path(const char *file)
{
    size_t path_len = strlen(IMAGE_DIR) + strlen(file) + 2;
    char *path = malloc(path_len);

    if(path == NULL) {
        printf("Unable to allocate memory for asset path.\n");
        exit(1);
    }

    snprintf(path, path_len, "%s%s", IMAGE_DIR, file);

    return path;
}

SDL_Surface *_load_image(const char *file)
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
