#ifndef ITERABLE_H
#define ITERABLE_H

#define Iterable_Decl(type) \
    typedef struct {        \
        type* data;         \
        u64 len;            \
        u64 pos;            \
    } Iter_##type;

#define Iterable_Impl(type)

#endif  // !ITERABLE_H
