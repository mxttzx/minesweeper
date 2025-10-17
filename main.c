#include "gui/GUI.h"
#include "draw/state.h"
#include "draw/game.h"

int main(int argc, char *argv[]) {
    GameState gs;
    InputState input;

    init_gui(&gs, GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);

    while(gs.should_continue) {
        read_input(&gs, &input);

        if (input.keys[SDLK_RETURN]) {
            new_game(&gs);
        }

        if (input.keys[SDLK_p]) {
            gs.should_continue = 0;
        }

        if (input.keys[SDLK_x]) {
            gs.should_continue = 0;
            gs.game_over = 1;
        }

        // update_game(&gs, &input, )
        // render_game()
    }

    free_gui(&gs);
    return 0;
}
