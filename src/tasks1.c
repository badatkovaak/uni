#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

void print_buf(char* buf, size_t len) {
    for (u64 i = 0; i < len; i++) {
        if (buf[i] != '\0') {
            printf("%c", buf[i]);
        } else {
            printf("\\0");
        }
    }
    printf("\n");
}

int is_correct(char* buffer, size_t len) {
    if (len % 2 != 0 || buffer[0] == ')') {
        printf("Path1\n");
        return -1;
    }
    size_t slen = (len) / 2;
    char* stack = (char*)malloc(slen);
    memset(stack, 57, slen);
    size_t stack_ptr = 0;
    for (u64 i = 0; i < len; i++) {
        printf("Iter %lu : ", i);
        print_buf(stack, slen);
        switch (buffer[i]) {
            case '(':
                stack[stack_ptr] = '(';
                stack_ptr++;
                if (stack_ptr >= slen && buffer[i + 1] != ')') {
                    return -1;
                }
                break;
            case ')':
                if (stack[stack_ptr - 1] != '(') {
                    return -1;
                }
                stack_ptr--;
                break;
            default:
                return -1;
        }
    }
    free(stack);
    if (stack_ptr) {
        return -1;
    }
    return 0;
}

int is_correct1(char* buffer, size_t len) {
    if (len % 2 != 0 || buffer[0] == ')') {
        printf("Path1\n");
        return -1;
    }
    size_t slen = (len) / 2;
    size_t stack_ptr = 0;
    for (u64 i = 0; i < len; i++) {
        switch (buffer[i]) {
            case '(':
                stack_ptr++;
                if (stack_ptr >= slen && buffer[i + 1] != ')') {
                    return -1;
                }
                break;
            case ')':
                stack_ptr--;
                break;
            default:
                return -1;
        }
    }
    if (stack_ptr) {
        return -1;
    }
    return 0;
}

int main(void) {
    size_t len = 64;
    char* buff = malloc(len);
    memset(buff, '8', len);
    for (;;) {
        printf("Iter \n");
        size_t read_len = getline(&buff, &len, stdin);
        printf("read_len = %lu , %d %d \n", read_len,
               buff[read_len - 1] == '\n', buff[read_len - 1] == '\0');
        print_buf(buff, len);
        int ans = -1;
        if (read_len > 1) {
            ans = is_correct1(buff, read_len - 1);
        }
        printf("Ans : %d\n", ans);
    }
    return 0;
}
