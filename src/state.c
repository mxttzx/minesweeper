#include "../include/state.h"
#include "SDL_mouse.h"

static int is_relevant_event(SDL_Event *event) {
    if (event == NULL) {
        return 0;
    }
    return (event->type == SDL_MOUSEBUTTONDOWN) ||
            (event->type == SDL_KEYDOWN) ||
            (event->type == SDL_QUIT);
}

void read_input(GameState *gs, InputState *input) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (!is_relevant_event(&event)) continue;

        switch (event.type) {
            case SDL_KEYDOWN:
            input->keys[event.key.keysym.sym] = 1;
            break;

            case SDL_KEYUP:
            input->keys[event.key.keysym.sym] = 0;
            break;

            case SDL_QUIT:
            input->quit = 1;
            break;

            case SDL_MOUSEBUTTONDOWN:
            input->mouse_input = 1;
            break;
        }
    }

    SDL_GetMouseState(&input->mouse_x, &input->mouse_y);
}

void init_gui(GameState *gs, InputState *input, const char *title, int w, int h) {
    memset(gs, 0, sizeof(*gs));
    memset(input, 0, sizeof(*input));

    gs->should_continue = 1;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }

    gs->window = SDL_CreateWindow(title, 0, 0, w, h, SDL_WINDOW_SHOWN);

    if (!gs->window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        exit(1);
    }

    gs->renderer = SDL_CreateRenderer(gs->window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gs->renderer, 255, 255, 255, 255);
}

void free_gui(GameState *gs) {
    if (gs->renderer) SDL_DestroyRenderer(gs->renderer);
    if (gs->window) SDL_DestroyWindow(gs->window);
    SDL_Quit();
}
