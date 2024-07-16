#include "my_test.h"

#define TRUE 1
#define FALSE 0

START_TEST(is_equal_test_1) {
  my_decimal value_1 = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};  //        0
  my_decimal value_2 = {
      {0x00000000, 0x00000000, 0x00000000, 0x80000000}};  //       -0
  my_decimal value_3 = {
      {0x00000000, 0x00000000, 0x00000000, 0x00050000}};  //  0.00000

  ck_assert_int_eq(TRUE, my_is_equal(value_1, value_1));
  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_2));
  ck_assert_int_eq(TRUE, my_is_equal(value_3, value_3));

  ck_assert_int_eq(TRUE, my_is_equal(value_1, value_2));
  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_1));
  ck_assert_int_eq(TRUE, my_is_equal(value_1, value_3));
  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_3));
}
END_TEST

START_TEST(is_equal_test_2) {
  my_decimal value_1 = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};  //  0
  my_decimal value_2 = {
      {0x00000001, 0x00000000, 0x00000000, 0x00000000}};  //  1
  my_decimal value_3 = {
      {0x00000001, 0x00000000, 0x00000000, 0x80000000}};  // -1

  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_2));
  ck_assert_int_eq(TRUE, my_is_equal(value_3, value_3));

  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_2));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_3));
  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_3));
}
END_TEST

START_TEST(is_equal_test_3) {
  my_decimal value_1 = {
      {0x00000001, 0x00000000, 0x00000000, 0x00000000}};  //     1
  my_decimal value_2 = {
      {0x0000000A, 0x00000000, 0x00000000, 0x00010000}};  //   1.0
  my_decimal value_3 = {
      {0x00000064, 0x00000000, 0x00000000, 0x00020000}};  //  1.00
  my_decimal value_4 = {
      {0x000003E8, 0x00000000, 0x00000000, 0x00030000}};  // 1.000

  ck_assert_int_eq(TRUE, my_is_equal(value_1, value_2));
  ck_assert_int_eq(TRUE, my_is_equal(value_1, value_3));
  ck_assert_int_eq(TRUE, my_is_equal(value_1, value_4));
  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_3));
  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_4));
  ck_assert_int_eq(TRUE, my_is_equal(value_3, value_4));
}
END_TEST

START_TEST(is_equal_test_4) {
  my_decimal value_1 = {
      {0x00000001, 0x00000000, 0x00000000, 0x80000000}};  //     -1
  my_decimal value_2 = {
      {0x0000000A, 0x00000000, 0x00000000, 0x80010000}};  //   -1.0
  my_decimal value_3 = {
      {0x00000064, 0x00000000, 0x00000000, 0x80020000}};  //  -1.00
  my_decimal value_4 = {
      {0x000003E8, 0x00000000, 0x00000000, 0x80030000}};  // -1.000

  ck_assert_int_eq(TRUE, my_is_equal(value_1, value_2));
  ck_assert_int_eq(TRUE, my_is_equal(value_1, value_3));
  ck_assert_int_eq(TRUE, my_is_equal(value_1, value_4));
  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_3));
  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_4));
  ck_assert_int_eq(TRUE, my_is_equal(value_3, value_4));
}
END_TEST

START_TEST(is_equal_test_5) {
  my_decimal value_1 = {{0x00000001, 0x00000000, 0x00000000,
                          0x00000000}};  //                    1
  my_decimal value_2 = {{0x00000000, 0x00000001, 0x00000000,
                          0x00000000}};  //           4294967296
  my_decimal value_3 = {{0x00000000, 0x00000000, 0x00000001,
                          0x00000000}};  //   1.844674407371e+19
  my_decimal value_4 = {{0x00000000, 0x00000000, 0x10000000,
                          0x00000000}};  //  3.9614081257132e+28

  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_2));
  ck_assert_int_eq(TRUE, my_is_equal(value_3, value_3));
  ck_assert_int_eq(TRUE, my_is_equal(value_4, value_4));

  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_2));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_3));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_4));

  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_3));
  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_4));

  ck_assert_int_eq(FALSE, my_is_equal(value_3, value_4));
}
END_TEST

