#ifndef STATE_H_
#define STATE_H_

#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include "SDL.h"

#include "./draw/game.h"

#define GAME_NAME "Minesweeper"

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int should_continue;
    int mouse_x, mouse_y;
    int game_over;
} GameState;

void init_gui(GameState *gs, const char *title, int w, int h);
void free_gui(GameState *gs);

void read_input(GameState *gs);
static int is_relevant_event(SDL_Event *event);

#endif
