#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

#include "defines.h"

#define Tree_Decl(type)     \
    typedef struct {        \
        type data;          \
        Vec_voids children; \
    } Node_##type;

#define Tree_Impl(type)                                               \
    Node_##type* create_node_##type(type data, Vec_voids* children) { \
        Node_##type* n = malloc(sizeof(Node_##type));                 \
        n->data = data;                                               \
        n->children = *children;                                      \
        return n;                                                     \
    }                                                                 \
                                                                      \
    Node_##type* create_leaf_##type(type data) {                      \
        Node_##type* l = malloc(sizeof(Node_##type));                 \
        l->data = data;                                               \
        l->children = (Vec_voids){nullptr, 0, 0};                     \
        return l;                                                     \
    }                                                                 \
                                                                      \
    int add_children_##type(Node_##type* root, Node_##type* new) {    \
        if (root->children.data == nullptr) {                         \
            return -1;                                                \
        }                                                             \
        push_voids(&root->children, (voids) new);                     \
        return 0;                                                     \
    }                                                                 \
                                                                      \
    int is_leaf_##type(Node_##type* node) {                           \
        return node->children.data == nullptr;                        \
    }

#endif  // !TREE_H
