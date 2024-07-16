#ifndef my_DECIMAL_H
#define my_DECIMAL_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 0xFFFFFFFF
#define S_MAX 0xFFFFFFFFFFFFFFFF

#define BUF 64
#define my_MAX_FLOAT 79228162514264337593543950335.0F
#define my_MIN_FLOAT 1E-28
#define my_MAX_INT 2147483647

#define SENIOR_BIT_0 31
#define SENIOR_BIT_1 63
#define JUNIOR_BIT_1 32
#define JUNIOR_BIT_2 64
#define GLOBAL_SENIOR_BIT 95

typedef struct {
  unsigned int bits[4];
} my_decimal;

typedef struct {
  uint64_t bits[6];
  uint32_t scale;
} super_decimal;

void my_bit_print_decimal(my_decimal num);
void my_bit_print(super_decimal num);
uint64_t my_get_bit(super_decimal sis, int index);
int my_get_bit_decimal(my_decimal num, int index);
int my_get_znak(super_decimal num);
int my_get_znak_decimal(my_decimal num);
int my_get_scale(super_decimal num);
int my_get_scale_decimal(my_decimal num);
void my_addition(super_decimal *num, int index, int znach);
void my_set_bit(super_decimal *num, int index, int znach);
void my_set_bit_decimal(my_decimal *num, int index, int znach);
void my_set_scale(super_decimal *num, int scale);
void my_set_znak(super_decimal *num, int znak);
void my_set_znak_decimal(my_decimal *num, int znak);
void my_bleach(super_decimal *num);
void my_clear(my_decimal *num);
void my_coice(super_decimal *num_1, super_decimal *num_2);
void my_normalization(super_decimal *result, int scale);
int my_is_null(my_decimal num);
void my_conversion(my_decimal num, super_decimal *result);
int my_get_overflow(super_decimal *num);
void my_summa(super_decimal num_1, super_decimal num_2, super_decimal *summ);
int my_comparison(my_decimal value_1, my_decimal value_2);
my_decimal my_step(my_decimal num_1, int move);
void my_scale_up(super_decimal *num);
uint64_t my_scale_down(super_decimal *num);
void my_mult_bu_10(my_decimal *num);
void my_bank(super_decimal *num, int ost, int s_ost);
void my_preparation(super_decimal *num_1, super_decimal *num_2,
                     super_decimal *itog, my_decimal value_1,
                     my_decimal value_2);
void my_set_scale_decimal(my_decimal *num, int scale);
void my_left(super_decimal num, super_decimal *result, int i);
int my_nan(my_decimal value);
int my_infinity(my_decimal value);
int my_last_bit(my_decimal value);
int my_degree_range(my_decimal value);
int my_checking(my_decimal value);
void my_conversion_decimal(super_decimal num, my_decimal *result);
int my_checking_float(float value);
void my_conversion_float(float src, unsigned int *mantissa, int *scale);
int my_scale_checking(my_decimal *dst, int scale);
void my_dividend_is_less(my_decimal *divident, my_decimal divider,
                          int *exponent);
void my_generate_exponent(my_decimal *sub_divident, my_decimal divider,
                           my_decimal *divident, int *exponent);
int my_is_full_matisse(my_decimal num_1);
void my_get_sub_divident(int *cursor, my_decimal divident,
                          my_decimal *sub_divident, my_decimal divider);
void my_array_add(my_decimal *array, int index, my_decimal num);
void my_array_sum(my_decimal *answer, my_decimal *array, int exponent);
my_decimal my_degree_ten(int degree);
void my_shift_bit(my_decimal *num, int step, int direction);
void my_generation_answer(my_decimal *sub_result, bool volume);
void my_down_bit(my_decimal *sub_divident, my_decimal divident, int cursor);
void my_down_zero_bit(my_decimal *sub_divident);
int my_generation_scale(int scale_divident, int scale_divider, int *exponent,
                         my_decimal *num);
void my_generation_sign(my_decimal *num, bool sign_divident,
                         bool sign_divider);
void my_bit_3_nool(my_decimal *divident, my_decimal *divider);
void my_sub_nool(my_decimal value_1, my_decimal value_2,
                  my_decimal *result);
void my_myn_culc(my_decimal divident, my_decimal divider,
                  my_decimal *all_sub_result, int *exponent,
                  bool div_remainder, int cursor);

int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result);

int my_floor(my_decimal value, my_decimal *result);
int my_round(my_decimal value, my_decimal *result);
int my_truncate(my_decimal value, my_decimal *result);
int my_negate(my_decimal value, my_decimal *result);

int my_is_equal(my_decimal num_1, my_decimal num_2);
int my_is_not_equal(my_decimal num_1, my_decimal num_2);
int my_is_less(my_decimal num_1, my_decimal num_2);
int my_is_greater(my_decimal num_1, my_decimal num_2);
int my_is_greater_or_equal(my_decimal num_1, my_decimal num_2);
int my_is_less_or_equal(my_decimal num_1, my_decimal num_2);

int my_from_decimal_to_float(my_decimal src, float *dst);
int my_from_float_to_decimal(float src, my_decimal *dst);
int my_from_decimal_to_int(my_decimal src, int *dst);
int my_from_int_to_decimal(int src, my_decimal *dst);

#endif