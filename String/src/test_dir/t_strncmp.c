#include "test.h"

START_TEST(strncmp_1) {
  char str1[] = "Hello, world!";
  char str2[] = "Hello, world!";
  my_size_t n = 14;
  int n1 = strncmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_strncmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_2) {
  char str1[] = "Hello, world!";
  char str2[] = "Hello, worldj";
  my_size_t n = 14;
  int n1 = strncmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_strncmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_3) {
  char str1[] = "";
  char str2[] = "";
  my_size_t n = 1;
  int n1 = strncmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_strncmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_4) {
  char str1[] = "f";
  char str2[] = "";
  my_size_t n = 1;
  int n1 = strncmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_strncmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_5) {
  char str1[] = "";
  char str2[] = "j";
  my_size_t n = 1;
  int n1 = strncmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_strncmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_6) {
  char str1[] = "1242434246364377659";
  char str2[] = "1242434246364377659";
  my_size_t n = 19;
  int n1 = strncmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_strncmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_7) {
  char str1[] = "1242434246364377659";
  char str2[] = "1242434246364377659";
  my_size_t n = 2;
  int n1 = strncmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_strncmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_8) {
  char str1[] = "g124243425";
  char str2[] = "124243424";
  my_size_t n = 0;
  int n1 = strncmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_strncmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(strncmp_9) {
  char str1[] = "";
  char str2[] = "";
  my_size_t n = 1;
  int n1 = strncmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_strncmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

Suite *test_strncmp(void) {
  Suite *s = suite_create("my_STRNCMP");
  TCase *tc = tcase_create("strncmp_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strncmp_1);
  tcase_add_test(tc, strncmp_2);
  tcase_add_test(tc, strncmp_3);
  tcase_add_test(tc, strncmp_4);
  tcase_add_test(tc, strncmp_5);
  tcase_add_test(tc, strncmp_6);
  tcase_add_test(tc, strncmp_7);
  tcase_add_test(tc, strncmp_8);
  tcase_add_test(tc, strncmp_9);

  suite_add_tcase(s, tc);
  return s;
}