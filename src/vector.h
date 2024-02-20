#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
    void* data;
    unsigned long len;
    unsigned long capacity;
} Vector;

#endif  // !VECTOR_H

#ifdef VEC_IMPL

#include <string.h>
// clang-format off
#define Vec_Impl(type)\
    \
    unsigned long closest_pow_2(unsigned long num) {\
        unsigned long res = num;\
        while (num % 2 == 0) {\
            num /= 2;\
        }\
        return res / num;\
    }\
    \
    Vector create_empty_##type() {\
    \
    }\
    \
    Vector create_with_capacity_##type(unsigned long capacity) {\
        unsigned long temp = closest_pow_2(capacity);\
        if (temp != capacity) {\
            temp *= 2;\
        }\
        void* data = malloc(temp * sizeof(type));\
        memset(data, 0, temp * sizeof(type));\
        Vector vec = {data, 0, temp};\
        return vec;\
    }\
    \
    void push_##type(Vector * v, type value) {\
        if (v->capacity > v->len) {\
            type* temp = (type *)v->data;\
            temp[v->len] = value;\
            v->len += 1;\
            return;\
        }\
        \
        v->data = realloc(v->data, v->len * 2);\
        v->capacity = v->len * 2;\
        memset((void*)((unsigned long)v->data + v->len*sizeof(type)), 0, v->len)\
        type* temp = (type *)v->data;\
        temp[v->len] = value;\
        v->len += 1;\
        return;\
    }\
    \
    type pop_##type(Vector* v) {\
        if (v->len == 0){\
            return 0;\
        }\
        type* temp = (type*)v->data;\
        type res = temp[v->len - 1];\
        v->len--;\
        if (v->len == 0) {\
            v->data = NULL;\
        }\
        return res;\
    }

// clang-format on

#endif  // VEC_IMPL
