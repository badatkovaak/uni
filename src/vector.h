#ifndef VECTOR_H
#define VECTOR_H

#include "defines.h"

#define Vec_Decl(type)             \
    typedef struct Vector_##type { \
        type *data;                \
        u64 len;                   \
        u64 capacity;              \
    } Vec_##type;

#include <stdlib.h>
#include <string.h>

#define Vec_Impl(type)                                                       \
    u64 closest_pow_2_##type(u64 num) {                                      \
        u64 res = 8;                                                         \
        while (res < num) {                                                  \
            res *= 2;                                                        \
        }                                                                    \
        return res;                                                          \
    }                                                                        \
                                                                             \
    Vec_##type create_with_capacity_##type(u64 capacity) {                   \
        u64 temp = closest_pow_2_##type(capacity);                           \
        void *data = malloc(temp * sizeof(type));                            \
        memset(data, 0, temp * sizeof(type));                                \
        return (Vec_##type){(type *)data, 0, temp};                          \
    }                                                                        \
                                                                             \
    Vec_##type create_from_array_##type(type *array, u64 len) {              \
        u64 temp = closest_pow_2_##type(len);                                \
        type *data = malloc(temp * sizeof(type));                            \
        for (u64 i = 0; i < len; i++) {                                      \
            data[i] = array[i];                                              \
        }                                                                    \
        return (Vec_##type){data, len, temp};                                \
    }                                                                        \
                                                                             \
    Vec_##type *create_with_capacity_into_##type(u64 capacity, void *dest) { \
        u64 temp = closest_pow_2_##type(capacity);                           \
        Vec_##type *v = (Vec_##type *)dest;                                  \
        v->data = malloc(temp * sizeof(type));                               \
        memset(v->data, 0, temp * sizeof(type));                             \
        v->len = 0;                                                          \
        v->capacity = temp;                                                  \
        return v;                                                            \
    }                                                                        \
                                                                             \
    Vec_##type *create_from_array_into_##type(type *array, u64 len,          \
                                              void *dest) {                  \
        u64 temp = closest_pow_2_##type(len);                                \
        Vec_##type *v = (Vec_##type *)dest;                                  \
        v->data = malloc(temp * sizeof(type));                               \
        v->len = len;                                                        \
        v->capacity = len;                                                   \
        for (u64 i = 0; i < len; i++) {                                      \
            v->data[i] = array[i];                                           \
        }                                                                    \
        return v;                                                            \
    }                                                                        \
                                                                             \
    void push_##type(Vec_##type *v, type value) {                            \
        if (!v->data) {                                                      \
            v->data = (type *)malloc(8 * sizeof(type));                      \
            v->capacity = 8;                                                 \
            v->data[0] = value;                                              \
            v->len = 1;                                                      \
            return;                                                          \
        }                                                                    \
        if (v->capacity > v->len) {                                          \
            v->data[v->len] = value;                                         \
            v->len += 1;                                                     \
            return;                                                          \
        }                                                                    \
                                                                             \
        void *old_data = v->data;                                            \
        v->data = (type *)malloc(2 * v->len * sizeof(type));                 \
        memcpy(v->data, old_data, v->len * sizeof(type));                    \
        free(old_data);                                                      \
        v->capacity = v->len * 2;                                            \
                                                                             \
        memset((void *)((u64)v->data + v->len * sizeof(type)), 0, v->len);   \
        v->data[v->len] = value;                                             \
        v->len += 1;                                                         \
                                                                             \
        return;                                                              \
    }                                                                        \
                                                                             \
    int insert_##type(Vec_##type *v, type value, u64 index) {                \
        if (index > v->len) {                                                \
            return -1;                                                       \
        }                                                                    \
        if (!v->data && index) {                                             \
            return -1;                                                       \
        }                                                                    \
        if (!v->data) {                                                      \
            v->data = (type *)malloc(8 * sizeof(type));                      \
            v->capacity = 8;                                                 \
            v->data[0] = value;                                              \
            v->len = 1;                                                      \
            return 0;                                                        \
        }                                                                    \
        if (v->capacity - v->len == 0) {                                     \
            void *old_data = v->data;                                        \
            v->data = (type *)malloc(2 * v->len * sizeof(type));             \
            memcpy(v->data, old_data, v->len * sizeof(type));                \
            free(old_data);                                                  \
            v->capacity = v->len * 2;                                        \
        }                                                                    \
        void *src = (void *)((u64)v->data + index * sizeof(type));           \
        void *dest = (void *)((u64)src + sizeof(type));                      \
        memmove(dest, src, (v->len - index) * sizeof(type));                 \
        v->data[index] = value;                                              \
        v->len += 1;                                                         \
        return 0;                                                            \
    }                                                                        \
                                                                             \
    type pop_##type(Vec_##type *v) {                                         \
        if (v->len == 0) {                                                   \
            puts("Trying to pop from empty vector");                         \
            __builtin_trap();                                                \
        }                                                                    \
        type res = v->data[v->len - 1];                                      \
        v->len -= 1;                                                         \
        if (v->len == 0) {                                                   \
            v->data = nullptr;                                               \
        }                                                                    \
        return res;                                                          \
    }                                                                        \
                                                                             \
    type remove_##type(Vec_##type *v, u64 index) {                           \
        if (index <= 0 || index >= v->len) {                                 \
            puts("Trying to remove incorrect Index!");                       \
            __builtin_trap();                                                \
        }                                                                    \
                                                                             \
        printf("%lu \n", v->len);                                            \
        type res = v->data[index];                                           \
        void *src = (void *)((u64)v->data + (index + 1) * sizeof(type));     \
        memmove((void *)((u64)src - sizeof(type)), src, v->len - index);     \
        v->len -= 1;                                                         \
        return res;                                                          \
    }                                                                        \
                                                                             \
    type get_##type(Vec_##type *v, u64 index) {                              \
        if (index >= v->len) {                                               \
            puts("Incorrect Index");                                         \
            __builtin_trap();                                                \
        }                                                                    \
        return v->data[index];                                               \
    }                                                                        \
                                                                             \
    void delete_vec_##type(Vec_##type *v) { free(v->data); }

#ifdef VEC_TO_BOX

#include "box.h"

#define Vec_To_Box(type)                          \
    Box_##type vec_to_box_##type(Vec_##type *v) { \
        return (Box_##type){v->data, v->len};     \
    }

#endif  // VEC_TO_BOX

#endif  // !VECTOR_H
