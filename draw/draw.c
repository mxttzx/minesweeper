#include "draw.h"
#include "SDL_video.h"
#include <stdlib.h>

void draw_cell(SDL_Window *gWindow, Cell *c)
{
    SDL_Surface *screen = SDL_GetWindowSurface(gWindow);
    SDL_Surface *image = _load_image(c->asset);

    // Calculations on neighboring mines should be done here (?)
    SDL_Rect pos = {
        c->x * IMAGE_WIDTH,
        c->y * IMAGE_HEIGHT,
        IMAGE_WIDTH,
        IMAGE_HEIGHT
    };

    if (image == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", c->asset, SDL_GetError());
        exit(1);
    }

    SDL_BlitSurface(image, NULL, screen, &pos);
}

void port_board_sdl(SDL_Window *gWindow, Board *board)
{
    int i, j;
    for (i = 0; i < board->rows; i++) {
        for (j = 0; j < board->cols; j++) {
            draw_cell(gWindow, &board->grid[i][j]);
        }
    }

    SDL_UpdateWindowSurface(gWindow);
}