START_TEST(is_equal_test_6) {
  my_decimal value_1 = {{0x00000001, 0x00000000, 0x00000000,
                          0x80000000}};  //                   -1
  my_decimal value_2 = {{0x00000000, 0x00000001, 0x00000000,
                          0x80000000}};  //          -4294967296
  my_decimal value_3 = {{0x00000000, 0x00000000, 0x00000001,
                          0x80000000}};  //  -1.844674407371e+19
  my_decimal value_4 = {{0x00000000, 0x00000000, 0x10000000,
                          0x80000000}};  // -3.9614081257132e+28

  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_2));
  ck_assert_int_eq(TRUE, my_is_equal(value_3, value_3));
  ck_assert_int_eq(TRUE, my_is_equal(value_4, value_4));

  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_2));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_3));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_4));

  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_3));
  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_4));

  ck_assert_int_eq(FALSE, my_is_equal(value_3, value_4));
}
END_TEST

START_TEST(is_equal_test_7) {
  my_decimal value_1 = {{0x00001979, 0x00000000, 0x00000000,
                          0x00000000}};  //                 6521
  my_decimal value_2 = {{0x00012189, 0x00000000, 0x00000000,
                          0x00000000}};  //                74121
  my_decimal value_3 = {{0x05D19D1B, 0x00000000, 0x00000000,
                          0x00000000}};  //             97623323
  my_decimal value_4 = {{0x00001979, 0x00000000, 0x00000000,
                          0x80000000}};  //                -6521
  my_decimal value_5 = {{0x00012189, 0x00000000, 0x00000000,
                          0x80000000}};  //               -74121
  my_decimal value_6 = {{0x05D19D1B, 0x00000000, 0x00000000,
                          0x80000000}};  //            -97623323

  ck_assert_int_eq(TRUE, my_is_equal(value_1, value_1));
  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_2));
  ck_assert_int_eq(TRUE, my_is_equal(value_3, value_3));
  ck_assert_int_eq(TRUE, my_is_equal(value_4, value_4));
  ck_assert_int_eq(TRUE, my_is_equal(value_5, value_5));
  ck_assert_int_eq(TRUE, my_is_equal(value_6, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_2));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_3));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_4));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_3));
  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_4));
  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_3, value_4));
  ck_assert_int_eq(FALSE, my_is_equal(value_3, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_3, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_4, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_4, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_5, value_6));
}
END_TEST

START_TEST(is_equal_test_8) {
  my_decimal value_1 = {{0x89E7FFFF, 0x8AC72304, 0x00000000,
                          0x00000000}};  //  9999999999999999999
  my_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
                          0x00000000}};  //   1.844674407371e+19
  my_decimal value_3 = {{0xFFFFFFFF, 0x05D19D1B, 0x00012189,
                          0x00000000}};  //  1.3672915367764e+24
  my_decimal value_4 = {{0x89E7FFFF, 0x8AC72304, 0x00000000,
                          0x80000000}};  // -9999999999999999999
  my_decimal value_5 = {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
                          0x80000000}};  //  -1.844674407371e+19
  my_decimal value_6 = {{0xFFFFFFFF, 0x05D19D1B, 0x00012189,
                          0x80000000}};  // -1.3672915367764e+24

  ck_assert_int_eq(TRUE, my_is_equal(value_1, value_1));
  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_2));
  ck_assert_int_eq(TRUE, my_is_equal(value_3, value_3));
  ck_assert_int_eq(TRUE, my_is_equal(value_4, value_4));
  ck_assert_int_eq(TRUE, my_is_equal(value_5, value_5));
  ck_assert_int_eq(TRUE, my_is_equal(value_6, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_2));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_3));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_4));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_3));
  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_4));
  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_3, value_4));
  ck_assert_int_eq(FALSE, my_is_equal(value_3, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_3, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_4, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_4, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_5, value_6));
}
END_TEST

