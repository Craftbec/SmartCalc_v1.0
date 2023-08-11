/// \file
#include "chek.h"

#include <stdio.h>

/**
 * @brief checking a symbol for a number
 *
 * @param a the character being checked
 * @return int 0 - NO, 1 - YES;
 */
int is_numbers(char a) {
  int res = 0;
  if (a >= '0' && a <= '9') res = 1;
  return res;
}

/**
 * @brief checking for the operator
 *
 * @param a the character being checked
 * @return int 0 - NO, 1 - YES;
 */
int is_sign(char a) {
  int res = 0;
  if (a == '*' || a == '/' || a == '^' || a == '+') res = 1;
  return res;
}

/**
 * @brief checking for negative
 *
 * @param a the character being checked
 * @return int 0 - NO, 1 - YES;
 */
int is_minus(char a) {
  int res = 0;
  if (a == '-') res = 1;
  return res;
}

/**
 * @brief checking for the correct mod entry
 *
 * @param str specified expression
 * @param i index of the symbol being checked
 * @param len string length
 * @return int 0 - NO, 1 - YES;
 */
int is_mod(char* str, int i, int len) {
  int res = 0;
  int tmp = len - i;
  if (tmp >= 1 && i >= 1) {
    if (is_numbers(str[i + 1]) && is_numbers(str[i - 1])) {
      res = 1;
    }
  }
  return res;
}

/**
 * @brief validation of a given expression
 *
 * @param str specified expression
 * @return int 0 - NO, 1 - YES;
 */
int proverka(char* str) {
  int res = 1;
  int sk = 0, sk2 = 0;
  int len = strlen(str);
  if (is_sign(str[0]) || str[0] == '.') res = 0;
  for (int i = 0; i < len; i++) {
    if (str[i] == '(') {
      sk++;
      if (len - i > 0) {
        if (is_sign(str[i + 1]) || (str[i + 1]) == ')') res = 0;
      }
      if (i > 0) {
        if (is_numbers(str[i - 1])) res = 0;
      }
    } else if (str[i] == ')') {
      sk2++;
    } else if (i > 0 && str[i] == '.') {
      if (!is_numbers(str[i - 1]) || !is_numbers(str[i + 1])) res = 0;
      if (!dot(str, i, len)) res = 0;
    } else if (i > 1 && (is_minus(str[i]) || is_sign(str[i]))) {
      if (is_minus(str[i - 1]) || is_sign(str[i - 1])) res = 0;
    } else if (str[i] == '%') {
      if (!is_mod(str, i, len)) res = 0;
    }
  }
  if (sk != sk2) res = 0;
  if (!is_numbers(str[len - 1]) && (str[len - 1] != ')')) res = 0;
  return res;
}

/**
 * @brief Checking for one point at a number
 *
 * @param str specified expression
 * @param i index of the symbol being checked
 * @param len string length
 * @return int 0 - NO, 1 - YES;
 */
int dot(char* str, int i, int len) {
  int res = 0;
  int tmp = 0;
  while (i <= len) {
    if (str[i] == '.') tmp++;
    if ((is_minus(str[i]) || is_sign(str[i]) || i == len) && tmp == 1) {
      res = 1;
      i = len;
    }
    i++;
  }
  return res;
}

/**
 * @brief Adding 0 before the sign '-'
 *
 * @param str specified expression
 * @return char* string without a unary minus
 */
char* unar(char* str) {
  char result[526] = "0";
  char res[526] = "0";
  int len = strlen(str);
  int j = 0;
  for (int i = len - 1; i >= 0; i--) {
    if ((str[i] == '-') && i == 0) {
      res[j] = '-';
      j++;
      res[j] = '0';
      j++;
    } else if (str[i] == '-' && str[i - 1] == '(') {
      res[j] = '-';
      j++;
      res[j] = '0';
      j++;
    } else {
      res[j] = str[i];
      j++;
    }
  }
  j--;
  len = strlen(res);
  for (int i = 0; i < len; i++) {
    result[i] = res[j];
    j--;
  }
  strcpy(str, result);
  return str;
}

/**
 * @brief changing the sign of the number
 *
 * @param str specified expression
 * @return char* string with the changed sign of the number
 */
char* min_unar(char* str) {
  char result[5] = "(-", res[526] = "", rest[5] = ")";
  int len = strlen(str);
  if (str[len - 1] == ')') {
    for (int i = len - 1; i >= 0; i--) {
      if (str[i] == '(') {
        strcpy(res, str);
        res[i] = '\0';
        i = -9;
      }
    }
    for (int i = len - 1; i >= 0; i--) {
      if (str[i] == '-') {
        strcat(res, &str[i + 1]);
        i = -9;
      }
    }
    res[len - 3] = '\0';
  } else if (is_numbers(str[len - 1])) {
    for (int i = len; i >= 0; i--) {
      if (is_minus(str[i]) || is_sign(str[i]) || str[i] == '(') {
        strncpy(res, str, i + 1);
        strcat(res, result);
        strcat(res, &str[i + 1]);
        strcat(res, rest);
        i = -9;
      } else if (i == 0) {
        strcat(res, result);
        strcat(res, &str[0]);
        strcat(res, rest);
        i = -9;
      }
    }
  } else {
    strcpy(res, str);
  }
  strcpy(str, res);
  return str;
}

/**
 * @brief replace x with its value
 *
 * @param str specified expression
 * @param x value of x
 * @return char* string without x
 */
char* is_x(char* str, char* x) {
  int lenx = strlen(x), len = strlen(str), j = 0;
  char temp[526] = {0}, tempx[526] = "(", x_temp[256];
  strcpy(x_temp, x);
  if (x[0] == '-') {
    strncat(tempx, x, lenx);
    lenx = strlen(tempx);
    tempx[lenx] = ')';
    strcpy(x, tempx);
  }
  lenx = strlen(x);
  for (int i = 0; i < len; i++) {
    if (str[i] != 'x') {
      temp[j] = str[i];
      j++;
    } else if (str[i] == 'x' && i > 0) {
      if (str[i - 1] == '(') {
        int x_len = strlen(x_temp);
        for (int l = 0; l < x_len; l++) {
          temp[j] = x_temp[l];
          j++;
        }
      } else {
        for (int l = 0; l < lenx; l++) {
          temp[j] = x[l];
          j++;
        }
      }
    } else {
      for (int l = 0; l < lenx; l++) {
        temp[j] = x[l];
        j++;
      }
    }
  }
  strcpy(str, temp);
  return str;
}
