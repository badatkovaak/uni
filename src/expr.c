#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "defines.h"
#include "iterable.h"
#include "option.h"
#include "vector.h"

#define is_valid_token(t) (t >= 1 && t <= 8)
#define is_digit(c) (c >= 48 && c <= 57)
#define is_binary_op(c) \
    (c == Plus || c == Minus || c == Mult || c == Div || c == Power)
#define precedence(c) ((c - 1) / 2)

#pragma clang diagnostic ignored "-Wextra-semi"

Option_Decl(char);
Option_Impl(char);
Option_Decl(i64);
Option_Impl(i64);

typedef enum {
    Plus = 1,
    Minus,
    Mult,
    Div,
    Power,
    LParen,
    RParen,
    IntLiteral,
    // Symbol,
} TokenType;

typedef struct {
    TokenType type;
    long int_val;  // };
} Token;

Vec_Decl(i64);
Vec_Impl(i64);
Vec_Decl(Token);
Vec_Impl(Token);

Iterable_Decl(Token);

typedef struct {
    char* buffer;
    u64 len;
    u64 pos;
} Lexer;

typedef struct {
    TokenType type;
    void* left;
    void* right;
} BinaryOp;

typedef struct {
    TokenType type;
    long value;
} Literal;

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

int lex_int_literal(Lexer* l, Vec_Token* v) {
    if (l->buffer[l->pos] == '-') {
        if (l->pos + 1 >= l->len) {
            push_Token(v, (Token){Minus, 0});
            return 0;
        }
        if (is_digit(l->buffer[l->pos + 1])) {
            l->pos += 1;
            Option_i64 i = read_int_literal(l);
            if (!i.is_present) {
                return -1;
            } else {
                push_Token(v, (Token){IntLiteral, -i.value});
                return 0;
            }
        } else {
            push_Token(v, (Token){Minus, 0});
            return 0;
        }
    } else {
        Option_i64 i = read_int_literal(l);
        if (!i.is_present) {
            return -1;
        } else {
            push_Token(v, (Token){IntLiteral, i.value});
            return 0;
        }
    }
    return -1;
}

Vec_Token lex(Lexer* l) {
    Vec_Token res = create_with_capacity_Token(16);
    for (; l->pos < l->len; l->pos++) {
        char curr = l->buffer[l->pos];
        if (curr == '-' || is_digit(curr)) {
            int r = lex_int_literal(l, &res);
            if (r) {
                return (Vec_Token){0, 0, 0};
            }
            continue;
        }
        switch (curr) {
            case '+':
                push_Token(&res, (Token){Plus, 0});
                break;
            case '-':
                push_Token(&res, (Token){Minus, 0});
                break;
            case '*':
                push_Token(&res, (Token){Mult, 0});
                break;
            case '/':
                push_Token(&res, (Token){Div, 0});
                break;
            case '^':
                push_Token(&res, (Token){Power, 0});
                break;
            case '(':
                push_Token(&res, (Token){LParen, 0});
                break;
            case ')':
                push_Token(&res, (Token){RParen, 0});
                break;
            case ' ':
            case '\n':
            case '\t':
                break;
        }
    }
    return res;
}

void pretty_print_tok(Token t) {
    switch (t.type) {
        case Plus:
            printf("+ ");
            break;
        case Minus:
            printf("- ");
            break;
        case Mult:
            printf("* ");
            break;
        case Div:
            printf("/ ");
            break;
        case Power:
            printf("^ ");
            break;
        case LParen:
            printf("( ");
            break;
        case RParen:
            printf(") ");
            break;
        case IntLiteral:
            printf("%li ", t.int_val);
            break;
    }
}

void pretty_print(Vec_Token* v) {
    for (u64 i = 0; i < v->len; i++) {
        Token t = v->data[i];
        pretty_print_tok(t);
    }
    printf("\n");
}

int parse_expr(Vec_Token* table, Vec_Token* v, u64 pos, u8 prec);
int parse_term(Vec_Token* table, Vec_Token* input, u64 pos);

int parse_term(Vec_Token* table, Vec_Token* input, u64 pos) {
    Token c = input->data[pos];
    if (c.type == LParen) {
        int res = parse_expr(table, input, pos + 1, 0);
        if (res == -1) {
            return -1;
        }
        if (input->data[pos + 1 + res].type == RParen) {
            return 2 + res;
        }
    } else if (c.type == IntLiteral) {
        push_Token(table, c);
        return 1;
    }
    return -1;
}

int parse_expr(Vec_Token* table, Vec_Token* input, u64 pos, u8 prec) {
    int res1;
    if (prec <= 1) {
        res1 = parse_expr(table, input, pos, prec + 1);
    } else {
        res1 = parse_term(table, input, pos);
    }
    if (res1 == -1) {
        return -1;
    }
    Token c = input->data[pos + res1];
    if (!is_binary_op(c.type)) {
        return res1;
    }
    if (precedence(c.type) >= prec) {
        int res2 = parse_expr(table, input, pos + res1 + 1, prec);
        if (res2 == -1) {
            return -1;
        }
        push_Token(table, c);
        return res1 + res2 + 1;
    }
    return res1;
}

Vec_Token parse(Vec_Token* v) {
    Vec_Token table = create_with_capacity_Token(v->len);
    int res = parse_expr(&table, v, 0, 0);
    printf("Parsed tokens : %d out of %lu\n", res, v->len);
    return table;
}

