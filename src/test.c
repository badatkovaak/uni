#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define LIST_IMPLEMENTATION ;
#include "list.h"

typedef unsigned long un;

void print_un(void* d) { printf("val : %lu\n", *((un*)d)); }

int main(void) {
    // printf("size : %lu\n", sizeof(list));
    const size_t array_len = 10;
    un** a = (un**)malloc(sizeof(un) * array_len);
    for (un i = 0; i < array_len; i++) {
        un* b = (un*)malloc(sizeof(un));
        *b = i;
        a[i] = b;
    }
    list* l = create(a[0]);
    printf("l : %lu %lu %lu\n", (un)l, (un)l->data, (un)l->next);

    for (un i = 1; i < array_len; i++) {
        push(l, a[i]);
    }

    // list* l = create_from_array((void**)a, array_len);
    printf("l : %lu %lu %lu\n", (un)l, (un)l->data, (un)l->next);
    push(l, a[0]);
    map(l, &print_un);
    list* node = l;
    printf("\n\n");
    while (node) {
        printf("%lu %lu %lu \n", *(un*)(node->data), (un)node->next, (un)node);
        node = node->next;
    }
    for (un i = 0; i < 11; i++) {
        un* res = (un*)pop(l);
        printf("poped : %lu , %lu\n", (un)res, (un)l);
    }
    for (un i = 0; i < array_len; i++) {
        free(a[i]);
    }
    free(a);

    return EXIT_SUCCESS;
}
