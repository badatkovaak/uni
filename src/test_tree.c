#include <stdio.h>
#include <string.h>

#include "box.h"
#include "tree.h"

#define VEC_TO_BOX
#include "vector.h"

typedef char* chars;

Box_Decl(chars);

Vec_Decl(chars);
Vec_Impl(chars);
Vec_To_Box(chars);

Tree_Decl(chars);
Tree_Impl(chars);

Box_chars split_at(char* str, char sep) {
    Vec_chars res = create_with_capacity_chars(8);
    u64 i = 0;
    u64 prev = 0;
    while (str[i] != 0) {
        if (str[i] == sep) {
            void* p = malloc(i - prev + 1);
            memcpy(p, str + prev, i - prev);
            ((char*)p)[i - prev] = '\0';
            push_chars(&res, p);
            i++;
            prev = i;
        }
        i++;
    }
    if (prev != i) {
        void* p = malloc(i - prev + 1);
        memcpy(p, str + prev, i - prev);
        ((char*)p)[i - prev] = '\0';
        push_chars(&res, p);
    }
    return vec_to_box_chars(&res);
}

int main(void) {
    Box_chars v = split_at("/ab/cd/ef", '/');
    for (u64 i = 0; i < v.len; i++) {
        printf("i: %lu , s: %s\n", i, v.data[i]);
    }
    return 0;
}
