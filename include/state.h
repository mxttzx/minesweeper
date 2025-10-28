#ifndef STATE_H_
#define STATE_H_

#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_scancode.h"
#include "SDL_video.h"
#include "SDL.h"

#define GAME_NAME "Minesweeper"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 600

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int should_continue;
    int mouse_x, mouse_y;
    int game_over;
} GameState;

typedef struct {
    int keys[SDL_NUM_SCANCODES];
    int mouse_x, mouse_y;
    int mouse_input;
    int quit;
} InputState;

void init_gui(GameState *gs, InputState *input, const char *title, int w, int h);
void free_gui(GameState *gs);

void read_input(GameState *gs, InputState *input);

#endif
