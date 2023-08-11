/// \file
#ifndef SRC_CHEK_H_
#define SRC_CHEK_H_

#include <string.h>

#include "pars.h"

int proverka(char* str);
int is_numbers(char a);
int is_sign(char a);
int is_minus(char a);
int is_mod(char* str, int i, int len);
int dot(char* str, int i, int len);
char* unar(char* str);
char* min_unar(char* str);
char* is_x(char* str, char* x);

#endif  //  SRC_CHEK_H_
