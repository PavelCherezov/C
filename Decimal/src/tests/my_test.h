#ifndef MY_TEST_H
#define MY_TEST_H

#include <check.h>
#include <stdio.h>

#include "../my_decimal.h"

#define TRUE 1
#define FALSE 0

// Arithmetic Operators
Suite* my_add_suite(void);
Suite* my_sub_suite(void);
Suite* my_mul_suite(void);
Suite* my_div_suite(void);

// Comparison Operators
Suite* my_is_less_suite(void);
Suite* my_is_less_or_equal_suite(void);
Suite* my_is_greater_suite(void);
Suite* my_is_greater_or_equal_suite(void);
Suite* my_is_equal_suite(void);
Suite* my_is_not_equal_suite(void);

// Convertors and parsers
Suite* my_from_int_to_decimal_suite(void);
Suite* my_from_float_to_decimal_suite(void);
Suite* my_from_decimal_to_int_suite(void);
Suite* my_from_decimal_to_float_suite(void);

// Another functions
Suite* my_floor_suite(void);
Suite* my_round_suite(void);
Suite* my_truncate_suite(void);
Suite* my_negate_suite(void);

#endif
