#include <stdio.h>

#include "defines.h"
#include "vector.h"

#define Coord1(a) a >> 32
#define Coord2(a) a % (1 << 32)

typedef struct {
    u8* cells;
    u32 height;
    u32 width;
} Labyrinth;

typedef struct {
    u32 x;
    u32 y;
} Coord;

typedef enum Dir {
    Down = 1,
    Right,
    Up,
    Left,
} Dir;

Vec_Decl(Dir);
Vec_Impl(Dir);

// typedef struct {
//     Direction* dirs;
//     // Coord* coords;
//     u64 len;
// } Path;

// clang-format off
static u8 LAB[16] = {
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 0, 0, 1,
    0, 1, 0, 0,
};
// clang-format on

Coord apply_path(Coord init, Vector_Dir* p) {
    for (u64 i = 0; i < p->len; i++) {
        switch ((Dir)p->data[i]) {
            case Down:
                init.y -= 1;
                break;
            case Right:
                init.x += 1;
                break;
            case Up:
                init.y += 1;
                break;
            case Left:
                init.x -= 1;
                break;
        }
    }
    return init;
}

Vector_Dir solveLabyrinth(Labyrinth* l, Vector_Dir* p, Coord init) {
    // Coord init;
    // if (!p->len) {
    //     init = (Coord) { 0, 0 };
    // } else {
    //     init = apply_path((u64)0, p);
    // }

    Coord curr = init;
    for (u64 i = 1; i < 5; i++) {
        switch (i) {
            case Down:
                if (curr.y + 1 == l->height) {
                    break;
                }
                if (l->cells[curr.y * l->width + curr.x]) {
                    break;
                }

                break;
            case Right:
                if (curr.x + 1 == l->width) {
                    break;
                }
            case Up:
                if (!curr.y) {
                    break;
                }
            case Left:
                if (!curr.x) {
                    break;
                }
        }
    }
    // u64 avail_paths_count =
    // if

    return (Vector_Dir){0, 0, 0};
}

int main(void) {
    // printf("%u %u %u\n", sizeof(Labyrinth), sizeof(Coord), sizeof(Path));
    if (true) {
    }
    return 0;
}
