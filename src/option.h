#ifndef OPTION_H
#define OPTION_H

#include "defines.h"
#define Option(type)    \
    typedef struct {    \
        u64 is_present; \
        type value;     \
    } option_##type;

#define Option_Impl(type)                             \
    type unwrap_unsafe_##type(option_##type t) {      \
        if (!t.is_present) {                          \
            puts("Unwrapped Option None.");           \
            char x = *(volatile char*)0;              \
            return 0;                                 \
        }                                             \
        return t.value;                               \
    }                                                 \
    type unwrap_or_default(option_##type t, type d) { \
        if (!t.is_present) {                          \
            return d;                                 \
        }                                             \
        return t.value;                               \
    }
// type

#endif  // !OPTION_H
