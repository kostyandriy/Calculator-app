#include "Calc.h"

// -------------------------------пробелы----------------------------------
void trim_input(char *input, char *result) {
  int count = 0;
  int len = strlen(input);
  for (int i = 0, j = 0; i < len; i++) {
    if (input[i] != ' ') {
      result[j] = input[i];
      j++;
    } else {
      count++;
    }
  }
  if (count > 0)
    result[strlen(input) - count] = '\0';
  else
    result[strlen(input)] = '\0';
}

//----------------------------------Логика скобок-----------------------------
int brackets_par(char *input) {
  int res = 0;
  int flag_er = 0;
  int flag_nonvalid = 0;
  int len = strlen(input);
  char temp[MAX_SIZE_STRING] = "";
  for (int i = 0; i < len && !flag_er; i++) {
    if (is_bracket(input[i]) == 1) {
      temp[strlen(temp)] = '(';
      if (!brackets_valid_in(input, i)) flag_nonvalid = 1;
    }
    if (is_bracket(input[i]) == 2) {
      if (temp[strlen(temp) - 1] == '(') {
        temp[strlen(temp) - 1] = '\0';
      } else {
        flag_er = 1;
      }
    }
  }
  if (!flag_er && strlen(temp) == 0 && !flag_nonvalid) {
    res = 1;
  }
  return res;
}

int brackets_valid_in(char *input, size_t i) {
  int res = 0;
  i += 1;
  if (input[i] != '\0' &&
      (input[i] == '(' || input[i] == '+' || input[i] == '-' ||
       is_number(input[i]) || funcs(input, &i, 0) || input[i] == 'x' ||
       is_dot(input, i)))
    res = 1;
  return res;
}

int is_bracket(char symbol) {
  int res = 0;
  if (symbol == '(') res = 1;
  if (symbol == ')') res = 2;
  return res;
}

// -------------------------------операторы----------------------------------
int is_operator(char *input, size_t *i, int offset) {
  int res = 0;
  int exist_mod = 0;
  int exist_operator = 0;
  if (input[*i] == 'm' && strlen(input) - *i - 1 >= 2) {
    if (input[*i + 1] == 'o' && input[*i + 2] == 'd') {
      exist_mod = 1;
      *i += 3 - offset;
    }
  }
  if ((input[*i] == '+') || (input[*i] == '-') || (input[*i] == '*') ||
      (input[*i] == '/') || (input[*i] == '^')) {
    exist_operator = 1;
    *i += 1 - offset;
  }
  if (exist_mod) res = 1;
  if (exist_operator) res = 2;
  return res;
}

int valid_after_operator(char *input) {
  int res = 0;
  int flag_er = 0;
  size_t len = strlen(input);
  for (size_t i = 0; i < len && !flag_er; i++) {
    if (is_operator(input, &i, 0) == 2) {
      if (!(input[i] != '\0' &&
            (is_number(input[i]) || input[i] == '(' || funcs(input, &i, 0) ||
             input[i] == 'x' || is_dot(input, i)))) {
        flag_er = 1;
      }
    }
  }
  if (!flag_er) res = 1;
  return res;
}

int valid_after_mod(char *input) {
  int res = 0;
  int flag_er = 0;
  for (size_t i = 0; i < strlen(input); i++) {
    if (is_operator(input, &i, 0) == 1) {
      if (!(input[i] != '\0' && input[i] != '-' &&
            (is_number(input[i]) || input[i] == '(' || funcs(input, &i, 0) ||
             input[i] == 'x' || is_dot(input, i))))
        flag_er = 1;
    }
  }
  if (!flag_er) res = 1;
  return res;
}

int valid_mul(char *input) {
  int res = 0;
  size_t len = (strlen(input));
  int flag_simple = 0;
  int flag_complex = 0;
  for (size_t i = 0; i < len && !flag_simple && !flag_complex; i++) {
    if (!valid_simple_mul(input, i)) flag_simple = 1;

    if (!valid_complex_mul(input, &i)) flag_complex = 1;
  }
  if (!flag_simple && !flag_complex) res = 1;

  return res;
}

int valid_simple_mul(char *input, size_t i) {
  int res = 0;
  int flag_er = 0;
  if (is_x(input[i])) {
    if (i != 0) {
      if (is_number(input[i - 1]) || is_dot(input, i - 1) ||
          is_bracket(input[i - 1] == 2))
        flag_er = 1;
    }
    if (is_number(input[i + 1]) || is_dot(input, i + 1) ||
        is_bracket(input[i + 1]) == 1)
      flag_er = 1;
  }
  if (i != 0 && is_bracket(input[i]) == 1 &&
      (is_number(input[i - 1]) || is_dot(input, i - 1)))
    flag_er = 1;
  if (is_bracket(input[i]) == 2 &&
      (is_number(input[i + 1]) || is_dot(input, i + 1)))
    flag_er = 1;

  if (!flag_er) res = 1;
  return res;
}

int valid_complex_mul(char *input, size_t *i) {
  int res = 0;
  int flag_er = 0;
  size_t k = *i;
  if (funcs(input, i, 1)) {
    if (k != 0) {
      if (is_number(input[k - 1]) || is_dot(input, k - 1) ||
          is_bracket(input[k - 1] == 2) || is_x(input[k - 1]))
        flag_er = 1;
    }
  }
  if (!flag_er) res = 1;

  return res;
}

