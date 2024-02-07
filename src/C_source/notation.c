#include "Calc.h"

void notation_stack(Stack **origin, Stack **result, Stack **support) {
  int k = 0;
  while (*origin) {
    first_part_notation(origin, result, support, &k);
    second_part_notation(origin, result, support, &k);
  }
  // ---------------ЗАКИДЫВАЕМ В READY ВСЕ ИЗ САППОРТА---------------------
  while (peek_node(*support) != 0) {
    push_node(result, (*support)->value, (*support)->priority,
              (*support)->type);
    pop_node(support);
  }
}

void first_part_notation(Stack **origin, Stack **result, Stack **support,
                         int *k) {
  // -------------ЧИСЛО------------------------
  if (peek_node(*origin) == 1) {
    push_node(result, (*origin)->value, (*origin)->priority, (*origin)->type);
    pop_node(origin);
    *k += 1;
  }
  // ---------------ИКС---------------------
  if (peek_node(*origin) == 2) {
    push_node(result, (*origin)->value, (*origin)->priority, (*origin)->type);
    pop_node(origin);
    *k += 1;
  }
  // // ---------------ЛЕВАЯ---------------------
  if (peek_node(*origin) == 3) {
    if ((*origin)->next->type == 5 || (*origin)->next->type == 6) {
      push_node(result, 0, get_priority(Number), 1);
    }
    push_node(support, (*origin)->value, (*origin)->priority, (*origin)->type);
    pop_node(origin);
    *k += 1;
  }
  // // ---------------ПРАВАЯ---------------------
  if (peek_node(*origin) == 4) {
    while (peek_node(*support) != 3) {
      push_node(result, (*support)->value, (*support)->priority,
                (*support)->type);
      pop_node(support);
    }
    if (peek_node(*support) == 3) pop_node(support);
    pop_node(origin);
    *k += 1;
  }
  // // ---------------ПЛЮС---------------------
  if (peek_node(*origin) == 5) {
    if (*k == 0) {
      push_node(result, 0, get_priority(Number), 1);
    }
    while (peek_node(*support) != 0 && (*support)->priority >= 1) {
      push_node(result, (*support)->value, (*support)->priority,
                (*support)->type);
      pop_node(support);
    }
    push_node(support, (*origin)->value, (*origin)->priority, (*origin)->type);
    pop_node(origin);
    *k += 1;
  }
}

void second_part_notation(Stack **origin, Stack **result, Stack **support,
                          int *k) {
  // // ---------------МИНУС---------------------
  if (peek_node(*origin) == 6) {
    if (*k == 0) {
      push_node(result, 0, get_priority(Number), 1);
    }
    while (peek_node(*support) != 0 && (*support)->priority >= 1) {
      push_node(result, (*support)->value, (*support)->priority,
                (*support)->type);
      pop_node(support);
    }
    push_node(support, (*origin)->value, (*origin)->priority, (*origin)->type);
    pop_node(origin);
    *k += 1;
  }
  // // ---------------УМНОЖИТЬ И ДЕЛИТЬ И MOD---------------------
  if (peek_node(*origin) >= 7 && peek_node(*origin) <= 9) {
    while (peek_node(*support) != 0 &&
           (*support)->priority >= get_priority(7)) {
      push_node(result, (*support)->value, (*support)->priority,
                (*support)->type);
      pop_node(support);
    }
    push_node(support, (*origin)->value, (*origin)->priority, (*origin)->type);
    pop_node(origin);
    *k += 1;
  }
  // ---------------СТЕПЕНЬ---------------------
  if (peek_node(*origin) == 10) {
    while (peek_node(*support) != 0 &&
           (*support)->priority > get_priority(op_power)) {
      push_node(result, (*support)->value, (*support)->priority,
                (*support)->type);
      pop_node(support);
    }
    push_node(support, (*origin)->value, (*origin)->priority, (*origin)->type);
    pop_node(origin);
    *k += 1;
  }
  // ---------------ФУНКЦИИ---------------------
  if (peek_node(*origin) >= 11 && peek_node(*origin) <= 19) {
    while (peek_node(*support) != 0 &&
           (*support)->priority >= get_priority(11)) {
      push_node(result, (*support)->value, (*support)->priority,
                (*support)->type);
      pop_node(support);
    }
    push_node(support, (*origin)->value, (*origin)->priority, (*origin)->type);
    pop_node(origin);
    *k += 1;
  }
}
