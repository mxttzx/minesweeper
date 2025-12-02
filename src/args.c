#include "../include/args.h"

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
                    startup->args.file.path = arg;
                    startup->mode = MODE_FILE;
                    break;
                case 'w':
                    startup->args.dims.cols = strtol(arg, &endptr, 10);
                    break;
                case 'h':
                    startup->args.dims.rows = strtol(arg, &endptr, 10);
                    break;
                case 'm':
                    startup->args.dims.mines = strtol(arg, &endptr, 10);
                    break;
                default:
                    fprintf(stderr, "minesweeper: illegal option -%c\n", opt);
                    exit(EXIT_FAILURE);
            }
        }
    }
}
