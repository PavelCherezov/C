#include "my_decimal.h"

// функйия сложения
int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int exit = 0;
  int ost = 0;
  int s_ost = 0;
  my_clear(result);
  if (my_is_null(value_1) == 1 || my_is_null(value_2) == 1) {
    if (my_is_null(value_1) == 1 && my_is_null(value_2) == 1) {
      my_clear(result);
    } else if (my_is_null(value_1) == 1 && my_is_null(value_2) == 0) {
      *result = value_2;
    } else if (my_is_null(value_1) == 0 && my_is_null(value_2) == 1) {
      *result = value_1;
    }
  } else {
    if (my_get_znak_decimal(value_1) == 0 &&
        my_get_znak_decimal(value_2) == 1) {
      my_set_znak_decimal(&value_2, 0);
      exit = my_sub(value_1, value_2, result);
    } else if (my_get_znak_decimal(value_1) == 1 &&
               my_get_znak_decimal(value_2) == 0) {
      my_set_znak_decimal(&value_1, 0);
      exit = my_sub(value_2, value_1, result);
    } else if (my_get_znak_decimal(value_1) == my_get_znak_decimal(value_2)) {
      super_decimal num_1, num_2, itog;
      my_preparation(&num_1, &num_2, &itog, value_1, value_2);
      my_coice(&num_1, &num_2);
      for (int i = 0; i < 6; i++) {
        itog.bits[i] = num_1.bits[i] + num_2.bits[i];
      }
      my_set_scale(&itog, my_get_scale(num_2));
      my_set_znak(&itog, my_get_znak(num_2));
      while (my_get_overflow(&itog) && my_get_scale(itog)) {
        s_ost += ost;
        ost = my_scale_down(&itog);
      }
      my_bank(&itog, ost, s_ost);
      if (my_get_overflow(&itog) == 0) {
        my_conversion_decimal(itog, result);
      } else if (!my_get_znak(itog)) {
        exit = 1;
      } else if (my_get_znak(itog)) {
        exit = 2;
      }
    }
  }
  return exit;
}

// функция вычитания
int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int exit = 0, ost = 0, s_ost = 0;
  my_clear(result);
  if (my_is_null(value_1) == 1 || my_is_null(value_2) == 1)
    my_sub_nool(value_1, value_2, result);
  else {
    if (my_get_znak_decimal(value_1) == 0 &&
        my_get_znak_decimal(value_2) == 1) {
      my_set_znak_decimal(&value_2, 0);
      exit = my_add(value_1, value_2, result);
    } else if (my_get_znak_decimal(value_1) == 1 &&
               my_get_znak_decimal(value_2) == 0) {
      my_set_znak_decimal(&value_1, 0);
      exit = my_add(value_1, value_2, result) ? 2 : 0;
      my_set_znak_decimal(result, exit ? 0 : 1);
    } else if (my_get_znak_decimal(value_1) == my_get_znak_decimal(value_2)) {
      int znak = 0;
      if (my_is_less(value_1, value_2)) {
        znak = 1;
      }
      if ((my_get_znak_decimal(value_1) == 1 &&
           my_is_less(value_2, value_1)) ||
          (my_is_less(value_1, value_2) &&
           my_get_znak_decimal(value_1) == 0)) {
        my_decimal swap = value_1;
        value_1 = value_2;
        value_2 = swap;
      }
      super_decimal num_1, num_2, itog;
      my_preparation(&num_1, &num_2, &itog, value_1, value_2);
      my_coice(&num_1, &num_2);
      for (int i = 0; i < 6; i++) {
        if (num_1.bits[i] < num_2.bits[i]) {
          num_1.bits[i] |= (uint64_t)1 << 32;
          num_1.bits[i + 1] -= 1;
        }
        itog.bits[i] = num_1.bits[i] - num_2.bits[i];
      }
      my_set_scale(&itog, my_get_scale(num_2));
      while (my_get_overflow(&itog) && my_get_scale(itog)) {
        s_ost += ost;
        ost = my_scale_down(&itog);
      }
      my_bank(&itog, ost, s_ost);
      if (my_get_overflow(&itog) == 0) {
        my_conversion_decimal(itog, result);
        my_set_znak_decimal(result, znak);
      } else if (!my_get_znak(itog))
        exit = 1;
      else if (my_get_znak(itog))
        exit = 2;
    }
  }
  return exit;
}

// функция умножения
int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int exit = 0;
  int ost = 0;
  int s_ost = 0;
  int znak = 0;
  my_clear(result);
  if (my_is_null(value_1) == 1 || my_is_null(value_2) == 1) {
    my_clear(result);
  } else {
    if ((my_get_znak_decimal(value_1) || my_get_znak_decimal(value_2)) &&
        !((my_get_znak_decimal(value_1) && my_get_znak_decimal(value_2)))) {
      znak = 1;
    }
    int scale = my_get_scale_decimal(value_1) + my_get_scale_decimal(value_2);
    super_decimal buff, num_1, num_2, itog;
    my_preparation(&num_1, &num_2, &itog, value_1, value_2);
    for (int i = 0; i < 384; i++) {
      my_bleach(&buff);
      if (my_get_bit(num_2, i)) {
        my_left(num_1, &buff, i);
        my_summa(itog, buff, &itog);
        my_get_overflow(&itog);
      }
    }
    my_set_scale(&itog, scale);
    my_set_znak(&itog, znak);
    while ((my_get_overflow(&itog) && my_get_scale(itog)) ||
           my_get_scale(itog) > 28) {
      s_ost += ost;
      ost = my_scale_down(&itog);
    }
    my_bank(&itog, ost, s_ost);
    if (my_get_overflow(&itog) == 0) {
      my_conversion_decimal(itog, result);
    } else if (!my_get_znak(itog)) {
      exit = 1;
    } else if (my_get_znak(itog)) {
      exit = 2;
    }
  }
  return exit;
}

int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int exit = 0;
  bool continue_calc = true;
  my_decimal divident = value_1, divider = value_2;
  int cursor = 0, exponent = 0;
  bool div_remainder = true;
  my_decimal all_sub_result[50] = {{{0, 0, 0, 0}}}, zero = {0};
  my_clear(result);
  int scale_divident = my_get_scale_decimal(divident),
      scale_divider = my_get_scale_decimal(divider);
  bool sign_divident = my_get_znak_decimal(divident),
       sign_divider = my_get_znak_decimal(divider);
  my_bit_3_nool(&divident, &divider);
  if (my_is_equal(divider, zero)) {
    exit = 3;
    continue_calc = false;
  }
  if (my_is_equal(divident, zero) && continue_calc) {
    my_clear(result);
    continue_calc = false;
  }
  if (continue_calc) {
    if (my_is_less(divident, divider))
      my_dividend_is_less(&divident, divider, &exponent);
    my_myn_culc(divident, divider, all_sub_result, &exponent, div_remainder,
                 cursor);
    my_array_sum(result, all_sub_result, exponent);
    exit =
        my_generation_scale(scale_divident, scale_divider, &exponent, result);
    if (exit == 1) {
      if (sign_divider) {
        exit = 2;
        my_clear(result);
      }
    }
    if (exit == 0) my_generation_sign(result, sign_divident, sign_divider);
  }
  return exit;
}