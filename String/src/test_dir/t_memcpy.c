#include "test.h"

START_TEST(memcpy_1) {
  char str1[] = "Hello, Ai!";
  char str2[] = "Hello, Ai!";
  char str3[] = "Code Good";
  my_size_t n = 9;
  ck_assert_str_eq(memcpy(str1, str3, n), my_memcpy(str2, str3, n));
}
END_TEST

START_TEST(memcpy_2) {
  char str1[] = "Hello, Ai!";
  char str2[] = "Hello, Ai!";
  char str3[] = "r";
  my_size_t n = 0;
  ck_assert_str_eq(memcpy(str1, str3, n), my_memcpy(str2, str3, n));
}
END_TEST

START_TEST(memcpy_3) {
  char str1[] = "Hello, Ai!";
  char str2[] = "Hello, Ai!";
  char str3[] = "\0";
  my_size_t n = 1;
  ck_assert_str_eq(memcpy(str1, str3, n), my_memcpy(str2, str3, n));
}
END_TEST

START_TEST(memcpy_4) {
  char str1[] = "Hello, Ai!";
  char str2[] = "Hello, Ai!";
  char str3[] = "New string";
  my_size_t n = strlen(str3);
  ck_assert_str_eq(memcpy(str1, str3, n), my_memcpy(str2, str3, n));
}
END_TEST

START_TEST(memcpy_5) {
  char str1[] = "Hello, Ai!";
  char str2[] = "Hello, Ai!";
  char str3[] = "123";
  my_size_t n = strlen(str3);
  ck_assert_str_eq(memcpy(str1, str3, n), my_memcpy(str2, str3, n));
}
END_TEST

START_TEST(memcpy_6) {
  char str1[] = "Hello, Ai!";
  char str2[] = "Hello, Ai!";
  char str3[] = "@#$%";
  my_size_t n = strlen(str3);
  ck_assert_str_eq(memcpy(str1, str3, n), my_memcpy(str2, str3, n));
}
END_TEST

START_TEST(memcpy_7) {
  char str1[] = "1234/4321";
  char str2[] = "1234/4321";
  char str3[] = "567";
  my_size_t n = strlen(str3);
  ck_assert_str_eq(memcpy(str1, str3, n), my_memcpy(str2, str3, n));
}
END_TEST

START_TEST(memcpy_8) {
  char str1[] = "1234/4321";
  char str2[] = "1234/4321";
  char str3[] = "cum";
  my_size_t n = strlen(str3);
  ck_assert_str_eq(memcpy(str1, str3, n), my_memcpy(str2, str3, n));
}
END_TEST

START_TEST(memcpy_9) {
  char str1[] = "1234/4321";
  char str2[] = "1234/4321";
  char str3[] = "cum++";
  my_size_t n = strlen(str3);
  ck_assert_str_eq(memcpy(str1, str3, n), my_memcpy(str2, str3, n));
}
END_TEST

START_TEST(memcpy_10) {
  char str1[] = "1234/4321";
  char str2[] = "1234/4321";
  char str3[] = "R";
  my_size_t n = strlen(str3);
  ck_assert_str_eq(memcpy(str1, str3, n), my_memcpy(str2, str3, n));
}
END_TEST

Suite *test_memcpy(void) {
  Suite *s = suite_create("my_MEMCPY");
  TCase *tc = tcase_create("memcpy_tc");

  tcase_add_test(tc, memcpy_1);
  tcase_add_test(tc, memcpy_2);
  tcase_add_test(tc, memcpy_3);
  tcase_add_test(tc, memcpy_4);
  tcase_add_test(tc, memcpy_5);
  tcase_add_test(tc, memcpy_6);
  tcase_add_test(tc, memcpy_7);
  tcase_add_test(tc, memcpy_8);
  tcase_add_test(tc, memcpy_9);
  tcase_add_test(tc, memcpy_10);

  suite_add_tcase(s, tc);
  return s;
}