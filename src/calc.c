/// \file
#include "calc.h"

/**
 * @brief calculator
 *
 * @param str - the specified expression
 * @return char* calculation result
 */
char *calculate(char *str) {
  if (proverka(str)) {
    str = unar(str);
    str = parsing(str);
  } else {
    sprintf(str, "%s", "Incorrect expression");
  }
  return str;
}
/**
 * @brief clearing memory
 *
 * @param ctr the string to be cleared
 */
void free_str(char *ctr) {
  if (ctr) {
    free(ctr);
  }
}
