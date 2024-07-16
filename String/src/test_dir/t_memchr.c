#include "test.h"

START_TEST(memchr_1) {
  char str[] = "Hello, Ai!";
  int ch = 'i';
  my_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_2) {
  char str[] = "Hello, Ai!";
  int ch = '!';
  my_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_3) {
  char str[] = "Hello, Ai!";
  int ch = 'e';
  my_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_4) {
  char str[] = "Hello, Ai!";
  int ch = 'H';
  my_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_5) {
  char str[] = "Hello, Ai!";
  int ch = 'o';
  my_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_6) {
  char str[] = "235940";
  int ch = '5';
  my_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_7) {
  char str[] = "235940";
  int ch = '3';
  my_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_8) {
  char str[] = "235940";
  int ch = '4';
  my_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_9) {
  char str[] = "235940!";
  int ch = '\0';
  my_size_t len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_10) {
  char str[] = "235940";
  int ch = '2';
  my_size_t len = 7;
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

Suite *test_memchr(void) {
  Suite *s = suite_create("my_MEMCHR");  //создаем тестовый сценарий
  TCase *tc = tcase_create("memchr_tc");  //создаем тестовый случай

  tcase_add_test(
      tc,
      memchr_1);  //добавляет тестовый случай "memchr_1" в тестовый случай "tc".
  tcase_add_test(tc, memchr_2);
  tcase_add_test(tc, memchr_3);
  tcase_add_test(tc, memchr_4);
  tcase_add_test(tc, memchr_5);
  tcase_add_test(tc, memchr_6);
  tcase_add_test(tc, memchr_7);
  tcase_add_test(tc, memchr_8);
  tcase_add_test(tc, memchr_9);
  tcase_add_test(tc, memchr_10);
  suite_add_tcase(
      s,
      tc);  //добавляет созданный тестовый случай "tc" в тестовый сценарий "s".

  return s;
}