void* vec_to_tree(Iter_Token* v, void** root) {
    if (v->len == 0) {
        puts("This function doesn't need newline.");
        return nullptr;
    }
    if (root == nullptr) {
        root = malloc(sizeof(void*));
    }
    // printf("roots %lu, %lu\n", root, *root);
    for (; v->pos < v->len; v->pos++) {
        printf("i : %lu %lu; tok : ", v->pos, v->len - 1 - v->pos);
        pretty_print_tok(v->data[v->len - 1 - v->pos]);
        puts("");

        Token t = v->data[v->len - 1 - v->pos];
        v->pos++;
        if (t.type == LParen || t.type == RParen) {
            continue;
        } else if (is_binary_op(t.type)) {
            BinaryOp* op = (BinaryOp*)malloc(sizeof(BinaryOp));
            op->type = t.type;
            vec_to_tree(v, &(op->right));
            vec_to_tree(v, &(op->left));
            // printf("Leaves %lu %lu %lu %lu %lu\n", op->right, op->left,
            //        *(u64*)op->right, *(u64*)op->left, op);
            *root = (void*)op;
            return *root;
        } else if (t.type == IntLiteral) {
            Literal* l = malloc(sizeof(Literal));
            *l = (Literal){IntLiteral, t.int_val};
            *root = l;
            return *root;
        } else {
            return 0;
        }
        break;
    }
    return *root;
}

void print_tree(void* root) {
    TokenType t = *(TokenType*)root;
    if (t == IntLiteral) {
        pretty_print_tok(*(Token*)root);
    } else if (is_binary_op(t)) {
        BinaryOp* node = (BinaryOp*)root;
        print_tree(node->left);
        pretty_print_tok((Token){node->type, 0});
        print_tree(node->right);
    }
}

// int parse_expr_tree(Vec_Token* table, Vec_Token* v, u64 pos, u8 prec);
// int parse_term_tree(Vec_Token* table, Vec_Token* input, u64 pos);
//
// int parse_term_tree(Vec_Token* table, Vec_Token* input, u64 pos) {
//     Token c = input->data[pos];
//     if (c.type == LParen) {
//         int res = parse_expr_tree(table, input, pos + 1, 0);
//         if (res == -1) {
//             return -1;
//         }
//         if (input->data[pos + 1 + res].type == RParen) {
//             return 2 + res;
//         }
//     } else if (c.type == IntLiteral) {
//         push_Token(table, c);
//         return 1;
//     }
//     return -1;
// }
//
// int parse_expr_tree(Vec_Token* table, Vec_Token* input, u64 pos, u8 prec) {
//     int res1;
//     if (prec <= 1) {
//         res1 = parse_expr_tree(table, input, pos, prec + 1);
//     } else {
//         res1 = parse_term_tree(table, input, pos);
//     }
//     if (res1 == -1) {
//         return -1;
//     }
//     Token c = input->data[pos + res1];
//     if (!is_binary_op(c.type)) {
//         return res1;
//     }
//     if (precedence(c.type) >= prec) {
//         int res2 = parse_expr_tree(table, input, pos + res1 + 1, prec);
//         if (res2 == -1) {
//             return -1;
//         }
//         push_Token(table, c);
//         return res1 + res2 + 1;
//     }
//     return res1;
// }
//
// Vec_Token parse_tree(Vec_Token* v) {
//     Vec_Token table = create_with_capacity_Token(v->len);
//     int res = parse_expr_tree(&table, v, 0, 0);
//     printf("Parsed tokens : %d out of %lu\n", res, v->len);
//     return table;
// }

int main(void) {
    // static const u64 len = 256;
    // struct pollfd fds[1] = {{0, POLLIN, 0}};

    Literal* leaf1 = malloc(sizeof(Literal));
    Literal* leaf2 = malloc(sizeof(Literal));
    *leaf1 = (Literal){IntLiteral, 10};
    *leaf2 = (Literal){IntLiteral, 3};
    BinaryOp* tree = malloc(sizeof(BinaryOp));
    *tree = (BinaryOp){Plus, leaf1, leaf2};
    print_tree(tree);
    puts("");
    char* buffer = "10 + 4 / 3 * 5 + 4 ^ 6";
    Lexer l = {buffer, strlen(buffer), 0};
    Vec_Token toks = lex(&l);
    pretty_print(&toks);

    Vec_Token res = parse(&toks);
    pretty_print(&res);
    Iter_Token I = (Iter_Token){res.data, res.len, 0};
    void* root = vec_to_tree(&I, 0);
    print_tree(root);
    puts("");

    // for (;;) {
    //     char buffer[len];
    //     memset(buffer, 0, len);
    //     poll(fds, 1, 50000);
    //
    //     if (fds[0].revents & POLLIN) {
    //         read(0, buffer, len - 1);
    //         Lexer l = {buffer, strlen(buffer), 0};
    //         Vec_Token toks = lex(&l);
    //         pretty_print(&toks);
    //
    //         Vec_Token res = parse(&toks);
    //         pretty_print(&res);
    //         Iter_Token I = (Iter_Token){res.data, res.len, 0};
    //         void* root = vec_to_tree(&I, 0);
    //         print_tree(root);
    //     }
    // }

    return 0;
}
