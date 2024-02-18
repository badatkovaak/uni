#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long un;

typedef unsigned char unchar;

typedef struct {
    unchar *data;
    size_t len;
    size_t capacity;
    // size_t elem_size;
} vector;

bool isPowerOf(un num, un base) {
    while (num % base == 0) {
        num /= base;
    }
    return (num == 1);
}

void printVec(vector *v) {
    for (un i = 0; i < v->len; i++) {
        printf("%d ", v->data[i]);
    }
    printf("\n%zu , %zu \n", v->len, v->capacity);
}

vector createVec(unchar *data, size_t len) {
    unchar *vecdata = (unchar *)malloc(len);
    memcpy(vecdata, data, len);
    vector vec = {vecdata, len, len};
    return vec;
}

void resizeVec(vector *v, size_t size) {
    if (v->capacity == size) {
        return;
    }
    v->data = (unchar *)realloc(v->data, size);
    v->capacity = size;
}

void pushToVec(vector *v, unchar elem) {
    if (v->capacity > v->len) {
        v->data[v->len] = elem;
        v->len += 1;
    } else {
        v->data = (unchar *)realloc(v->data, v->len * 2);
        v->capacity = v->len * 2;
        for (un i = v->len; i < v->capacity; i++) {
            v->data[i] = 0;
        }
        v->data[v->len] = elem;
        v->len += 1;
    }
}

unchar popFromVec(vector *v, unchar elem) {
    unchar res = v->data[v->len - 1];
    v->len -= 1;
    if (2 * v->capacity < v->len) {
        v->data = (unchar *)realloc(v->data, v->len / 2);
        v->capacity = v->len / 2;
    }
    return res;
}

// void insertIntoVec(vector *v, size_t index, unchar elem)
// {
//     for (un i = v->len; i > index; i--)
//     {
//     }
// }

vector vecWithCapacity(size_t capacity) {
    unchar *data = (unchar *)malloc(capacity);
    vector v = {data, 0, capacity};
    return v;
}

int main() {
    const un N = 10;
    unchar *data = malloc(N);

    for (un i = 0; i < N; i++) {
        data[i] = i;
    }

    vector v = createVec(data, N);

    free(data);
    printVec(&v);
    pushToVec(&v, 11);
    printVec(&v);

    return 0;
}
