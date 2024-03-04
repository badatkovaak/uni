#include <stdio.h>

#include "defines.h"
#include "vector.h"

#define Opposite(d) (d >= 2) ? d - 2 : d + 2

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

u8 countSetBits(u8 n) {
    unsigned int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

Coord apply_path(Coord init, Vector_Dir* p) {
    for (u64 i = 0; i < p->len; i++) {
        switch ((Dir)p->data[i]) {
            case Down:
                init.y += 1;
                break;
            case Right:
                init.x += 1;
                break;
            case Up:
                init.y -= 1;
                break;
            case Left:
                init.x -= 1;
                break;
        }
    }
    return init;
}

Vector_Dir solveLabyrinth(Labyrinth* l, Vector_Dir* d, Coord init) {
    Vector_Dir zero = (Vector_Dir){0, 0, 0};
    Coord curr = init;
    u64 count = 0;
    Vector_Dir walked = (Vector_Dir){0, 0, 0};
    Dir avail[4] = {0};

    Dir came_from = 0;
    if (d->len) {
        came_from = Opposite(get_Dir(d, d->len - 1));
    } else {
        came_from = Up;
    }

    for (;;) {
        printf("coords %u %u\n", curr.x, curr.y);
        for (u64 i = 1; i < 5; i++) {
            switch (i) {
                case Down:
                    if (curr.y + 1 == l->height || came_from == Down) {
                        printf("Down %u %u\n", curr.y, l->height);
                        break;
                    }
                    if (!l->cells[(curr.y + 1) * l->width + curr.x]) {
                        break;
                    }
                    if ((curr.y + 1) * l->width + curr.x ==
                        (l->width - 1) * (l->height - 1)) {
                        push_Dir(&walked, Down);
                        for (u64 i = d->len - 1; i >= 0; i--) {
                            push_Dir(&walked, get_Dir(d, i));
                        }
                        return walked;
                    }
                    avail[count] = Down;
                    count++;
                    break;
                case Right:
                    if (curr.x + 1 == l->width || came_from == Right) {
                        printf("Right %u %u\n", curr.x, l->width);
                        break;
                    }
                    if (!l->cells[curr.y * l->width + curr.x + 1]) {
                        break;
                    }
                    if (curr.y * l->width + curr.x + 1 ==
                        (l->width - 1) * (l->height - 1)) {
                        push_Dir(&walked, Down);
                        for (u64 i = d->len - 1; i >= 0; i--) {
                            push_Dir(&walked, get_Dir(d, i));
                        }
                        return walked;
                    }
                    avail[count] = Right;
                    count++;
                    break;
                case Up:
                    if (!curr.y || came_from == Up) {
                        printf("Up %u %u\n", curr.y, l->height);
                        break;
                    }
                    if (!l->cells[(curr.y - 1) * l->width + curr.x]) {
                        break;
                    }
                    avail[count] = Up;
                    count++;
                    break;
                case Left:
                    if (!curr.x || came_from == Left) {
                        printf("Left %u %u\n", curr.x, l->width);
                        break;
                    }
                    if (!l->cells[curr.y * l->width + curr.x - 1]) {
                        break;
                    }
                    avail[count] = Left;
                    count++;
                    break;
            }
        }

        printf("count: %lu\n", count);

        Dir next = 0;
        if (!count) {
            return zero;
        } else if (count == 1 && curr.x + curr.y != 0) {
            return zero;
        } else if (count == 1 && curr.x + curr.y == 0) {
            printf("avail %u\n", avail[0]);
            next = avail[0];
        } else if (count == 2) {
            if (avail[0] != came_from) {
                next = avail[0];
            } else {
                next = avail[1];
            }
        } else {
            for (u64 i = 0; i < count; i++) {
                if (avail[i] == came_from) {
                    continue;
                }
                push_Dir(d, avail[i]);
                push_Dir(&walked, avail[i]);
                Vector_Dir res = solveLabyrinth(l, d, curr);
                pop_Dir(&walked);
                pop_Dir(d);
                if (!res.len) {
                    puts("Here");
                    continue;
                } else {
                    return res;
                }
            }
        }
        printf("next : %u %u\n", next, came_from);
        push_Dir(&walked, next);
        count = 0;
        avail[0] = 0;
        avail[1] = 0;
        curr = apply_path(curr, &walked);
    }

    return zero;
}

int main(void) {
    // printf("%u %u %u\n", sizeof(Labyrinth), sizeof(Coord), sizeof(Path));

    Vector_Dir d = (Vector_Dir){0, 0, 0};
    Labyrinth l = (Labyrinth){LAB, 4, 4};
    solveLabyrinth(&l, &d, (Coord){0, 0});
    return 0;
}
