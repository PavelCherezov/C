#include "test.h"

START_TEST(strncpy_1) {
  char str1[20] = "Hello, world!";
  char str2[20] = "Hello, world!";
  char str3[] = "Good";
  my_size_t n = 5;
  ck_assert_pstr_eq(strncpy(str1, str3, n), my_strncpy(str2, str3, n));
}
END_TEST

START_TEST(strncpy_2) {
  char str1[20] = "Hello, world!";
  char str2[20] = "Hello, world!";
  char str3[] = "\0";
  my_size_t n = 1;
  ck_assert_pstr_eq(strncpy(str1, str3, n), my_strncpy(str2, str3, n));
}
END_TEST

START_TEST(strncpy_4) {
  char str1[5] = "";
  char str2[5] = "";
  char str3[] = "";
  my_size_t n = 0;
  ck_assert_pstr_eq(strncpy(str1, str3, n), my_strncpy(str2, str3, n));
}
END_TEST

START_TEST(strncpy_5) {
  char str1[70] = "";
  char str2[70] = "";
  char str3[] = "Cats are wonderful pets that many people love";
  my_size_t n = strlen(str3);
  ck_assert_pstr_eq(strncpy(str1, str3, n), my_strncpy(str2, str3, n));
}
END_TEST

START_TEST(strncpy_6) {
  char str1[5] = "";
  char str2[5] = "";
  char str3[] = "\0";
  my_size_t n = 1;
  ck_assert_pstr_eq(strncpy(str1, str3, n), my_strncpy(str2, str3, n));
}
END_TEST

Suite *test_strncpy(void) {
  Suite *s = suite_create("my_STRNCPY");
  TCase *tc = tcase_create("strncpy_tc");

  tcase_add_test(tc, strncpy_1);
  tcase_add_test(tc, strncpy_2);
  tcase_add_test(tc, strncpy_4);
  tcase_add_test(tc, strncpy_5);
  tcase_add_test(tc, strncpy_6);

  suite_add_tcase(s, tc);
  return s;
}