START_TEST(is_equal_test_9) {
  my_decimal value_1 = {{0x00001979, 0x00000000, 0x00000000,
                          0x00020000}};  //                65.21
  my_decimal value_2 = {{0x00001979, 0x00000000, 0x00000000,
                          0x00000000}};  //                 6521
  my_decimal value_3 = {{0x006380A8, 0x00000000, 0x00000000,
                          0x00030000}};  //             6521.000
  my_decimal value_4 = {{0x00001979, 0x00000000, 0x00000000,
                          0x80020000}};  //               -65.21
  my_decimal value_5 = {{0x00001979, 0x00000000, 0x00000000,
                          0x80000000}};  //                -6521
  my_decimal value_6 = {{0x006380A8, 0x00000000, 0x00000000,
                          0x80030000}};  //            -6521.000

  ck_assert_int_eq(TRUE, my_is_equal(value_1, value_1));
  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_2));
  ck_assert_int_eq(TRUE, my_is_equal(value_3, value_3));
  ck_assert_int_eq(TRUE, my_is_equal(value_4, value_4));
  ck_assert_int_eq(TRUE, my_is_equal(value_5, value_5));
  ck_assert_int_eq(TRUE, my_is_equal(value_6, value_6));
  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_3));
  ck_assert_int_eq(TRUE, my_is_equal(value_3, value_2));
  ck_assert_int_eq(TRUE, my_is_equal(value_6, value_5));
  ck_assert_int_eq(TRUE, my_is_equal(value_5, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_2));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_3));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_4));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_4));
  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_3, value_4));
  ck_assert_int_eq(FALSE, my_is_equal(value_3, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_3, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_4, value_6));
}
END_TEST

START_TEST(is_equal_test_10) {
  my_decimal value_1 = {{0x89E7FFFF, 0x8AC72304, 0x00000000,
                          0x00000000}};  //    9999999999999999999
  my_decimal value_2 = {{0x89E7FFFF, 0x8AC72304, 0x00000000,
                          0x000A0000}};  //   999999999.9999999999
  my_decimal value_3 = {{0x89E7FFFF, 0x8AC72304, 0x00000000,
                          0x00130000}};  //  0.9999999999999999999
  my_decimal value_4 = {{0x89E7FFFF, 0x8AC72304, 0x00000000,
                          0x80000000}};  //   -9999999999999999999
  my_decimal value_5 = {{0x89E7FFFF, 0x8AC72304, 0x00000000,
                          0x800A0000}};  //  -999999999.9999999999
  my_decimal value_6 = {{0x89E7FFFF, 0x8AC72304, 0x00000000,
                          0x80130000}};  // -0.9999999999999999999

  ck_assert_int_eq(TRUE, my_is_equal(value_1, value_1));
  ck_assert_int_eq(TRUE, my_is_equal(value_2, value_2));
  ck_assert_int_eq(TRUE, my_is_equal(value_3, value_3));
  ck_assert_int_eq(TRUE, my_is_equal(value_4, value_4));
  ck_assert_int_eq(TRUE, my_is_equal(value_5, value_5));
  ck_assert_int_eq(TRUE, my_is_equal(value_6, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_2));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_3));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_4));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_1, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_3));
  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_4));
  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_2, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_3, value_4));
  ck_assert_int_eq(FALSE, my_is_equal(value_3, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_3, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_4, value_5));
  ck_assert_int_eq(FALSE, my_is_equal(value_4, value_6));

  ck_assert_int_eq(FALSE, my_is_equal(value_5, value_6));
}
END_TEST

Suite* my_is_equal_suite(void) {
  Suite* s;
  s = suite_create("\033[33mmy_is_equal\033[0m");

  TCase* tc_core;
  tc_core = tcase_create("my_is_equal_core");

  tcase_add_test(tc_core, is_equal_test_1);
  tcase_add_test(tc_core, is_equal_test_2);
  tcase_add_test(tc_core, is_equal_test_3);
  tcase_add_test(tc_core, is_equal_test_4);
  tcase_add_test(tc_core, is_equal_test_5);
  tcase_add_test(tc_core, is_equal_test_6);
  tcase_add_test(tc_core, is_equal_test_7);
  tcase_add_test(tc_core, is_equal_test_8);
  tcase_add_test(tc_core, is_equal_test_9);
  tcase_add_test(tc_core, is_equal_test_10);

  suite_add_tcase(s, tc_core);

  return s;
}
