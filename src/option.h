#ifndef OPTION_H
#define OPTION_H

#include "defines.h"
#define Option(type)    \
    typedef struct {    \
        u64 is_present; \
        type value;     \
    } Option_##type;

#define Option_Impl(type)                             \
    Option_##type pure_##type(type value) {           \
        return (Option_##type){1, value};             \
    }                                                 \
    type unwrap_unsafe_##type(Option_##type t) {      \
        if (!t.is_present) {                          \
            puts("Unwrapped Option None.");           \
            __builtin_trap();                         \
        }                                             \
        return t.value;                               \
    }                                                 \
    type unwrap_or_default(Option_##type t, type d) { \
        if (!t.is_present) {                          \
            return d;                                 \
        }                                             \
        return t.value;                               \
    }

#endif  // !OPTION_H
