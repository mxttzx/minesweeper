#ifndef TEMP_H_
#define TEMP_H_

#include "board.h"

// Temporary structs needed to animate wins and losses
typedef struct {
    Cell *cell;
    int count;
    int done;
} TempLoss;

typedef struct {
    Cell **cells;
    int amount;
    int count;
    int done;
} TempWin;

#endif
