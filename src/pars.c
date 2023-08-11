/// \file
#include "pars.h"

/**
 * @brief get a number from the string
 *
 * @param str  specified expression
 * @param i index of the initial element
 * @return double number
 */
double pars_num(char *str, int i) {
  double res = 0;
  res = atof(&str[i]);
  return res;
}

/**
 * @brief depending on the function, we assign an number
 *
 * @param str  specified expression
 * @return int number of the function
 */
int pars_function(char *str) {
  int res = 0;
  switch (*str) {
    case '+':
      res = 1;
      break;
    case '-':
      res = 2;
      break;
    case '*':
      res = 3;
      break;
    case '/':
      res = 4;
      break;
    case '%':
      res = 5;
      break;
    case '^':
      res = 6;
      break;
    case 's':
      if (*(str + 1) == 'q') res = 7;
      if (*(str + 1) == 'i') res = 11;
      break;
    case 'a':
      if (*(str + 1) == 'c') res = 8;
      if (*(str + 1) == 's') res = 9;
      if (*(str + 1) == 't') res = 10;
      break;
    case 'c':
      res = 12;
      break;
    case 't':
      res = 13;
      break;
    case 'l':
      if (*(str + 1) == 'n') res = 14;
      if (*(str + 1) == 'o') res = 15;
      break;
    case '(':
      res = 16;
      break;
    case ')':
      res = 17;
      break;
  }
  return res;
}

/**
 * @brief calculating the priority number by function
 *
 * @param a function number
 * @return int priority
 */
int priority_function(int a) {
  int res = 0;
  if (a == 1 || a == 2) res = 1;
  if (a > 2 && a < 6) res = 2;
  if (a == 6) res = 3;
  if (a > 6 && a < 16) res = 4;
  if (a == 16 || a == 17) res = 5;
  return res;
}

/**
 * @brief splitting the string into tokens
 *
 * @param str  specified expression
 * @return char* string in which we write the result
 */
char *parsing(char *str) {
  char *temp = NULL;
  temp = calloc(256, sizeof(char));
  int len = strlen(str), j = 0;
  t_lex head[256] = {{0, 0, 0}};
  for (int i = 0; i < len; i++, j++) {
    if (is_numbers(str[i])) {
      head[j].value = pars_num(str, i);
      head[j].operation = 0;
      head[j].priority = 0;
      while (is_numbers(str[i]) || str[i] == '.') {
        i++;
      }
      i = i - 1;
    } else if (str[i] == '-' || str[i] == '+' || str[i] == '*' ||
               str[i] == '/' || str[i] == '%' || str[i] == '^') {
      head[j].value = 0;
      head[j].operation = pars_function(&str[i]);
      head[j].priority = priority_function(head[j].operation);
    } else if (str[i] == 'c' || str[i] == 's' || str[i] == 't' ||
               str[i] == 'l' || str[i] == 'a') {
      head[j].value = 0;
      head[j].operation = pars_function(&str[i]);
      head[j].priority = priority_function(head[j].operation);
      while (!is_numbers(str[i]) && str[i] != '(') {
        i++;
      }
      i = i - 1;
    } else if (str[i] == ')' || str[i] == '(') {
      head[j].value = 0;
      head[j].operation = pars_function(&str[i]);
      head[j].priority = priority_function(head[j].operation);
    }
  }
  temp = input(head, j, temp);
  return temp;
}

/**
 * @brief translation into reverse Polish notation
 *
 * @param head array of structures divided into tokens
 * @param j number of elements
 * @param temp string in which we write the result
 * @return char* string in which we write the result
 */
char *input(t_lex *head, int j, char *temp) {
  t_stack ready[256] = {0};
  t_lex support[256] = {0};
  int n = 0, m = 0;
  for (int i = 0; i < j; i++) {
    if (!head[i].operation) {
      ready[n].lex = head[i];
      n++;
    } else if (head[i].operation == 17) {
      while (support[m - 1].operation != 16) {
        ready[n].lex = support[m - 1];
        n++;
        m--;
      }
      m--;
    } else if (head[i].operation > 0 && head[i].operation < 17) {
      for (int k = m; k >= 0; k--) {
        if (head[i].priority <= support[m - 1].priority &&
            support[m - 1].operation != 16 &&
            (support[m - 1].operation && head[i].operation != 6)) {
          ready[n].lex = support[m - 1];
          n++;
          m--;
        } else {
          break;
        }
      }
      support[m] = head[i];
      m++;
    }
  }
  if (m > 0) {
    while (m) {
      ready[n].lex = support[m - 1];
      n++;
      m--;
    }
  }
  temp = calculations(ready, n, temp);
  return temp;
}

/**
 * @brief calculating the value according to the function for two numbers
 *
 * @param oper function number
 * @param first value to calculate
 * @param second value to calculate
 * @return double calculation result
 */
double operations(int oper, double first, double second) {
  double result = 0;
  if (oper == 1) result = first + second;
  if (oper == 2) result = first - second;
  if (oper == 3) result = first * second;
  if (oper == 4) result = first / second;
  if (oper == 5) result = fmod(first, second);
  if (oper == 6) result = pow(first, second);
  return result;
}

/**
 * @brief calculating a value according to a function for a single number
 *
 * @param oper function number
 * @param first value for calculation
 * @return double calculation result
 */
double functions(int oper, double first) {
  double result = 0;
  if (oper == 7) result = sqrt(first);
  if (oper == 8) result = acos(first);
  if (oper == 9) result = asin(first);
  if (oper == 10) result = atan(first);
  if (oper == 11) result = sin(first);
  if (oper == 12) result = cos(first);
  if (oper == 13) result = tan(first);
  if (oper == 14) result = log(first);
  if (oper == 15) result = log10(first);
  return result;
}

/**
 * @brief calculating the value of a given expression
 *
 * @param stackt array of structures folded in reverse polish notation
 * @param n number of elements
 * @param temp string in which we write the result
 * @return char* string in which we write the result
 */
char *calculations(t_stack *stackt, int n, char *temp) {
  double result = 0;
  t_res res[256] = {0};
  int r = 0;
  for (int i = 0; i < n; i++) {
    if (stackt[i].lex.operation == 0) {
      res[r].res = stackt[i].lex.value;
      r++;
    } else if (stackt[i].lex.operation > 0 && stackt[i].lex.operation < 7) {
      if (r > 1) {
        res[r - 2].res =
            operations(stackt[i].lex.operation, res[r - 2].res, res[r - 1].res);
        r--;
      }
    } else if (stackt[i].lex.operation > 6 && stackt[i].lex.operation < 16) {
      if (r > 0) {
        res[r - 1].res = functions(stackt[i].lex.operation, res[r - 1].res);
      }
    }
  }
  if (r > 1) {
    strcpy(temp, "Incorrect expression");
  } else {
    result = res[0].res;
    if (fabs(result) > 1000000000) {
      sprintf(temp, "%e", result);
    } else {
      sprintf(temp, "%.15f", result);
    }
  }
  int len = strlen(temp);
  for (int i = len - 1; i >= 0; i--) {
    if (temp[i] == '0' && i != 0) {
      temp[i] = '\0';
    } else if (temp[i] == '.') {
      temp[i] = '\0';
      break;
    } else {
      break;
    }
  }
  return temp;
}
