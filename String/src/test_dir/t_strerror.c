#include "test.h"

START_TEST(strerror_1) {
  for (int i = 0; i < 110; i++) {
    ck_assert_str_eq(strerror(i), my_strerror(i));
  }
}
END_TEST

START_TEST(strerror_2) {
  int num = 10;
  ck_assert_str_eq(strerror(num), my_strerror(num));
}
END_TEST

Suite *test_strerror(void) {
  Suite *s = suite_create("my_STRERROR");
  TCase *tc = tcase_create("strerror_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strerror_1);
  tcase_add_test(tc, strerror_2);

  suite_add_tcase(s, tc);
  return s;
}