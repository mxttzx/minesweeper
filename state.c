#include "state.h"
#include "SDL_keycode.h"


static int is_relevant_event(SDL_Event *event) {
    if (event == NULL) {
        return 0;
    }
    return (event->type == SDL_MOUSEBUTTONDOWN) ||
            (event->type == SDL_KEYDOWN) ||
            (event->type == SDL_QUIT);
}

void read_input(GameState *gs) {
    SDL_Event event;

    while (1) {
        int event_polled = SDL_PollEvent(&event);
        if (event_polled == 0) {
            return;
        } else if (is_relevant_event(&event)) {
            break;
        }
    }

    switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_p) {
                printf("P pressed\n");
                gs->should_continue = 0;
            }
            if (event.key.keysym.sym == SDLK_RETURN) {
                printf("Return pressed\n");
                // Start new game here!
            }
            break;
        case SDL_QUIT:
            gs->should_continue = 0;
            gs->game_over = 1;
            break;
        case SDL_MOUSEBUTTONDOWN:
            gs->mouse_x = event.button.x;
            gs->mouse_y = event.button.y;
            break;
    }
}

void init_gui(GameState *gs, const char *title, int w, int h) {
    memset(gs, 0, sizeof(*gs));
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
