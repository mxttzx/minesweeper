#ifndef ARGS_H_
#define ARGS_H_

#include <stdlib.h>
#include <stdio.h>

// WPO6 - poly_plus
typedef struct file {
    char *path;
} FromFile;

typedef struct dims {
    int rows, cols, mines;
} FromDims;

enum mode {
    NONE, MODE_DIMS, MODE_FILE
};

union arguments {
    FromFile file;
    FromDims dims;
};

struct variant {
    union arguments args;
    enum mode mode;
};

void parse_args(struct variant *startup, int argc, char *argv[]);

#endif
