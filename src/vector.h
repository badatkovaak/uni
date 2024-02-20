#ifndef VECTOR_H
#define VECTOR_H

#include "defines.h"

typedef struct Vector {
    void* data;
    u64 len;
    u64 capacity;
} Vector;

#include <stdlib.h>
#include <string.h>

#define Vec_Impl(type)                                                    \
    u64 closest_pow_2(u64 num) {                                          \
        u64 res = num;                                                    \
        while (num % 2 == 0) {                                            \
            num /= 2;                                                     \
        }                                                                 \
        return res / num;                                                 \
    }                                                                     \
    Vector create_with_capacity_##type(u64 capacity) {                    \
        u64 temp = closest_pow_2(capacity);                               \
        if (temp != capacity) {                                           \
            temp *= 2;                                                    \
        }                                                                 \
        void* data = malloc(temp * sizeof(type));                         \
        memset(data, 0, temp * sizeof(type));                             \
        Vector vec = {data, 0, temp};                                     \
        return vec;                                                       \
    }                                                                     \
    void push_##type(Vector* v, type value) {                             \
        if (v->capacity > v->len) {                                       \
            type* temp = (type*)v->data;                                  \
            temp[v->len] = value;                                         \
            v->len += 1;                                                  \
            return;                                                       \
        }                                                                 \
        v->data = realloc(v->data, v->len * 2);                           \
        v->capacity = v->len * 2;                                         \
        memset((void*)((u64)v->data + v->len * sizeof(type)), 0, v->len); \
        type* temp = (type*)v->data;                                      \
        temp[v->len] = value;                                             \
        v->len += 1;                                                      \
        return;                                                           \
    }                                                                     \
    type pop_##type(Vector* v) {                                          \
        if (v->len == 0) {                                                \
            return 0;                                                     \
        }                                                                 \
        type* temp = (type*)v->data;                                      \
        type res = temp[v->len - 1];                                      \
        v->len--;                                                         \
        if (v->len == 0) {                                                \
            v->data = nullptr;                                            \
        }                                                                 \
        return res;                                                       \
    }

#endif  // !VECTOR_H
