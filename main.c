#include "include/state.h"
#include "include/board.h"
#include "include/game.h"
#include "include/assets.h"
#include "include/save.h"
#include "include/args.h"


int main(int argc, char *argv[]) {
    // Default values for starting a game
    union arguments def = {
        .dims.cols = 9,
        .dims.rows = 9,
        .dims.mines = 9,
    };

    struct variant startup = {
        .args = def,
        .mode = MODE_DIMS
    };

    srand((unsigned) time(NULL)); // Initialize a random seed based on int time value

    GameState gs;
    InputState input;
    Assets assets;

    memset(&gs, 0, sizeof(gs));
    memset(&input, 0, sizeof(input));

    parse_args(&startup, argc, argv);

    Board *board;
    if (startup.mode == MODE_FILE) {
        board = load_game(&gs, startup.args.file.path);
    } else {
        board = new_game(&gs, startup.args.dims.rows, startup.args.dims.cols, startup.args.dims.mines);
    }

    init_gui(&gs, GAME_NAME, board->cols * CELL_WIDTH, board->rows * CELL_HEIGHT);
    load_assets(gs.renderer, &assets);

    while(gs.should_continue) {
        read_input(&gs, &input);

        if (!gs.game_over) {
            update_game(&gs, board, &input);
        }

        render_game(&gs, board, &assets);
    }

    free_assets(&assets);
    free_board(board);
    free_gui(&gs);

    return EXIT_SUCCESS;
}
