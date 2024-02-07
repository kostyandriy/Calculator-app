#include <check.h>

#include "../C_source/Calc.h"

START_TEST(input) {
  char *input = "1 + 2 -   3";
  double res = 0;
  final_func(input, &res, 0);
  ck_assert_double_eq(res, 1 + 2 - 3);

  final_func("1-2*12-3^2", &res, 0);
  ck_assert_double_eq_tol(res, -32, 7);

  final_func("sin(12)-3", &res, 0);
  ck_assert_double_eq_tol(res, sin(12) - 3, 7);

  final_func("ln(12)^3-1*(-12+5)", &res, 0);
  ck_assert_double_eq_tol(res, pow(log(12), 3.0) - 1 * (-12 + 5), 7);

  final_func("1+2-3", &res, 0);
  ck_assert_double_eq_tol(res, 1 + 2 - 3, 7);

  final_func("(cos((-5)))+ln((10/(5*7))^2)-(tan(sin(-3mod2))-5mod3*4/5/7)",
             &res, 0);
  ck_assert_double_eq_tol(res, -0.874353, 7);

  final_func("cos(cos(12))-3-5", &res, 0);
  ck_assert_double_eq_tol(res, cos(cos(12)) - 3 - 5, 7);

  final_func("sin(3^3-ln(12))-12+(-11+20)", &res, 0);
  ck_assert_double_eq_tol(res, sin(27 - log(12)) - 12 + (-11 + 20), 7);

  final_func("sqrt(atan(x))", &res, 0);
  ck_assert_double_eq_tol(res, sqrt(atan(12)), 7);

  final_func("asin(1)", &res, 0);
  ck_assert_double_eq_tol(res, asin(1), 7);

  final_func("log(10)", &res, 0);
  ck_assert_double_eq_tol(res, log10(10), 7);

  final_func("sqrt(4)", &res, 0);
  ck_assert_double_eq_tol(res, sqrt(4), 7);

  final_func("ln(2)", &res, 0);
  ck_assert_double_eq_tol(res, log(2), 7);

  final_func("tan(2)", &res, 0);
  ck_assert_double_eq_tol(res, tan(2), 7);

  final_func("atan(2)", &res, 0);
  ck_assert_double_eq_tol(res, atan(2), 7);

  // test credit_test
  ck_assert_double_eq_tol(per_month_ann(123456, 12.5 / 1200., 10), 13063.89, 3);
  double total = 0;
  ck_assert_double_eq_tol(per_month_diff(123456, 12.5 / 1200., 10, &total),
                          12474.20, 3);
  ck_assert_double_eq_tol(total, 130529.00, 3);
}
END_TEST

int main(void) {
  Suite *s;
  TCase *tc;
  SRunner *sr;

  s = suite_create("tests");
  tc = tcase_create("test");

  tcase_add_test(tc, input);

  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
