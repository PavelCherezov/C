#include "test.h"

START_TEST(memcmp_1) {
  char str1[] = "Hello Ai!";
  char str2[] = "Hello Ai!";
  my_size_t n = 6;
  int n1 = memcmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_memcmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_2) {
  char str1[] = "Hello Ai!";
  char str2[] = "Hello Ai!";
  my_size_t n = 9;
  int n1 = memcmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_memcmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_3) {
  char str1[] = "Hello Ai!";
  char str2[] = "Hello Ai!";
  my_size_t n = 0;
  int n1 = memcmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_memcmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_4) {
  char str1[] = "Hello Ai!";
  char str2[] = "Hello Ai!";
  my_size_t n = 10;
  int n1 = memcmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_memcmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_5) {
  char str1[] = "9960356";
  char str2[] = "9960356";
  my_size_t n = 0;
  int n1 = memcmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_memcmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_6) {
  char str1[] = "9960356";
  char str2[] = "9960356";
  my_size_t n = 6;
  int n1 = memcmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_memcmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_7) {
  char str1[] = "9960356";
  char str2[] = "9960356";
  my_size_t n = 7;
  int n1 = memcmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_memcmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_8) {
  char str1[] = "9960356";
  char str2[] = "99603569";
  my_size_t n = 8;
  int n1 = memcmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_memcmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_9) {
  char str1[] = "9960356";
  char str2[] = "996035T";
  my_size_t n = 7;
  int n1 = memcmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_memcmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_10) {
  char str1[] = "9960356";
  char str2[] = "996035T";
  my_size_t n = 6;
  int n1 = memcmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_memcmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_11) {
  char str1[] =
      "Do not forget to increase the variable used in the condition, otherwise "
      "the loop will never end!";
  char str2[] =
      "Do not forget to increase the variable used in the condition, otherwise "
      "the loop will never end!";
  my_size_t n = 100;
  int n1 = memcmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_memcmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(memcmp_12) {
  char str1[] =
      "Do not forget to increase the variable used in the condition, otherwise "
      "the loop will never end!";
  char str2[] =
      "Doo not forget to increase the variable used in the condition, "
      "otherwise the loop will never end!";
  my_size_t n = 96;
  int n1 = memcmp(str1, str2, n);
  n1 = n1 > 0 ? 1 : n1 == 0 ? 0 : -1;
  int n2 = my_memcmp(str1, str2, n);
  n2 = n2 > 0 ? 1 : n2 == 0 ? 0 : -1;
  ck_assert_int_eq(n1, n2);
}
END_TEST

Suite *test_memcmp(void) {
  Suite *s = suite_create("my_MEMCMP");  //создаем тестовый сценарий
  TCase *tc = tcase_create("memcmp_tc");  //создаем тестовый случай

  tcase_add_test(tc, memcmp_1);
  tcase_add_test(tc, memcmp_2);
  tcase_add_test(tc, memcmp_3);
  tcase_add_test(tc, memcmp_4);
  tcase_add_test(tc, memcmp_5);
  tcase_add_test(tc, memcmp_6);
  tcase_add_test(tc, memcmp_7);
  tcase_add_test(tc, memcmp_8);
  tcase_add_test(tc, memcmp_9);
  tcase_add_test(tc, memcmp_10);
  tcase_add_test(tc, memcmp_11);
  tcase_add_test(tc, memcmp_12);

  suite_add_tcase(
      s,
      tc);  //добавляет созданный тестовый случай "tc" в тестовый сценарий "s".

  return s;
}