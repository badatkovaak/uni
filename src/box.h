#ifndef BOX_H
#define BOX_H

#define Box_Decl(type) \
    typedef struct {   \
        type* data;    \
        u64 len;       \
    } Box_##type;

#endif  // !BOX_H
