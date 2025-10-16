#ifndef CELL_H_
#define CELL_H_

#include "../gui/GUI.h"

typedef struct {
    char *asset;
    int x, y;
    int w, h;
    int neig_mines;
    int is_mine;
    int is_flag;
    int is_seen;
} Cell;

#endif
