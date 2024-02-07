#include "Calc.h"

void push_node(Stack **head, double value, int priority, my_type type) {
  Stack *tmp = (Stack *)malloc(sizeof(Stack));
  if (tmp != NULL) {
    tmp->value = value;
    tmp->priority = priority;
    tmp->type = type;
    tmp->next = *head;
    *head = tmp;
  }
}

void pop_node(Stack **head) {
  if (*head != NULL) {
    Stack *out = *head;
    *head = (*head)->next;
    free(out);
  }
}

int peek_node(Stack *head) {
  int res = 0;
  if (head != NULL) {
    res = head->type;
  }
  return res;
}

void remove_node(Stack **head) {
  while (*head) {
    Stack *tmp = *head;
    *head = (*head)->next;
    free(tmp);
  }
}
