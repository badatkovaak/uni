// Linked List
// typedef struct list list;
typedef struct list {
    void* data;
    struct list* next;
} list;

void push(list* first, void* data);

void insert_front(list* first, void* data);

void* pop(list* first);

void* remove_front(list* first);

list* create(void* data);

list* create_from_array(void** array, unsigned array_len);

void map(list* first, void (*func)(void*));

int delete_list(list* first);

#ifdef LIST_IMPLEMENTATION

// #include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long un;

list* create(void* data) {
    list* node = (list*)malloc(sizeof(list));
    node->data = data;
    node->next = NULL;
    return node;
}

void push(list* first, void* data) {
    printf("push : %lu %lu\n", first, data);
    list* temp = first;

    while (temp->next) {
        printf("it : %lu\n", (un)temp);
        temp = temp->next;
    }

    printf("done! %lu\n", (un)temp);

    list* node = (list*)malloc(sizeof(list));
    if (temp) {
        temp->next = node;
    }
    node->data = data;
    node->next = NULL;
}

void insert_front(list* first, void* data) {
    list* new_node = (list*)malloc(sizeof(list));

    new_node->data = first->data;
    new_node->next = first->next;

    first->data = data;
    first->next = new_node;
}

list* create_from_array(void** array, unsigned array_len) {
    list* curr_node;
    list* prev_node = NULL;

    for (int i = array_len; i > 0; i--) {
        curr_node = (list*)malloc(sizeof(list));
        curr_node->data = array[i - 1];
        curr_node->next = prev_node;
        prev_node = curr_node;
        printf("%d : %lu %lu %lu\n", i - 1, (un)(prev_node->data),
               (un)(prev_node->next), (un)prev_node);
    }

    return curr_node;
}

void* remove_front(list* first) {
    void* res = first->data;
    list* temp = first->next;
    first->data = temp->data;
    first->next = temp->next;
    free(temp);
    return res;
}

void* pop(list* first) {
    list* node = first;

    while (node && node->next && (node->next)->next) {
        node = node->next;
    }

    void* res = NULL;
    printf("pop - %lu %lu\n", (un)node, (un)node->next);
    if (node->next) {
        res = (node->next)->data;
        free(node->next);
        node->next = NULL;
    } else {
        res = node->data;
        free(node);
        // first = NULL;
    }
    return res;
}

void map(list* first, void (*func)(void*)) {
    list* node = first;

    while (node) {
        func(node->data);
        node = node->next;
    }
}

#endif  // LIST_IMPLEMENTATION
