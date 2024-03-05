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

// clang-format on

void print_Dirs(Vector_Dir* v) {
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

Coord apply_path(Coord init, Vector_Dir* p, u64 start) {
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

    printf("\n-------------\nInstance : %u %u\n", curr.x, curr.y);
    print_Dirs(d);

    for (;;) {
        printf("coords %u %u came : %u\n", curr.x, curr.y, came_from);
        print_Dirs(&walked);
        for (u64 i = 1; i < 5; i++) {
            switch (i) {
                case Down:
                    if (curr.y + 1 == l->height || came_from == Down) {
                        printf("Down %u\n", curr.y);
                        break;
                    }
                    if (l->cells[(curr.y + 1) * l->width + curr.x]) {
                        printf("Down Cell %u %u %u\n",
                               l->cells[(curr.y + 1) * l->width + curr.x],
                               curr.x, curr.y);
                        break;
                    }
                    if ((curr.y + 1) * l->width + curr.x ==
                        l->width * l->height - 1) {
                        printf("Down Is The End %u %u %u %u\n",
                               l->width * l->height - 1,
                               (curr.y + 1) * l->width + curr.x, curr.x,
                               curr.y);
                        push_Dir(&walked, Down);
                        print_Dirs(&walked);
                        print_Dirs(d);
                        for (u64 i = 0; i < d->len; i++) {
                            insert_Dir(&walked, get_Dir(d, d->len - i - 1), 0);
                        }
                        return walked;
                    }
                    avail[count] = Down;
                    count++;
                    break;
                case Right:
                    if (curr.x + 1 == l->width || came_from == Right) {
                        printf("Right %u\n", curr.x);
                        break;
                    }
                    if (l->cells[curr.y * l->width + curr.x + 1]) {
                        printf("Right Cell\n");
                        break;
                    }
                    if (curr.y * l->width + curr.x + 1 ==
                        l->width * l->height - 1) {
                        printf("Right Is The End %u %u %u %u\n",
                               l->width * l->height - 1,
                               curr.y * l->width + curr.x + 1, curr.x, curr.y);
                        push_Dir(&walked, Right);
                        print_Dirs(&walked);
                        print_Dirs(d);
                        for (u64 i = 0; i < d->len; i++) {
                            insert_Dir(&walked, get_Dir(d, d->len - i - 1), 0);
                        }
                        return walked;
                    }
                    avail[count] = Right;
                    count++;
                    break;
                case Up:
                    if (!curr.y || came_from == Up) {
                        printf("Up %u\n", curr.y);
                        break;
                    }
                    if (l->cells[(curr.y - 1) * l->width + curr.x]) {
                        printf("Up Cell\n");
                        break;
                    }
                    avail[count] = Up;
                    count++;
                    break;
                case Left:
                    if (!curr.x || came_from == Left) {
                        printf("Left %u\n", curr.x);
                        break;
                    }
                    if (l->cells[curr.y * l->width + curr.x - 1]) {
                        printf("Left Cell\n");
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
        } else if (count == 1) {
            printf("avail %u\n", avail[0]);
            next = avail[0];
        } else {
            for (u64 i = 0; i < count; i++) {
                printf("New Instance : %u\n", avail[i]);
                // push_Dir(d, avail[i]);
                // print_Dirs(&walked);
                // push_Dir(&walked, avail[i]);
                Vector_Dir new = zero;
                for (u64 i = 0; i < d->len; i++) {
                    push_Dir(&new, get_Dir(d, d->len - i - 1));
                }
                for (u64 i = 0; i < walked.len; i++) {
                    push_Dir(&new, get_Dir(&walked, walked.len - i - 1));
                }
                push_Dir(&new, avail[i]);
                // print_Dirs(&new);
                Coord new_curr = apply_path(curr, &walked, 1);
                Vector_Dir res = solveLabyrinth(l, &new, new_curr);
                // pop_Dir(&walked);
                // pop_Dir(d);

                if (!res.len) {
                    puts("Here");
                    continue;
                } else {
                    puts("Res Path");
                    print_Dirs(&walked);
                    print_Dirs(&res);
                    print_Dirs(d);
                    // for (u64 i = 0; i < walked.len; i++) {
                    //     insert_Dir(&res, get_Dir(&walked, walked.len - i -
                    //     1),
                    //                0);
                    // }
                    return res;
                }
            }
            puts("Path 11");
            return zero;
        }
        printf("next : %u %u\n", next, came_from);
        push_Dir(&walked, next);
        // push_Dir(d, next);
        printf("walked : %lu\n", walked.len);
        count = 0;
        avail[0] = 0;
        avail[1] = 0;
        curr = apply_path(curr, &walked, 1);
        came_from = Opposite(next);
    }

    return zero;
}

Vector_Dir solve(Labyrinth* l, Coord curr, Dir last) {
    Vector_Dir zero = (Vector_Dir){0, 0, 0};
    Vector_Dir path = zero;
    Dir came_from = 0;
    u64 count = 0;
    Dir avail[4] = {0, 0, 0, 0};
    Dir next = 0;

    if (curr.x + curr.y == 0) {
        came_from = Up;
    } else {
        came_from = Opposite(last);
    }

    for (;;) {
        printf("coordinates - %u %u\n", curr.x, curr.y);
        for (u64 i = 1; i < 5; i++) {
            switch (i) {
                case Down:
                    if (curr.y + 1 == l->height || came_from == Down) {
                        printf("Down %u\n", curr.y);
                        break;
                    }
                    if (l->cells[(curr.y + 1) * l->width + curr.x]) {
                        printf("Down Cell %u %u %u\n",
                               l->cells[(curr.y + 1) * l->width + curr.x],
                               curr.x, curr.y);
                        break;
                    }
                    if ((curr.y + 1) * l->width + curr.x ==
                        l->width * l->height - 1) {
                        printf("Down Is The End %u %u %u %u\n",
                               l->width * l->height - 1,
                               (curr.y + 1) * l->width + curr.x, curr.x,
                               curr.y);
                        push_Dir(&path, Down);
                        return path;
                    }
                    avail[count] = Down;
                    count++;
                    break;
                case Right:
                    if (curr.x + 1 == l->width || came_from == Right) {
                        printf("Right %u\n", curr.x);
                        break;
                    }
                    if (l->cells[curr.y * l->width + curr.x + 1]) {
                        printf("Right Cell\n");
                        break;
                    }
                    if (curr.y * l->width + curr.x + 1 ==
                        l->width * l->height - 1) {
                        printf("Right Is The End %u %u %u %u\n",
                               l->width * l->height - 1,
                               curr.y * l->width + curr.x + 1, curr.x, curr.y);
                        push_Dir(&path, Right);
                        return path;
                    }
                    avail[count] = Right;
                    count++;
                    break;
                case Up:
                    if (!curr.y || came_from == Up) {
                        printf("Up %u\n", curr.y);
                        break;
                    }
                    if (l->cells[(curr.y - 1) * l->width + curr.x]) {
                        printf("Up Cell\n");
                        break;
                    }
                    avail[count] = Up;
                    count++;
                    break;
                case Left:
                    if (!curr.x || came_from == Left) {
                        printf("Left %u\n", curr.x);
                        break;
                    }
                    if (l->cells[curr.y * l->width + curr.x - 1]) {
                        printf("Left Cell\n");
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
                Vector_Dir res = solve(l, init, avail[0]);
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
        printf("next : %u\n", next);
        count = 0;
        push_Dir(&path, next);
        curr = apply_path(curr, &path, 1);
        came_from = Opposite(next);
    }

    return zero;
}

int main(void) {
    // printf("%u %u %u\n", sizeof(Labyrinth), sizeof(Coord), sizeof(Path));

    Vector_Dir d = (Vector_Dir){0, 0, 0};
    // Labyrinth l = (Labyrinth){LAB, 5, 5};
    Vector_Dir res = solve((Labyrinth*)&l, (Coord){0, 0}, 0);
    printf("res : %lu\n", res.len);
    print_Dirs(&res);
    // for (u64 i = 0; i < res.len; i++) {
    //     printf("%lu %u\n", i, res.data[i]);
    // }
    // printf("opp %u\n", Opposite(2));
    return 0;
}
