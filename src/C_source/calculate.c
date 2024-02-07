#include "Calc.h"

int calculate(Stack **ready, double *result) {
  int res = 0;
  int flag_error_math = 0;
  Stack *number = NULL;
  while (*ready && !flag_error_math) {
    calculate_1(ready, &number, &flag_error_math);
    calculate_2(ready, &number, &flag_error_math);
    calculate_3(ready, &number, &flag_error_math);
    calculate_4(ready, &number, &flag_error_math);
  }
  if (number) {
    *result = number->value;
    pop_node(&number);
  } else
    flag_error_math = 1;
  if (!flag_error_math) res = 1;

  return res;
}

void calculate_1(Stack **ready, Stack **number, int *flag_error_math) {
  double tmp_1 = 0;
  double tmp_2 = 0;
  double tmp_res = 0;
  if (peek_node(*ready) == 1 && !(*flag_error_math)) {
    push_node(number, (*ready)->value, (*ready)->priority, (*ready)->type);
    pop_node(ready);
  }
  if (peek_node(*ready) == 2 && !(*flag_error_math)) {
    push_node(number, (*ready)->value, (*ready)->priority, (*ready)->type);
    pop_node(ready);
  }
  if (peek_node(*ready) == 5 && !(*flag_error_math)) {
    tmp_2 = (*number)->value;
    pop_node(number);
    tmp_1 = (*number)->value;
    pop_node(number);
    tmp_res = tmp_1 + tmp_2;
    push_node(number, tmp_res, get_priority(Number), Number);
    pop_node(ready);
  }
  if (peek_node(*ready) == 6 && !(*flag_error_math)) {
    tmp_2 = (*number)->value;
    pop_node(number);
    tmp_1 = (*number)->value;
    pop_node(number);
    tmp_res = tmp_1 - tmp_2;
    push_node(number, tmp_res, get_priority(Number), Number);
    pop_node(ready);
  }
  if (peek_node(*ready) == 7 && !(*flag_error_math)) {
    tmp_2 = (*number)->value;
    pop_node(number);
    tmp_1 = (*number)->value;
    pop_node(number);
    tmp_res = tmp_2 * tmp_1;
    push_node(number, tmp_res, get_priority(Number), Number);
    pop_node(ready);
  }
}

void calculate_2(Stack **ready, Stack **number, int *flag_error_math) {
  double tmp_1 = 0;
  double tmp_2 = 0;
  double tmp_res = 0;
  if (peek_node(*ready) == 8 && !(*flag_error_math)) {
    tmp_2 = (*number)->value;
    pop_node(number);
    if (tmp_2 != 0) {
      tmp_1 = (*number)->value;
      pop_node(number);
      tmp_res = tmp_1 / tmp_2;
      push_node(number, tmp_res, get_priority(Number), Number);
    } else
      *flag_error_math = 1;
    pop_node(ready);
  }
  if (peek_node(*ready) == 9 && !(*flag_error_math)) {
    if (number) {
      tmp_2 = (*number)->value;
      pop_node(number);
      if (tmp_2 != 0 && number) {
        tmp_1 = (*number)->value;
        pop_node(number);
        tmp_res = fmod(tmp_1, tmp_2);
        push_node(number, tmp_res, get_priority(Number), Number);
      } else
        *flag_error_math = 1;
    } else
      *flag_error_math = 1;
    pop_node(ready);
  }
  if (peek_node(*ready) == 10 && !(*flag_error_math)) {
    tmp_2 = (*number)->value;
    pop_node(number);
    tmp_1 = (*number)->value;
    pop_node(number);
    tmp_res = pow(tmp_1, tmp_2);
    push_node(number, tmp_res, get_priority(Number), Number);
    pop_node(ready);
  }
  if (peek_node(*ready) == 11 && !(*flag_error_math)) {
    tmp_1 = (*number)->value;
    pop_node(number);
    tmp_res = sin(tmp_1);
    push_node(number, tmp_res, get_priority(Number), Number);
    pop_node(ready);
  }
}

