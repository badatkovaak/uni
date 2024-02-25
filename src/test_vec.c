#include <stdio.h>
#include <stdlib.h>

#define VEC_IMPL
#include "defines.h"
#include "option.h"
#include "vector.h"

Vec_Impl(u64);
Option(u64);
Option_Impl(u64);

int main(void) {
    Vector vec = create_with_capacity_u64(10);
    printf("Hi There %lu %lu %lu\n", (u64)vec.data, vec.len, vec.capacity);
    for (u64 i = 0; i < 30; i++) {
        push_u64(&vec, i);
    }
    printf("Hi There %lu %lu %lu\n", (u64)vec.data, vec.len, vec.capacity);
    u64 l = pop_u64(&vec);
    insert_u64(&vec, l, vec.len);
    for (u64 i = 0; i < vec.len; i++) {
        printf("%lu : %lu\n", i, get_u64(&vec, i));
    }
    delete_vec_u64(&vec);
    return EXIT_SUCCESS;
}