int valid_start(char *input) {
  int res = 0;
  int flag_er = 0;
  size_t i = 0;
  if (input[i] == '^' || input[i] == '*' || input[i] == '/') flag_er = 1;
  if (is_operator(input, &i, 0) == 1) flag_er = 1;
  if (!flag_er) res = 1;
  return res;
}

//------------------------------------числа------------------------------------
int is_number(char symbol) { return (symbol >= '0' && symbol <= '9'); }

int valid_number(char *input) {
  int res = 0;
  int len = strlen(input);
  int flag_dot = 0;
  for (int i = 0; i < len && !flag_dot; i++) {
    int amount_dot = 0;
    while (input[i] != '\0' && (is_number(input[i]) || is_dot(input, i))) {
      if (is_dot(input, i)) amount_dot++;
      if (amount_dot > 1) flag_dot = 1;
      i++;
    }
  }
  if (!flag_dot) res = 1;
  return res;
}

//--------------------------------точка----------------------------------
int is_dot(char *input, int i) {
  int res = 0;
  if (input[i] == '.' && i != 0) {
    if (is_number(input[i - 1]) || is_number(input[i + 1])) res = 1;
  }
  return res;
}

//----------------------------------x----------------------------
int is_x(char symbol) { return (symbol == 'x'); }

//----------------------------функции-------------------------------------
int trigonometry(char *input, size_t *i, int offset) {
  int res = 0;
  if (input[*i] == 's' && strlen(input) - *i - 1 >= 2) {
    if (input[*i + 1] == 'i' && input[*i + 2] == 'n') {
      res = 1;
      *i += 3 - offset;
    }
  }
  if (input[*i] == 'c' && strlen(input) - *i - 1 >= 2) {
    if (input[*i + 1] == 'o' && input[*i + 2] == 's') {
      res = 2;
      *i += 3 - offset;
    }
  }
  if (input[*i] == 't' && strlen(input) - *i - 1 >= 2) {
    if (input[*i + 1] == 'a' && input[*i + 2] == 'n') {
      res = 3;
      *i += 3 - offset;
    }
  }
  return res;
}

int funcs(char *input, size_t *i, int offset) {
  int res = 0;
  int tmp = 0;
  if (input[*i] == 'l') {
    if (strlen(input) - *i - 1 >= 1) {
      if (input[*i + 1] == 'n') {
        res = 8;
        *i += 2 - offset;
      }
    }
    if (strlen(input) - *i - 1 >= 2) {
      if (input[*i + 1] == 'o' && input[*i + 2] == 'g') {
        res = 9;
        *i += 3 - offset;
      }
    }
  }
  if (input[*i] == 's' && strlen(input) - *i - 1 >= 3) {
    if (input[*i + 1] == 'q' && input[*i + 2] == 'r' && input[*i + 3] == 't') {
      res = 7;
      *i += 4 - offset;
    }
  }
  tmp = trigonometry(input, i, offset);
  if (input[*i] == 'a' && strlen(input) - *i - 1 >= 3) {
    *i += 1;
    tmp = trigonometry(input, i, offset) + 3;
  }
  if (tmp != 0) res = tmp;
  return res;
}

//----------------------------Скобка после функции---------------------------
int bracket_after_func(char *input) {
  int res = 0;
  int flag_non_bracket = 0;
  size_t len = strlen(input);
  for (size_t i = 0; i < len; i++) {
    if (funcs(input, &i, 0) != 0) {
      if (input[i] != '(') {
        flag_non_bracket = 1;
      }
    }
  }
  if (!flag_non_bracket) {
    res = 1;
  }
  return res;
}

//-----------------------------Общая проверка------------------------------
int valid_input(char *input) {
  int res = 0;
  int flag_symb = 0;
  int flag_brackets = 0;
  int flag_operators = 0;
  int flag_brackets_after_func = 0;
  int flag_valid_number = 0;
  int flag_valid_mul = 0;
  int flag_valid_start = 0;
  int flag_after_mod = 0;
  size_t len = strlen(input);

  for (size_t i = 0;
       i < len && !flag_symb && !(input[i] == '\n' || input[i] == '\0'); i++) {
    if (!(is_number(input[i]) || funcs(input, &i, 1) != 0 || is_dot(input, i) ||
          is_x(input[i]) || is_operator(input, &i, 1) != 0 ||
          is_bracket(input[i]))) {
      flag_symb = 1;
    }
  }

  if (!brackets_par(input)) flag_brackets = 1;

  if (!valid_after_operator(input)) flag_operators = 1;

  if (!bracket_after_func(input)) flag_brackets_after_func = 1;

  if (!valid_number(input)) flag_valid_number = 1;

  if (!valid_mul(input)) flag_valid_mul = 1;

  if (!valid_start(input)) flag_valid_start = 1;

  if (!valid_after_mod(input)) flag_after_mod = 1;

  if (!flag_symb && !flag_brackets && !flag_operators &&
      !flag_brackets_after_func && !flag_valid_number && !flag_valid_mul &&
      !flag_valid_start && !flag_after_mod)
    res = 1;

  return res;
}
