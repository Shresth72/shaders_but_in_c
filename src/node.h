#pragma once
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

typedef enum {
  NK_X,
  NK_Y,

  NK_NUMBER,
  NK_ADD,
  NK_MULT,
  NK_MOD,

  NK_BOOLEAN,
  NK_GT,

  NK_TRIPLE,
  NK_IF,
} Node_Kind;

#define node_kind_string(kind)                                                 \
  ((kind) == NK_X         ? "x"                                                \
   : (kind) == NK_Y       ? "y"                                                \
   : (kind) == NK_NUMBER  ? "number"                                           \
   : (kind) == NK_ADD     ? "add"                                              \
   : (kind) == NK_MULT    ? "mult"                                             \
   : (kind) == NK_MOD     ? "mod"                                              \
   : (kind) == NK_BOOLEAN ? "boolean"                                          \
   : (kind) == NK_GT      ? "gt"                                               \
   : (kind) == NK_TRIPLE  ? "triple"                                           \
   : (kind) == NK_IF      ? "if"                                               \
                          : "unknown")

typedef struct {
  Node *lhs;
  Node *rhs;
} Node_Binop;

typedef struct {
  Node *first;
  Node *second;
  Node *third;
} Node_Triple;

typedef struct {
  Node *cond;
  Node *then;
  Node *elze;
} Node_If;

typedef union {
  float number;
  bool boolean;
  Node_Binop binop;
  Node_Triple triple;
  Node_If iff;
} Node_As;

struct Node {
  Node_Kind kind;
  const char *file;
  int line;
  Node_As as;
};

void node_print(Node *node);
Node *eval(Node *expr, float x, float y);

Node *node_loc(const char *file, int line, Node_Kind kind);

Node *node_number_loc(const char *file, int line, float number);
Node *node_add_loc(const char *file, int line, Node *lhs, Node *rhs);
Node *node_mult_loc(const char *file, int line, Node *lhs, Node *rhs);
Node *node_boolean_loc(const char *file, int line, bool boolean);
Node *node_triple_loc(const char *file, int line, Node *first, Node *second,
                      Node *third);

// MACROS
#define node_x() node_loc(__FILE__, __LINE__, NK_X)
#define node_y() node_loc(__FILE__, __LINE__, NK_Y)

#define node_number(number) node_number_loc(__FILE__, __LINE__, number)
#define node_add(lhs, rhs) node_add_loc(__FILE__, __LINE__, lhs, rhs)
#define node_mult(lhs, rhs) node_mult_loc(__FILE__, __LINE__, lhs, rhs)

#define node_boolean(number) node_boolean_loc(__FILE__, __LINE__, boolean)

#define node_triple(first, second, third)                                      \
  node_triple_loc(__FILE__, __LINE__, first, second, third)
