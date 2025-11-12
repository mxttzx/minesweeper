#include "../include/state.h"
#include "SDL_keycode.h"
#include "SDL_mouse.h"
#include <stdlib.h>

static int is_relevant_event(SDL_Event *event) {
    if (event == NULL) {
        return 0;
    }
    return (event->type == SDL_MOUSEBUTTONDOWN) ||
            (event->type == SDL_MOUSEBUTTONUP) ||
            (event->type == SDL_KEYUP) ||
            (event->type == SDL_KEYDOWN) ||
            (event->type == SDL_QUIT);
}

void reset_input(InputState *input) {
    input->keys[SDLK_p] = 0;
    input->keys[SDLK_s] = 0;
    input->keys[SDL_BUTTON_LEFT] = 0;
    input->keys[SDL_BUTTON_RIGHT] = 0;
}

void read_input(GameState *gs, InputState *input) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (!is_relevant_event(&event)) continue;

        switch (event.type) {
            case SDL_QUIT:
                gs->should_continue = 0;
                SDL_Quit();
                break;

            // Allow only one singular key per event
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_p) {
                    input->keys[SDLK_p] = 1;
                } else if (event.key.keysym.sym == SDLK_s) {
                    input->keys[SDLK_s] = 1;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    input->keys[SDL_BUTTON_LEFT] = 1;
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    input->keys[SDL_BUTTON_RIGHT] = 1;
                }
                break;
        }
    }
    SDL_GetMouseState(&input->mouse_x, &input->mouse_y);
}

void init_gui(GameState *gs, InputState *input, const char *title, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "init_gui: failed to initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    gs->window = SDL_CreateWindow(title, 0, 0, w, h, SDL_WINDOW_SHOWN);

    if (!gs->window) {
        fprintf(stderr, "init_gui: failed to create SDL window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    gs->renderer = SDL_CreateRenderer(gs->window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gs->renderer, 255, 255, 255, 255);
}

void free_gui(GameState *gs) {
    if (gs->renderer) SDL_DestroyRenderer(gs->renderer);
    if (gs->window) SDL_DestroyWindow(gs->window);
    SDL_Quit();
}
