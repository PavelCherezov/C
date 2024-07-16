#include "test.h"

START_TEST(memset_1) {
  char str1[] = "Hello, Ai!";
  char str2[] = "Hello, Ai!";

  int ch = ' ';
  my_size_t n = strlen(str1);
  ck_assert_str_eq(memset(str1, ch, n), my_memset(str2, ch, n));
}
END_TEST

START_TEST(memset_2) {
  char str1[] = "Hello, Ai!";
  char str2[] = "Hello, Ai!";

  int ch = ' ';
  my_size_t n = 5;
  ck_assert_str_eq(memset(str1, ch, n), my_memset(str2, ch, n));
}
END_TEST

START_TEST(memset_3) {
  char str1[] = "Hello, Ai!";
  char str2[] = "Hello, Ai!";

  int ch = ' ';
  my_size_t n = 0;
  ck_assert_str_eq(memset(str1, ch, n), my_memset(str2, ch, n));
}
END_TEST

START_TEST(memset_4) {
  char str1[] = "Hello, Ai!";
  char str2[] = "Hello, Ai!";

  int ch = '\0';
  my_size_t n = 0;
  ck_assert_str_eq(memset(str1, ch, n), my_memset(str2, ch, n));
}
END_TEST

START_TEST(memset_5) {
  char str1[] = "Hello, Ai!";
  char str2[] = "Hello, Ai!";

  int ch = '\0';
  my_size_t n = 4;
  ck_assert_str_eq(memset(str1, ch, n), my_memset(str2, ch, n));
}
END_TEST

START_TEST(memset_6) {
  char str1[] = "Hello, Ai!";
  char str2[] = "Hello, Ai!";

  int ch = 81;
  my_size_t n = 7;
  ck_assert_str_eq(memset(str1, ch, n), my_memset(str2, ch, n));
}
END_TEST

Suite *test_memset(void) {
  Suite *s = suite_create("my_MEMSET");
  TCase *tc = tcase_create("memset_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, memset_1);
  tcase_add_test(tc, memset_2);
  tcase_add_test(tc, memset_3);
  tcase_add_test(tc, memset_4);
  tcase_add_test(tc, memset_5);
  tcase_add_test(tc, memset_6);

  suite_add_tcase(s, tc);
  return s;
}
