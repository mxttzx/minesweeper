#ifndef STATE_H_
#define STATE_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_error.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_scancode.h"
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_mouse.h"
#include "assets.h"

#define GAME_NAME "Minesweeper"
#define GAME_WON "YOU WON!"
#define GAME_LOST "YOU LOST!"

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int should_continue;
    int game_over;
    int first_move;
    int peek;
} GameState;

typedef struct {
    int keys[SDL_NUM_SCANCODES];
    int mouse_x, mouse_y;
    int mouse_input;
    int quit;
} InputState;

void init_gui(GameState *gs, const char *title, int w, int h);
void free_gui(GameState *gs);

void read_input(GameState *gs, InputState *input);
void reset_input(InputState *input);

#endif
