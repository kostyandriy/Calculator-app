#include "Calc.h"

void stack_from_str(Stack **node, char *input, double x) {
  for (size_t i = 0; input[i] != '\0'; i++) {
    simple_symbols(node, input[i], x);
    complex_symbols(node, input, &i);
    number_symbols(node, input, &i);
  }
}

int get_priority(my_type type) {
  int res = -2;
  if (type >= 1 && type <= 2) res = 0;
  if (type >= 3 && type <= 4) res = -1;
  if (type >= 5 && type <= 6) res = 1;
  if (type >= 7 && type <= 9) res = 2;
  if (type == 10) res = 3;
  if (type >= 11 && type <= 19) res = 4;
  return res;
}

int get_type_simple(char symbol) {
  int res = 0;
  if (is_x(symbol)) res = 2;
  if (is_bracket(symbol) == 1) res = 3;
  if (is_bracket(symbol) == 2) res = 4;
  if (symbol == '+') res = 5;
  if (symbol == '-') res = 6;
  if (symbol == '*') res = 7;
  if (symbol == '/') res = 8;
  if (symbol == '^') res = 10;
  return res;
}

int get_type_complex(char *input, size_t *i) {
  int res = 0;
  int func = funcs(input, i, 1);
  if (is_operator(input, i, 1) == 1) res = 9;
  if (func == 1) res = 11;
  if (func == 2) res = 12;
  if (func == 3) res = 13;
  if (func == 4) res = 14;
  if (func == 5) res = 15;
  if (func == 6) res = 16;
  if (func == 7) res = 17;
  if (func == 8) res = 18;
  if (func == 9) res = 19;
  return res;
}

void simple_symbols(Stack **node, char symbol, double x) {
  int type = get_type_simple(symbol);
  if (type != 0 && type != 2) push_node(node, 0, get_priority(type), type);
  if (type == 2) push_node(node, x, get_priority(type), type);
}

void complex_symbols(Stack **node, char *input, size_t *i) {
  int type = get_type_complex(input, i);
  if (type != 0) push_node(node, 0, get_priority(type), type);
}

void number_symbols(Stack **node, char *input, size_t *i) {
  double res = 0;
  if (is_number(input[*i]) || is_dot(input, *i)) {
    res = atof(input + *i);
    while (input[*i] != '\0' && (is_number(input[*i]) || is_dot(input, *i))) {
      *i += 1;
    }
    *i -= 1;
    push_node(node, res, 0, Number);
  }
}

void inverse_stack(Stack **input, Stack **result) {
  while (*input) {
    push_node(result, (*input)->value, (*input)->priority, (*input)->type);
    pop_node(input);
  }
}
