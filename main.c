#include "include/state.h"
#include "include/board.h"
#include "include/game.h"


int main(int argc, char *argv[]) {
    GameState gs;
    InputState input;

    Board *board = new_board();

    init_gui(&gs, GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);

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

        update_game(&gs, &input, board);
        render_game(&gs, board);
    }

    free(board);
    free_gui(&gs);
    return 0;
}
