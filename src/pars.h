/// \file
#ifndef SRC_PARS_H_
#define SRC_PARS_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc.h"
#include "chek.h"

typedef struct {
  double value;
  int priority;
  int operation;
} t_lex;

typedef struct {
  t_lex lex;
} t_stack;

typedef struct {
  double res;
} t_res;

double is_num(char *str, int i, int len);
double pars_num(char *str, int i);
int pars_function(char *str);
int priority_function(int a);
char *parsing(char *str);
char *input(t_lex *head, int j, char *temp);
double operations(int oper, double first, double second);
double functions(int oper, double first);
char *calculations(t_stack *stackt, int n, char *temp);
char *str_res(double res, int e);

// 1) +
// 2) -
// 3) *
// 4) /
// 5) %
// 6) ^
// 7) sqrt
// 8) acos
// 9) asin
// 10) atan
// 11) sin
// 12) cos
// 13) tan
// 14) ln
// 15) log
// 16) (
// 17) )

#endif  //  SRC_PARS_H_
