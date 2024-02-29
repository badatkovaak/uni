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

Vec_Impl(Dir);

// typedef struct {
//     Direction* dirs;
//     // Coord* coords;
//     u64 len;
// } Path;

static LAB[16] = {
    0,1,0,1,
    0,1,0,1,
    0,0,0,1,
    0,1,0,0,
};

apply_path(Coord init, Vector p){
    for (u64 i = 0; i < p.len; i++) {
        switch ((Dir)p.data[i]) {
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
}

Vector solveLabyrinth(Labyrinth l, Vector p) { 
    Coord init;
    if (!p.len) {
        init = (Coord) { 0, 0 };
    } else {
        init = apply_path((u64)0, p);
    }
    
    Coord curr = init;
    for (u64 i = 1; i < 5; i++){
        switch(i) {
            case Down:
                if (curr.y == l.height) {
                    break;
                }

        }
    }
    // u64 avail_paths_count = 
    // if 

    return (Path){0, 0}; 
}

int main(void) {
    
    // printf("%u %u %u\n", sizeof(Labyrinth), sizeof(Coord), sizeof(Path));
    if (true) {
    }
    return 0;
}