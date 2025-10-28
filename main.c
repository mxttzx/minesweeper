#include "SDL_keycode.h"
#include "include/state.h"
#include "include/board.h"
#include "include/game.h"
#include "include/assets.h"

int main(int argc, char *argv[]) {
    GameState gs;
    InputState input;
    Assets assets;

    Board *board = new_board();

    init_gui(&gs, &input, GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    load_assets(gs.renderer, &assets);

    while(gs.should_continue) {
        read_input(&gs, &input);

        if (input.keys[SDLK_RETURN]) {
            new_game(&gs, board);
        }

        if (input.keys[SDLK_p]) {
            gs.should_continue = 0;
        }

        if (input.keys[SDLK_x]) {
            gs.should_continue = 0;
            gs.game_over = 1;
        }

        // update_game(&gs, &input, board);
        render_game(&gs, board, &assets);
    }

    free_assets(&assets);
    free(board);
    free_gui(&gs);
    return 0;
}
