#include "my_decimal.h"

// проверка nan
int my_nan(my_decimal value) {
  int flag = 1;
  for (int i = 111; i <= 118; i++) {
    if (my_get_bit_decimal(value, i) == 0) flag = 0;
  }
  return flag;
}

// бесконечность (infinity)
int my_infinity(my_decimal value) {
  int flag = 1;
  for (int i = 111; i <= 118; i++) {
    if (my_get_bit_decimal(value, i) == 0) flag = 0;
  }
  for (int i = 95; i >= 0; i--) {
    if (my_get_bit_decimal(value, i) == 1) flag = 0;
  }
  return flag;
}

// проверка последнего бита
int my_last_bit(my_decimal value) {
  int flag = 0;
  for (int i = 127; i >= 96; i--) {
    if (my_get_bit_decimal(value, i)) {
      if (i != 127 && (i < 112 || i > 119)) {
        flag = 1;
      }
    }
  }
  return flag;
}

// диапазон  степени
int my_degree_range(my_decimal value) {
  return my_get_scale_decimal(value) < 0 || my_get_scale_decimal(value) > 28;
}

// проверка краевых, для округления
int my_checking(my_decimal value) {
  return my_nan(value) || my_degree_range(value) || my_infinity(value) ||
         my_last_bit(value);
}
