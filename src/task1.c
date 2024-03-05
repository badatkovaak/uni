#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

#define is_opening(t) (t == '(' || t == '[' || t == '{' || t == '<')

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

int is_correct(char* buffer, u64 len) {
    if (len % 2 != 0 || buffer[0] == ')') {
        printf("Path1\n");
        return -1;
    }
    u64 slen = (len) / 2;
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

int is_correct1(char* buffer, u64 len) {
    if (len % 2 != 0 || buffer[0] == ')') {
        printf("Path1\n");
        return -1;
    }
    u64 slen = (len) / 2;
    u64 stack_ptr = 0;
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

int is_correct2(char* buffer, u64 len, u64 consumed, char type) {
    if (len % 2 != 0 && !is_opening(buffer[0])) {
        printf("Path1\n");
        return -1;
    }
    if (type == 0) {
        type = buffer[0];
    }
    u64 stack_ptr = 0;
    u64 cons = 0;
    char closing = type + 1 + (type != '(');
    for (u64 i = consumed; i < len; i++) {
        char b = buffer[i];
        printf("%lu %c %c\n", i, b, type);
        if (b == type) {
            stack_ptr++;
            cons++;
            if (stack_ptr >= (len / 2) && buffer[i + 1] != closing) {
                // printf("Path2\n");
                return -1;
            }
        } else if (b == closing) {
            stack_ptr--;
            cons++;
        } else if (b != type && is_opening(b)) {
            // printf("Path4\n");
            int res = is_correct2(buffer, len, consumed + cons, b);
            if ((res + 2) % 2 == 1 || res == 0 || res == -1) {
                // printf("Path3\n");
                return -1;
            } else {
                cons += res;
                i += res - 1;
            }
        } else {
            // puts("Path5");
            return -1;
        }
        // printf("%lu %lu %c\n", len, consumed + cons, type);
        if (!stack_ptr && consumed) {
            return cons;
        } else if (!stack_ptr && !consumed) {
            while (cons + consumed < len) {
                // printf("Path6\n");
                int res = is_correct2(buffer, len, consumed + cons, type);
                if ((res + 2) % 2 == 1 || res == 0) {
                    // printf("Path3\n");
                    return -1;
                } else {
                    cons += res;
                    if (cons == len) {
                        return cons;
                    }
                    i += res - 1;
                }
            }
            return cons;
        }
    }

    return cons;
}

int main(void) {
    size_t len = 64;
    char* buff = malloc(len);
    // printf("%d %d %d %d %d %d %d %d \n", '(', ')', '[', ']', '{', '}', '<',
    // '>');
    memset(buff, '8', len);
    for (;;) {
        printf("Iter \n");
        size_t read_len = getline(&buff, &len, stdin);
        printf("read_len = %lu , %d %d \n", read_len,
               buff[read_len - 1] == '\n', buff[read_len - 1] == '\0');
        // print_buf(buff, len);
        int ans = -1;
        if (read_len > 1) {
            ans = is_correct2(buff, read_len - 1, 0, 0);
        }
        printf("Ans : %d\n", ans);
    }
    return 0;
}
