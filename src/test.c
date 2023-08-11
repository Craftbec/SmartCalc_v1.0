#include <check.h>

#include "calc.h"
#include "chek.h"
#include "pars.h"

START_TEST(test_1) {
  char str[256] = "x+5";
  char x[256] = "5";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "10");
}
END_TEST
START_TEST(test_2) {
  char str[256] = "x*5";
  char x[256] = "5";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "25");
}
END_TEST
START_TEST(test_3) {
  char str[256] = "x/5";
  char x[256] = "5";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "1");
}
END_TEST
START_TEST(test_4) {
  char str[256] = "x-5";
  char x[256] = "5";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "0");
}
END_TEST
START_TEST(test_5) {
  char str[256] = "cos(x)";
  char x[256] = "0";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "1");
}
END_TEST
START_TEST(test_6) {
  char str[256] = "sin(x)";
  char x[256] = "0";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "0");
}
END_TEST
START_TEST(test_7) {
  char str[256] = "tan(x)";
  char x[256] = "0";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "0");
}
END_TEST
START_TEST(test_8) {
  char str[256] = "atan(x)";
  char x[256] = "0";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "0");
}
END_TEST
START_TEST(test_9) {
  char str[256] = "asin(x)";
  char x[256] = "0";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "0");
}
END_TEST
START_TEST(test_10) {
  char str[256] = "acos(x)";
  char x[256] = "1";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "0");
}
END_TEST
START_TEST(test_11) {
  char str[256] = "x^5";
  char x[256] = "5";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "3125");
}
END_TEST
START_TEST(test_12) {
  char str[256] = "sqrt(x)";
  char x[256] = "81";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "9");
}
END_TEST
START_TEST(test_13) {
  char str[256] = "log(x)";
  char x[256] = "10";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "1");
}
END_TEST
START_TEST(test_14) {
  char str[256] = "ln(x)";
  char x[256] = "1";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "0");
}
END_TEST
START_TEST(test_15) {
  char str[256] = "x%15";
  char x[256] = "43";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "13");
}
END_TEST
START_TEST(test_16) {
  char str[256] = "+15";
  char x[256] = "43";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "Incorrect expression");
}
END_TEST
START_TEST(test_17) {
  char str[256] = "15(5+x)";
  char x[256] = "43";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "Incorrect expression");
}
END_TEST
START_TEST(test_18) {
  char str[256] = "15sqrt(x)";
  char x[256] = "4";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "Incorrect expression");
}
END_TEST
START_TEST(test_19) {
  char str[256] = "-15*sqrt(x)";
  char x[256] = "4";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "-30");
}
END_TEST

START_TEST(test_21) {
  char str[256] = "(-15+4)*x";
  char x[256] = "2";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "-22");
}
END_TEST
START_TEST(test_22) {
  char str[256] = "(-15.4.5+4)*x";
  char x[256] = "2";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "Incorrect expression");
}
END_TEST
START_TEST(test_23) {
  char str[256] = "x^x^x";
  char x[256] = "2";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "16");
}
END_TEST
START_TEST(test_24) {
  char str[256] = "4-(15+x)";
  char x[256] = "2";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "-13");
}
END_TEST
START_TEST(test_25) {
  char str[256] = "x+x-x";
  char x[256] = "2";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "2");
}
END_TEST
START_TEST(test_26) {
  char str[256] = "x*x-x";
  char x[256] = "2";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "2");
}
END_TEST
START_TEST(test_27) {
  char str[256] = "x^x^2";
  char x[256] = "10";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "1.000000e+1");
}
END_TEST

START_TEST(test_28) {
  char *str = calloc(256, sizeof(char));
  free_str(str);
}

START_TEST(test_29) {
  char str[256] = "2";
  ck_assert_str_eq(min_unar(str), "(-2)");
}

END_TEST
START_TEST(test_30) {
  char str[256] = "(-2)";
  ck_assert_str_eq(min_unar(str), "2");
}
END_TEST
START_TEST(test_31) {
  char str[256] = "2+";
  ck_assert_str_eq(min_unar(str), "2+");
}
END_TEST
START_TEST(test_32) {
  char str[256] = "2+(-2)";
  ck_assert_str_eq(min_unar(str), "2+2");
}
END_TEST
START_TEST(test_33) {
  char str[256] = "2+2";
  ck_assert_str_eq(min_unar(str), "2+(-2)");
}
END_TEST
START_TEST(test_34) {
  char str[256] = "2+x";
  char x[256] = "-36";
  is_x(str, x);
  ck_assert_str_eq(calculate(str), "-34");
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_1);
  tcase_add_test(tc1_1, test_2);
  tcase_add_test(tc1_1, test_3);
  tcase_add_test(tc1_1, test_4);
  tcase_add_test(tc1_1, test_5);
  tcase_add_test(tc1_1, test_6);
  tcase_add_test(tc1_1, test_7);
  tcase_add_test(tc1_1, test_8);
  tcase_add_test(tc1_1, test_9);
  tcase_add_test(tc1_1, test_10);
  tcase_add_test(tc1_1, test_11);
  tcase_add_test(tc1_1, test_12);
  tcase_add_test(tc1_1, test_13);
  tcase_add_test(tc1_1, test_14);
  tcase_add_test(tc1_1, test_15);
  tcase_add_test(tc1_1, test_16);
  tcase_add_test(tc1_1, test_17);
  tcase_add_test(tc1_1, test_18);
  tcase_add_test(tc1_1, test_19);
  tcase_add_test(tc1_1, test_21);
  tcase_add_test(tc1_1, test_22);
  tcase_add_test(tc1_1, test_23);
  tcase_add_test(tc1_1, test_24);
  tcase_add_test(tc1_1, test_25);
  tcase_add_test(tc1_1, test_26);
  tcase_add_test(tc1_1, test_27);
  tcase_add_test(tc1_1, test_28);
  tcase_add_test(tc1_1, test_29);
  tcase_add_test(tc1_1, test_30);
  tcase_add_test(tc1_1, test_31);
  tcase_add_test(tc1_1, test_32);
  tcase_add_test(tc1_1, test_33);
  tcase_add_test(tc1_1, test_34);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