void calculate_3(Stack **ready, Stack **number, int *flag_error_math) {
  double tmp_1 = 0;
  double tmp_res = 0;
  if (peek_node(*ready) == 12 && !(*flag_error_math)) {
    tmp_1 = (*number)->value;
    pop_node(number);
    tmp_res = cos(tmp_1);
    push_node(number, tmp_res, get_priority(Number), Number);
    pop_node(ready);
  }
  if (peek_node(*ready) == 13 && !(*flag_error_math)) {
    tmp_1 = (*number)->value;
    pop_node(number);
    tmp_res = tan(tmp_1);
    push_node(number, tmp_res, get_priority(Number), Number);
    pop_node(ready);
  }
  if (peek_node(*ready) == 14 && !(*flag_error_math)) {
    tmp_1 = (*number)->value;
    if (tmp_1 >= -1 && tmp_1 <= 1) {
      pop_node(number);
      tmp_res = asin(tmp_1);
      push_node(number, tmp_res, get_priority(Number), Number);
    } else
      *flag_error_math = 1;
    pop_node(ready);
  }
  if (peek_node(*ready) == 15 && !(*flag_error_math)) {
    tmp_1 = (*number)->value;
    if (tmp_1 >= -1 && tmp_1 <= 1) {
      pop_node(number);
      tmp_res = acos(tmp_1);
      push_node(number, tmp_res, get_priority(Number), Number);
    } else
      *flag_error_math = 1;
    pop_node(ready);
  }
  if (peek_node(*ready) == 16 && !(*flag_error_math)) {
    tmp_1 = (*number)->value;
    if (fmod(tmp_1, M_PI / 2) > 1e-8 || fmod(tmp_1, M_PI / 2) < -1e-8) {
      pop_node(number);
      tmp_res = atan(tmp_1);
      push_node(number, tmp_res, get_priority(Number), Number);
    } else
      *flag_error_math = 1;
    pop_node(ready);
  }
}

void calculate_4(Stack **ready, Stack **number, int *flag_error_math) {
  double tmp_1 = 0;
  double tmp_res = 0;
  if (peek_node(*ready) == 17 && !(*flag_error_math)) {
    tmp_1 = (*number)->value;
    if (tmp_1 >= 0) {
      pop_node(number);
      tmp_res = sqrt(tmp_1);
      push_node(number, tmp_res, get_priority(Number), Number);
    } else
      *flag_error_math = 1;
    pop_node(ready);
  }
  if (peek_node(*ready) == 18 && !(*flag_error_math)) {
    tmp_1 = (*number)->value;
    if (tmp_1 > 0) {
      pop_node(number);
      tmp_res = log(tmp_1);
      push_node(number, tmp_res, get_priority(Number), Number);
    } else
      *flag_error_math = 1;
    pop_node(ready);
  }
  if (peek_node(*ready) == 19 && !(*flag_error_math)) {
    tmp_1 = (*number)->value;
    if (tmp_1 > 0) {
      pop_node(number);
      tmp_res = log10(tmp_1);
      push_node(number, tmp_res, get_priority(Number), Number);
    } else
      *flag_error_math = 1;
    pop_node(ready);
  }
}

int final_func(char *input, double *calculated, double x) {
  int result = 0;
  char res[MAX_SIZE_STRING] = "";
  trim_input(input, res);
  double tmp = 0;
  if (valid_input(res)) {
    Stack *inverse_orig = NULL;
    Stack *orig = NULL;
    Stack *inverse_ready = NULL;
    Stack *support = NULL;
    Stack *ready = NULL;
    stack_from_str(&inverse_orig, res, x);
    inverse_stack(&inverse_orig, &orig);
    notation_stack(&orig, &inverse_ready, &support);
    inverse_stack(&inverse_ready, &ready);
    if (calculate(&ready, &tmp)) {
      *calculated = tmp;
      result = 1;
    } else {
      result = -1;
    }
    remove_node(&ready);
  } else {
    result = -2;
  }
  return result;
}
