#include "../include/args.h"

/*
 * Parses the arguments and writes the startup settings to the startup variant struct
 * Starting a game can either be done by starting in MODE_FILE or MODE_DIMS
 */
void parse_args(struct variant *startup, int argc, char *argv[]) {
    int opt;
    char *arg, *endptr;

    // 3c_advanced - slide 11
    while (--argc > 0 && **++argv == '-') {
        char *opts = *argv + 1;
        while((opt = *opts++) != '\0') {
            argv++; argc--;
            arg = *argv;
            switch (opt) {
                case 'f':
                    // File mode will always take priority over dims mode
                    startup->args.file.path = arg;
                    startup->mode = MODE_FILE;
                    break;
                case 'w':
                    startup->args.dims.cols = atoi(arg);
                    break;
                case 'h':
                    startup->args.dims.rows = atoi(arg);
                    break;
                case 'm':
                    startup->args.dims.mines = atoi(arg);
                    break;
                default:
                    fprintf(stderr, "minesweeper: illegal option -%c\n", opt);
                    exit(EXIT_FAILURE);
            }
        }
    }
}
