#ifndef VECTOR_H
#define VECTOR_H

#include "defines.h"

typedef struct Vector {
    void *data;
    u64 len;
    u64 capacity;
} Vector;

#include <stdlib.h>
#include <string.h>

#define Vec_Impl(type)                                                     \
    u64 closest_pow_2(u64 num) {                                           \
        u64 res = 8;                                                       \
        while (res < num) {                                                \
            res *= 2;                                                      \
        }                                                                  \
        return res;                                                        \
    }                                                                      \
    Vector create_with_capacity_##type(u64 capacity) {                     \
        u64 temp = closest_pow_2(capacity);                                \
        void *data = malloc(temp * sizeof(type));                          \
        memset(data, 0, temp * sizeof(type));                              \
        Vector vec = {data, 0, temp};                                      \
        return vec;                                                        \
    }                                                                      \
    void push_##type(Vector *v, type value) {                              \
        if (v->capacity > v->len) {                                        \
            type *temp = (type *)v->data;                                  \
            temp[v->len] = value;                                          \
            v->len += 1;                                                   \
            return;                                                        \
        }                                                                  \
                                                                           \
        void *old_data = v->data;                                          \
        v->data = malloc(2 * v->len * sizeof(type));                       \
        memcpy(v->data, old_data, v->len * sizeof(type));                  \
        free(old_data);                                                    \
        v->capacity = v->len * 2;                                          \
                                                                           \
        memset((void *)((u64)v->data + v->len * sizeof(type)), 0, v->len); \
        type *temp = (type *)v->data;                                      \
        temp[v->len] = value;                                              \
        v->len += 1;                                                       \
                                                                           \
        return;                                                            \
    }                                                                      \
    int insert_##type(Vector *v, type value, u64 index) {                  \
        if (index > v->len) {                                              \
            return -1;                                                     \
        }                                                                  \
        if (v->capacity - v->len == 0) {                                   \
            void *old_data = v->data;                                      \
            v->data = malloc(2 * v->len * sizeof(type));                   \
            memcpy(v->data, old_data, v->len * sizeof(type));              \
            free(old_data);                                                \
            v->capacity = v->len * 2;                                      \
        }                                                                  \
        void *src = (void *)((u64)v->data + index * sizeof(type));         \
        void *dest = (void *)((u64)src + sizeof(type));                    \
        memmove(dest, src, (v->len - index) * sizeof(type));               \
        type *temp = (type *)v->data;                                      \
        temp[index] = value;                                               \
        v->len += 1;                                                       \
        return 0;                                                          \
    }                                                                      \
    type pop_##type(Vector *v) {                                           \
        if (v->len == 0) {                                                 \
            return 0;                                                      \
        }                                                                  \
        type res = ((type *)v->data)[v->len - 1];                          \
        v->len -= 1;                                                       \
        if (v->len == 0) {                                                 \
            v->data = nullptr;                                             \
        }                                                                  \
        return res;                                                        \
    }                                                                      \
    type remove_##type(Vector *v, u64 index) {                             \
        if (index <= 0 || index >= v->len) {                               \
            puts("Incorrect Index!\n");                                    \
            return 0;                                                      \
        }                                                                  \
                                                                           \
        printf("%lu \n", v->len);                                          \
        type res = ((type *)v->data)[index];                               \
        void *src = (void *)((u64)v->data + (index + 1) * sizeof(type));   \
        memmove(src - sizeof(type), src, v->len - index);                  \
        v->len -= 1;                                                       \
        return res;                                                        \
    }                                                                      \
    type get_##type(Vector *v, u64 index) {                                \
        if (index < 0 || index >= v->len) {                                \
            puts("Incorrect Index\n");                                     \
            return 0;                                                      \
        }                                                                  \
        return ((type *)v->data)[index];                                   \
    }                                                                      \
    void delete_vec_##type(Vector *v) { free(v->data); }

#endif  // !VECTOR_H
