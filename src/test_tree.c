#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "box.h"
#include "tree.h"

#define VEC_TO_BOX
#include "vector.h"

Box_Decl(chars);

Vec_Decl(chars);
Vec_Impl(chars);
Vec_To_Box(chars);

Vec_Decl(voids);
Vec_Impl(voids);

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

Node_chars* add_file(Node_chars* root, char* data) {
    // void* dest = malloc(sizeof(Node_chars));
    Node_chars* n = create_leaf_chars(data);
    add_children_chars(root, n);
    return n;
}

Node_chars* add_dir(Node_chars* root, char* data) {
    void* dest = malloc(sizeof(Node_chars));
    Node_chars* n =
        create_node_chars(data, create_with_capacity_into_voids(0, dest));
    add_children_chars(root, n);
    return n;
}

void print_tree_chars(Node_chars* root, int level) {
    char* buffer = "";
    if (level != -1) {
        buffer = malloc(level + 1);
        memset(buffer, '\t', level);
        buffer[level] = '\0';
    }
    printf("%s", buffer);
    if (!is_leaf_chars(root)) {
        printf("/");
    }
    printf("%s\n", root->data);
    for (u64 i = 0; i < root->children.len; i++) {
        print_tree_chars(root->children.data[i], level + 1);
    }
}

int main(void) {
    Box_chars v = split_at("/ab/cd/ef", '/');
    for (u64 i = 0; i < v.len; i++) {
        printf("i: %lu , s: %s\n", i, v.data[i]);
    }
    void* dest = malloc(sizeof(Vec_chars));
    Node_chars* root =
        create_node_chars("", create_with_capacity_into_voids(0, dest));
    Node_chars* home = add_dir(root, "home");
    Node_chars* user = add_dir(home, "user");
    Node_chars* documents = add_dir(user, "Documents");
    Node_chars* bashrc = add_file(user, ".bashrc");
    Node_chars* var = add_dir(root, "var");
    Node_chars* root1 = add_dir(root, "root");
    print_tree_chars(root, 0);
    return 0;
}
