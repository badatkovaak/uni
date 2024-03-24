#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "defines.h"
#include "option.h"
#include "peekable.h"
#include "vector.h"

#define is_valid_token(t) (t >= 1 && t <= 8)
#define is_digit(c) (c >= 48 && c <= 57)

Option_Decl(char);
Option_Impl(char);
Option_Decl(i64);
Option_Impl(i64);
Peekable_Decl(char);
Peekable_Impl(char);

typedef enum {
    Plus = 1,
    Minus,
    Mult,
    Div,
    Power,
    LParen,
    RParen,
    IntLiteral,
} Token;

Vec_Decl(i64);
Vec_Impl(i64);
Vec_Decl(Token);
Vec_Impl(Token);

// typedef struct {
//     i64* data;
//     u64 len;
//     u64 pos;
// } LiteralBuffer;

typedef struct {
    char* buffer;
    u64 len;
    u64 pos;
    Vector_i64* lit;
} Lexer;

Option_i64 read_int_literal(Lexer* l) {
    u64 i = l->pos;
    u64 c = 0;

    char* buf = (char*)malloc(32);
    memset(buf, 0, 32);

    while (is_digit(l->buffer[i])) {
        buf[c] = l->buffer[i];
        if (c + 1 >= 31) {
            return none_i64();
        }
        c += 1;
        if (i + 1 >= l->len) {
            errno = 0;
            i64 res = strtol(buf, 0, 10);
            if (errno != 0) {
                return none_i64();
            }
            l->pos = i;
            return pure_i64(res);
        }
        i += 1;
    }
    errno = 0;
    i64 res = strtol(buf, 0, 10);
    if (errno != 0) {
        return none_i64();
    }
    l->pos = i - 1;
    return pure_i64(res);
}

int lex_int_literal(Lexer* l, Vector_Token* v) {
    if (l->buffer[l->pos] == '-') {
        if (l->pos + 1 >= l->len) {
            push_Token(v, Minus);
            return 0;
        }

        if (is_digit(l->buffer[l->pos + 1])) {
            goto res;
            //     l->pos += 1;
            //     Option_i64 i = read_int_literal(l);
            //     if (!i.is_present) {
            //         return -1;
            //     } else {
            //         push_Token(v, IntLiteral);
            //         push_i64(l->lit, i.value);
            //         return 0;
            //     }
        } else {
            push_Token(v, Minus);
            return 0;
        }
    } else {
    res:
        l->pos += 1;
        Option_i64 i = read_int_literal(l);
        if (!i.is_present) {
            return -1;
        } else {
            push_Token(v, IntLiteral);
            push_i64(l->lit, i.value);
            return 0;
        }
    }
    return -1;
}

Vector_Token lex(Lexer* l) {
    Vector_Token res = create_with_capacity_Token(16);
    for (u64 i = 0; i < l->len; i++) {
        char curr = l->buffer[i];
        if (curr == '-' || is_digit(curr)) {
            int r = lex_int_literal(l, &res);
        }
        switch (curr) {
            case '+':
                break;
            case '-':
                break;
            case '*':
                break;
            case '/':
                break;
            case '^':
                break;
            case '(':
                break;
            case ')':
                break;
            case ' ':
            case '\n':
            case '\t':
                break;
        }
    }
    return (Vector_Token){0, 0, 0};
}

int main(void) {
    static const u64 len = 256;
    struct pollfd fds[1] = {{0, POLLIN, 0}};

    for (;;) {
        char buffer[len];
        memset(buffer, 0, len);
        poll(fds, 1, 50000);

        if (fds[0].revents & POLLIN) {
            read(0, buffer, len - 1);
            printf("%s\n", buffer);
        }
    }

    return 0;
}
