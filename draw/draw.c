#include "draw.h"
#include <stdlib.h>
#include <string.h>

char *_build_asset_path(const char *file)
{
    size_t path_len = strlen(IMAGE_DIR) + strlen(file) + 2; // Seperator (/) and null terminator
    char *path = malloc(path_len);

    if(path == NULL) {
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

void draw_cell(SDL_Surface *gScreenSurface, SDL_Window *gWindow, struct cell *c)
{
    SDL_Rect pos = {
        c->x * IMAGE_WIDTH,
        c->y * IMAGE_HEIGHT,
        IMAGE_WIDTH,
        IMAGE_HEIGHT
    };

    SDL_Surface *image = load_image(c->asset);
    if (image == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", c->asset, SDL_GetError());
        exit(1);
    }

    SDL_BlitSurface(image, NULL, gScreenSurface, &pos);
    SDL_UpdateWindowSurface(gWindow);
}

void draw_grid(SDL_Surface *gScreenSurface, SDL_Window *gWindow, int rows, int cols)
{
    int i, j;
    struct cell grid[rows][cols];

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            struct cell *c = &grid[i][j];
            c->x = i;
            c->y = j;
            c->asset = "0.bmp";
            draw_cell(gScreenSurface, gWindow, c);
        }
    }
}
