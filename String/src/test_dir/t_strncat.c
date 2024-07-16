#include "test.h"

START_TEST(strncat_1) {
  char s1[30] = "Hello, world!";
  char s2[30] = "Hello, world!";
  char s3[] = "Hello, world!";
  my_size_t n = 1;
  ck_assert_pstr_eq(strncat(s1, s3, n), my_strncat(s2, s3, n));
}
END_TEST

START_TEST(strncat_2) {
  char s1[30] = "Hello, world!";
  char s2[30] = "Hello, world!";
  char s3[] = "\0";
  my_size_t n = 1;
  ck_assert_pstr_eq(strncat(s1, s3, n), my_strncat(s2, s3, n));
}
END_TEST

START_TEST(strncat_3) {
  char s1[30] = "Hello, world!";
  char s2[30] = "Hello, world!";
  char s3[] = "\n\0\\d\f\\g\7";
  my_size_t n = 3;
  ck_assert_pstr_eq(strncat(s1, s3, n), my_strncat(s2, s3, n));
}
END_TEST

START_TEST(strncat_4) {
  char s1[30] = "Hello, world!";
  char s2[30] = "Hello, world!";
  char s3[] = "";
  my_size_t n = 0;
  ck_assert_pstr_eq(strncat(s1, s3, n), my_strncat(s2, s3, n));
}
END_TEST

START_TEST(strncat_5) {
  char s1[30] = "";
  char s2[30] = "";
  char s3[] = "Hello, world!";
  my_size_t n = 13;
  ck_assert_pstr_eq(strncat(s1, s3, n), my_strncat(s2, s3, n));
}
END_TEST

START_TEST(strncat_6) {
  char str1[100] = "Hello, world!";
  char str2[100] = "Hello, world!";
  char str3[] = "My name is Arbokboe";
  my_size_t n = 6;
  ck_assert_pstr_eq(strncat(str1, str3, n), my_strncat(str2, str3, n));
}
END_TEST

START_TEST(strncat_7) {
  char str1[30] = "";
  char str2[30] = "";
  char str3[] = "Hello, world!";
  my_size_t n = 3;
  ck_assert_pstr_eq(strncat(str1, str3, n), my_strncat(str2, str3, n));
}
END_TEST

START_TEST(strncat_8) {
  char str1[100] = "Hello, world!";
  char str2[100] = "Hello, world!";
  char str3[] = "My name is Arbokboe.";
  my_size_t n = 2;
  ck_assert_pstr_eq(strncat(str1, str3, n), my_strncat(str2, str3, n));
}
END_TEST

START_TEST(strncat_9) {
  char str1[100] = "";
  char str2[100] = "";
  char str3[] = "";
  my_size_t n = 10;
  ck_assert_pstr_eq(strncat(str1, str3, n), my_strncat(str2, str3, n));
}
END_TEST

START_TEST(strncat_10) {
  char str1[100] = "Hello\0, world!";
  char str2[100] = "Hello\0, world!";
  char str3[] = "My name is\0 Arbokboe.";
  my_size_t n = 15;
  ck_assert_pstr_eq(strncat(str1, str3, n), my_strncat(str2, str3, n));
}
END_TEST

START_TEST(strncat_11) {
  char str1[100] = "Hello, world!";
  char str2[100] = "Hello, world!";
  char str3[] = "\0";
  my_size_t n = 1;
  ck_assert_pstr_eq(strncat(str1, str3, n), my_strncat(str2, str3, n));
}
END_TEST

START_TEST(strncat_12) {
  char str1[100] = "Hello, world!";
  char str2[100] = "Hello, world!";
  char str3[] = "\0";
  my_size_t n = 0;
  ck_assert_pstr_eq(strncat(str1, str3, n), my_strncat(str2, str3, n));
}
END_TEST

START_TEST(strncat_13) {
  char str1[100] = "Hello, world!";
  char str2[100] = "Hello, world!";
  char str3[] = "\0\0\0\0";
  my_size_t n = 4;
  ck_assert_pstr_eq(strncat(str1, str3, n), my_strncat(str2, str3, n));
}
END_TEST

START_TEST(strncat_14) {
  char str1[100] = "Hello, world!";
  char str2[100] = "Hello, world!";
  char str3[] = "";
  my_size_t n = 2;
  ck_assert_pstr_eq(strncat(str1, str3, n), my_strncat(str2, str3, n));
}
END_TEST

START_TEST(strncat_15) {
  char str1[100] = "Hello, world!\0\0\0";
  char str2[100] = "Hello, world!\0\0\0";
  char str3[] = "My name is Arbokboe";
  my_size_t n = 0;
  ck_assert_pstr_eq(strncat(str1, str3, n), my_strncat(str2, str3, n));
}
END_TEST

Suite *test_strncat(void) {
  Suite *s = suite_create("my_STRNCAT");
  TCase *tc = tcase_create("strncat_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strncat_1);
  tcase_add_test(tc, strncat_2);
  tcase_add_test(tc, strncat_3);
  tcase_add_test(tc, strncat_4);
  tcase_add_test(tc, strncat_5);
  tcase_add_test(tc, strncat_6);
  tcase_add_test(tc, strncat_7);
  tcase_add_test(tc, strncat_8);
  tcase_add_test(tc, strncat_9);
  tcase_add_test(tc, strncat_10);
  tcase_add_test(tc, strncat_11);
  tcase_add_test(tc, strncat_12);
  tcase_add_test(tc, strncat_13);
  tcase_add_test(tc, strncat_14);
  tcase_add_test(tc, strncat_15);

  suite_add_tcase(s, tc);
  return s;
}