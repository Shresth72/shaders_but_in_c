#pragma once
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include <raylib.h>

#include "lib/raylib/raylib-5.5_linux_amd64/include/raylib.h"
#include "lib/stb_image.h"
#include "lib/stb_image_write.h"

typedef struct Node Node;

typedef enum {
  // Types
  NK_X,
  NK_Y,
  NK_NUMBER,
  NK_BOOLEAN,

  // Binary Operations
  NK_ADD,
  NK_MULT,
  NK_MOD,
  NK_GT,

  // Operation Wrappers
  NK_TRIPLE,
  NK_IF,

  // Rule (ref to another grammar rule index)
  NK_RULE,
  NK_RANDOM,
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
   : (kind) == NK_RULE    ? "rule"                                             \
   : (kind) == NK_RANDOM  ? "random"                                           \
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

  int rule;
} Node_As;

struct Node {
  Node_Kind kind;
  const char *file;
  int line;
  Node_As as;
};

// MAIN FUNCTIONS
Node *eval(Node *expr, float x, float y);
Node *eval_binop(Node *expr, float x, float y, Node_Kind kind);
bool render_pixels(Node *f);

// GRADIENTS
Node *gray_gradient_ast();
Node *cool_gradient_ast();

// UTILS FUNCTIONS
void node_print(Node *node);
bool expect_kind(Node *expr, Node_Kind kind);

// GRAMMAR FUNCTIONS
Node *node_loc(const char *file, int line, Node_Kind kind);

Node *node_number_loc(const char *file, int line, float number);
Node *node_boolean_loc(const char *file, int line, bool boolean);
Node *node_rule_loc(const char *file, int line, int rule);

Node *node_binop_loc(const char *file, int line, Node_Kind kind, Node *lhs,
                     Node *rhs);
Node *node_add_loc(const char *file, int line, Node *lhs, Node *rhs);
Node *node_mult_loc(const char *file, int line, Node *lhs, Node *rhs);
Node *node_mod_loc(const char *file, int line, Node *lhs, Node *rhs);
Node *node_gt_loc(const char *file, int line, Node *lhs, Node *rhs);

Node *node_triple_loc(const char *file, int line, Node *first, Node *second,
                      Node *third);
Node *node_if_loc(const char *file, int line, Node *cond, Node *then,
                  Node *elze);

// UTIL MACROS
#define NODE_PRINT_LN(node) (node_print(node), printf("\n"))
#define UNREACHABLE_CODE(message)                                              \
  do {                                                                         \
    fprintf(stderr, "%s:%d: UNREACHABLE CODE: %s\n", __FILE__, __LINE__,       \
            message);                                                          \
    abort();                                                                   \
  } while (0)

// GRAMMAR MACROS
#define node_x() node_loc(__FILE__, __LINE__, NK_X)
#define node_y() node_loc(__FILE__, __LINE__, NK_Y)
#define node_random() node_loc(__FILE__, __LINE__, NK_RANDOM)

#define node_number(number) node_number_loc(__FILE__, __LINE__, number)
#define node_boolean(number) node_boolean_loc(__FILE__, __LINE__, boolean)
#define node_rule(rule) node_rule_loc(__FILE__, __LINE__, rule)

#define node_add(lhs, rhs) node_add_loc(__FILE__, __LINE__, lhs, rhs)
#define node_mult(lhs, rhs) node_mult_loc(__FILE__, __LINE__, lhs, rhs)
#define node_mod(lhs, rhs) node_mod_loc(__FILE__, __LINE__, lhs, rhs)
#define node_gt(lhs, rhs) node_gt_loc(__FILE__, __LINE__, lhs, rhs)

#define node_triple(first, second, third)                                      \
  node_triple_loc(__FILE__, __LINE__, first, second, third)
#define node_if(cond, then, elze)                                              \
  node_if_loc(__FILE__, __LINE__, cond, then, elze)
