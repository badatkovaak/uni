#include <stdio.h>

#include "defines.h"
#include "vector.h"

#define Opposite(d) (d > 2) ? d - 2 : d + 2

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

// clang-format off

// static u8 LAB[16] = {
//     0, 1, 0, 1,
//     0, 1, 0, 1,
//     0, 0, 0, 1,
//     0, 1, 0, 0,
// };
// const Labyrinth l = {LAB, 4, 4};

static u8 LAB[25] = {
    0, 0, 1, 1, 0,
    1, 0, 0, 0, 0,
    1, 0, 1, 0, 1,
    0, 0, 1, 0, 0,
    1, 0, 0, 1, 0,
};
const Labyrinth l = {LAB, 5, 5};

// static u8 LAB[25] = {
//     0, 1, 0, 1, 0,
//     0, 1, 0, 0, 0,
//     0, 1, 0, 1, 0,
//     0, 0, 0, 1, 0,
//     0, 1, 0, 1, 0, 
// };
// const Labyrinth l = {LAB, 5,5};

// static u8 LAB[25] = {
//     0, 1, 0, 1, 0,
//     0, 1, 0, 1, 0,
//     0, 1, 0, 0, 0,
//     0, 0, 0, 1, 0,
//     0, 1, 0, 1, 0, 
// };
// const Labyrinth l = {LAB, 5,5};

// static u8 LAB[25] = {
//     0, 1, 0, 1, 0,
//     0, 0, 0, 0, 0,
//     0, 1, 0, 1, 0,
//     0, 0, 0, 0, 0,
//     0, 1, 0, 1, 0, 
// };
// const Labyrinth l = {LAB, 5,5};

// static u8 LAB[25] = {
//     0, 1, 0, 1, 0,
//     0, 0, 0, 0, 0,
//     0, 0, 0, 1, 0,
//     1, 0, 0, 1, 0,
//     0, 1, 0, 1, 0, 
// };
// const Labyrinth l = {LAB, 5,5};

// static u8 LAB[25] = {
//     0, 0, 0, 0, 0,
//     0, 1, 1, 1, 0,
//     0, 1, 0, 0, 0,
//     0, 1, 0, 1, 1,
//     0, 1, 0, 0, 0, 
// };
// const Labyrinth l = {LAB, 5,5};

// clang-format on

void print_Dirs(Vec_Dir* v) {
    puts("");
    for (u64 i = 0; i < v->len; i++) {
        switch (v->data[i]) {
            case 1:
                printf("Down\n");
                break;
            case 2:
                printf("Right\n");
                break;
            case 3:
                printf("Up\n");
                break;
            case 4:
                printf("Left\n");
                break;
        }
    }
    puts("");
}

Coord apply_path(Coord init, Vec_Dir* p, u64 start) {
    // puts("");
    for (u64 i = p->len - start; i < p->len; i++) {
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
        // printf("  init : %u %u\n", init.x, init.y);
    }
    // puts("");
    return init;
}

Vec_Dir solve(Labyrinth* l, Coord curr, Dir last) {
    Vec_Dir zero = (Vec_Dir){0, 0, 0};
    Vec_Dir path = zero;
    Dir came_from = 0;
    u64 count = 0;
    Dir avail[4] = {0, 0, 0, 0};
    Dir next = 0;

    if (!last) {
        came_from = Up;
    } else {
        came_from = Opposite(last);
    }

    for (;;) {
        for (u64 i = 1; i < 5; i++) {
            switch (i) {
                case Down:
                    if (curr.y + 1 == l->height || came_from == Down) {
                        break;
                    }
                    if (l->cells[(curr.y + 1) * l->width + curr.x]) {
                        break;
                    }
                    if ((curr.y + 1) * l->width + curr.x ==
                        l->width * l->height - 1) {
                        push_Dir(&path, Down);
                        return path;
                    }
                    avail[count] = Down;
                    count++;
                    break;
                case Right:
                    if (curr.x + 1 == l->width || came_from == Right) {
                        break;
                    }
                    if (l->cells[curr.y * l->width + curr.x + 1]) {
                        break;
                    }
                    if (curr.y * l->width + curr.x + 1 ==
                        l->width * l->height - 1) {
                        push_Dir(&path, Right);
                        return path;
                    }
                    avail[count] = Right;
                    count++;
                    break;
                case Up:
                    if (!curr.y || came_from == Up) {
                        break;
                    }
                    if (l->cells[(curr.y - 1) * l->width + curr.x]) {
                        break;
                    }
                    avail[count] = Up;
                    count++;
                    break;
                case Left:
                    if (!curr.x || came_from == Left) {
                        break;
                    }
                    if (l->cells[curr.y * l->width + curr.x - 1]) {
                        break;
                    }
                    avail[count] = Left;
                    count++;
                    break;
            }
        }
        next = 0;
        if (!count) {
            return zero;
        } else if (count == 1) {
            next = avail[0];
        } else {
            for (u64 i = 0; i < count; i++) {
                push_Dir(&path, avail[i]);
                Coord init = apply_path(curr, &path, 1);
                Vec_Dir res = solve(l, init, avail[i]);
                pop_Dir(&path);
                if (!res.len) {
                    continue;
                } else {
                    push_Dir(&path, avail[i]);
                    for (u64 i = 0; i < res.len; i++) {
                        push_Dir(&path, get_Dir(&res, i));
                    }
                    return path;
                }
            }
            return zero;
        }
        count = 0;
        push_Dir(&path, next);
        curr = apply_path(curr, &path, 1);
        came_from = Opposite(next);
    }

    return zero;
}

int main(void) {
    // printf("%u %u %u\n", sizeof(Labyrinth), sizeof(Coord), sizeof(Path));

    Vec_Dir d = (Vec_Dir){0, 0, 0};
    // Labyrinth l = (Labyrinth){LAB, 5, 5};
    Vec_Dir res = solve((Labyrinth*)&l, (Coord){0, 0}, 0);
    printf("res : %lu\n", res.len);
    print_Dirs(&res);
    // for (u64 i = 0; i < res.len; i++) {
    //     printf("%lu %u\n", i, res.data[i]);
    // }
    // printf("opp %u\n", Opposite(2));
    return 0;
}
