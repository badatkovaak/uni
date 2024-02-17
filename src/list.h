// Linked List

typedef struct list {
    void* data;
    struct list* next;
} list;

void push(list* first, void* data);

void insert(list* first, unsigned index, void* data);

void insert_front(list* first, void* data);

void* pop(list* first);

void* remove_front(list* first);

list* create_node(void* data);

list* create_from_array(void** array, unsigned array_len);

void map(list* first, void (*func)(void*));

void delete_list(list* first);

#ifdef LIST_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef unsigned long un;

void push(list* first, void* data) {
    list* temp = first;

    while (temp->next) {
        temp = temp->next;
    }

    list* node = (list*)malloc(sizeof(list));
    if (temp) {
        temp->next = node;
    }
    node->data = data;
    node->next = NULL;
}

void insert(list* first, unsigned index, void* data) {
    list* prev = NULL;
    list* curr = first;
    unsigned count = 0;

    while (curr && count < index) {
        prev = curr;
        curr = curr->next;
        count += 1;
    }

    if (count != index) {
        printf("Incorrect index\n");
        return;
    }

    list* node = (list*)malloc(sizeof(list));
    if (prev) {
        node->data = data;
        node->next = curr;
        prev->next = node;
    } else {
        node->data = first->data;
        node->next = first->next;
        first->data = data;
        first->next = node;
    }
}

void insert_front(list* first, void* data) {
    list* new_node = (list*)malloc(sizeof(list));

    new_node->data = first->data;
    new_node->next = first->next;

    first->data = data;
    first->next = new_node;
}

list* create_node(void* data) {
    list* node = (list*)malloc(sizeof(list));
    node->data = data;
    node->next = NULL;
    return node;
}

list* create_from_array(void** array, unsigned array_len) {
    list* curr_node;
    list* prev_node = NULL;

    for (int i = array_len; i > 0; i--) {
        curr_node = (list*)malloc(sizeof(list));
        curr_node->data = array[i - 1];
        curr_node->next = prev_node;
        prev_node = curr_node;
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
    if (node->next) {
        res = (node->next)->data;
        free(node->next);
        node->next = NULL;
    } else {
        res = node->data;
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

void delete_list(list* first) {
    list* prev = first;
    list* curr = first->next;

    while (curr) {
        free(prev);
        prev = curr;
        curr = curr->next;
    }
    free(prev);
}

#endif  // LIST_IMPLEMENTATION
