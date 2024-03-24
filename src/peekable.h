#ifndef PEEKABLE_H
#define PEEKABLE_H

#include "defines.h"
#include "option.h"

#define Peekable_Decl(type) \
    typedef struct {        \
        type* data;         \
        u64 len;            \
        u64 pos;            \
    } Peekable_##type;

#define Peekable_Impl(type)                                       \
                                                                  \
    type peek_or_default_##type(Peekable_##type* p, type value) { \
        if (p->len - p->pos > 2) {                                \
            return p->data[p->pos + 1];                           \
        } else {                                                  \
            return value;                                         \
        }                                                         \
    }                                                             \
                                                                  \
    Option_##type peek_##type(Peekable_##type* p) {               \
        if (p->len - p->pos > 2) {                                \
            return pure_##type(p->data[p->pos + 1]);              \
        } else {                                                  \
            return none_##type();                                 \
        }                                                         \
    }                                                             \
                                                                  \
    Option_##type next_##type(Peekable_##type* p) {               \
        if (p->len - p->pos > 1) {                                \
            p->pos += 1;                                          \
            return pure_##type(p->data[p->pos]);                  \
        } else {                                                  \
            return none_##type();                                 \
        }                                                         \
    }

#endif  // !PEEKABLE_H
