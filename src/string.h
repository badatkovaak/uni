#ifndef STRING_H
#define STRING_H

typedef struct String {
    char* str;
    unsigned long len;
    unsigned long capacity;
} String;

String create_from_null_term(const char* str);
String create(const char* str, unsigned long len);
String create_with_capacity(unsigned long capacity);
void str_push(String* str, char value);
char str_pop(String* str, unsigned long index);
void str_insert(String* str, unsigned long index, char value);
char str_remove(String* str, unsigned long index);
unsigned long str_delete(String* s);

#endif

#ifdef STRING_IMPL

#ifndef STR_MALLOC
#define STR_MALLOC(sz) malloc(sz)
#define STR_FREE(p) free(p)
#include <stdlib.h>
#endif

// #ifndef define(un)
// typedef unsigned long un;
// #endif  // !#define(un)

#include <string.h>

unsigned long closest_pow_2(unsigned long num) {
    unsigned long count = 0;
    unsigned long res = num;
    while (num % 2 == 0) {
        num /= 2;
        count++;
    }
    return res / num;
}

String create_from_null_term(const char* str) {
    size_t len = strlen(str);
    unsigned long close = closest_pow_2(len);
    if (close != len) {
        close *= 2;
    }
    char* chars = (char*)malloc(len);
}

String create(char* str, unsigned long len) {}
String create_with_capacity(unsigned long capacity) {}
void str_push(String* str, char value) {}
char str_pop(String* str, unsigned long index) {}
void str_insert(String* str, unsigned long index, char value) {}
char str_remove(String* str, unsigned long index) {}
unsigned long str_delete(String* s) {}

#endif  // STRING_IMPL
