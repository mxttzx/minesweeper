#include "include/state.h"
#include "include/board.h"
#include "include/game.h"
#include "include/assets.h"

int main(int argc, char *argv[]) {
    GameState gs;
    InputState input;
    Assets assets;

    int rows = 9;
    int cols = 9;
    int mines = 9;

    if (argc >= 4){
        rows = atoi(argv[1]);
        cols = atoi(argv[2]);
        mines = atoi(argv[3]);
    } else {
        printf("No custom dimensions provided, resuming with default config: (%dx%d) grid, %d mines\n", rows, cols, mines);
    }

    init_gui(&gs, &input, GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    load_assets(gs.renderer, &assets);

    srand((unsigned) time(NULL)); // Initialize a random seed based on int time value

    Board *board = new_game(&gs, rows, cols, mines);
    while(gs.should_continue) {
        read_input(&gs, &input);
        update_game(&gs, board, &input);
        render_game(&gs, board, &assets);
    }

    free_assets(&assets);
    free_board(board);
    free_gui(&gs);
    return 0;
}
