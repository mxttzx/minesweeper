#include "include/state.h"
#include "include/board.h"
#include "include/game.h"
#include "include/assets.h"
#include "include/save.h"
#include <argp.h>

// https://stackoverflow.com/a/24479532
const char *argp_program_version = "Minesweeper 1.0";
const char *argp_program_bug_address = "mathijs.custers@vub.be";

static const char doc[] = "A simple minesweeper implementation";
static const char args_doc[] = "";

static struct argp_option options[] = {
    { "rows", 'w', "ROWS", 0, "The amount of rows of the playing board" },
    { "cols", 'h', "COLS", 0, "The amount of columns of the playing board" },
    { "mines", 'm', "MINES", 0, "The amount of mines the playing board has" },
    { "file", 'f', "FILE", 0, "The file from which to load an existing game" },
    { 0 }
};

struct arguments {
    int rows;
    int cols;
    int mines;
    char *file;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
        char *endptr;
        case 'w': arguments->rows = strtol(arg, &endptr, 10); break;
        case 'h': arguments->cols = strtol(arg, &endptr, 10); break;
        case 'm': arguments->mines = strtol(arg, &endptr, 10); break;
        case 'f': arguments->file = arg; break;
        default: return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };


int main(int argc, char *argv[]) {
    struct arguments arguments = { .rows = 9, .cols = 9, .mines = 9 };

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    srand((unsigned) time(NULL)); // Initialize a random seed based on int time value

    GameState gs;
    InputState input;
    Assets assets;

    memset(&gs, 0, sizeof(gs));
    memset(&input, 0, sizeof(input));

    Board *board;
    if (arguments.file) {
        printf("Loading existing game from load file: %s\n", arguments.file);
        board = load_game(&gs, arguments.file);

    } else {
        printf("Started a new game: (%dx%d), %d mines\n", arguments.rows, arguments.cols, arguments.mines);
        board = new_game(&gs, arguments.rows, arguments.cols, arguments.mines);
    }

    init_gui(&gs, &input, GAME_NAME, board->cols * CELL_WIDTH, board->rows * CELL_HEIGHT);
    load_assets(gs.renderer, &assets);

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
