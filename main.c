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

    srand((unsigned) time(NULL)); // Initialize a random seed based on int time value

    while(gs.should_continue) {
        read_input(&gs, &input);
        update_game(&gs, &input, board);
        render_game(&gs, board, &assets);
    }

    free_assets(&assets);
    free(board);
    free_gui(&gs);
    return 0;
}
