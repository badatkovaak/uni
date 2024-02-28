#include <stdio.h>

#include "defines.h"

#define Coord1(a) a >> 32
#define Coord2(a) a % (1 << 32)

typedef struct {
    u64* cells;
    u64 size1;
    u64 size2;
} labyrinth;

typedef struct {
    u64* cells;
    u64 len;
} path;

path solveLabyrinth(labyrinth l, path p) { return (path){0, 0}; }

int main(void) {
    if (true) {
    }
    return 0;
}
