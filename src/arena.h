#ifndef ARENA_H
#define ARENA_H

typedef struct Arena {
    void* start;
    void* top;
    unsigned long size;
} Arena;

Arena* create_arena(unsigned long size);
void* arena_malloc(Arena* arena, unsigned long size);
void free_arena(Arena* arena);

#endif

#ifdef ARENA_IMPL
// #define ARENA_IMPL

typedef unsigned long un;

#include <stdlib.h>

Arena* create_arena(un size) {
    Arena* arena = (Arena*)malloc(sizeof(Arena));
    arena->start = malloc(size);
    arena->top = arena->start;
    arena->size = size;
    return arena;
}

un remaining_size(Arena* arena) {
    un diff = (un)arena->top - (un)arena->start;
    return arena->size - diff;
}

void* arena_malloc(Arena* arena, un size) {
    if (remaining_size(arena) < size) {
        return NULL;
    }

    void* res = arena->top;
    arena->top = (void*)((un)arena->top + size);
    return res;
}

void free_arena(Arena* arena) {
    free(arena->start);
    free(arena);
}

#endif  // ARENA_IMPL
