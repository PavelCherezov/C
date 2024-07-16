#include "my_decimal.h"

// делимое меньше делителя
// делимое нужно нарастить за счёт экспоненты
void my_dividend_is_less(my_decimal *divident, my_decimal divider,
                          int *exponent) {
  my_decimal ten = {{10, 0, 0, 0}};
  while (my_is_less(*divident, divider)) {
    my_mul(*divident, ten, divident);
    (*exponent)++;
  }
}

void my_generate_exponent(my_decimal *sub_divident, my_decimal divider,
                           my_decimal *divident, int *exponent) {
  my_decimal ten = {{10, 0, 0, 0}};

  while (my_is_greater(divider, *sub_divident)) {
    (*exponent)++;
    my_mul(*sub_divident, ten, sub_divident);
  }
  *divident = *sub_divident;
}

// вычисляю первичный под_делитель
// изменяет по ссылке sub_divident - подделитель
// делитель и делимое не должны быть равны, нужно делать проверку до.
void my_get_sub_divident(int *cursor, my_decimal divident,
                          my_decimal *sub_divident, my_decimal divider) {
  bool shift_cursor = true;

  sub_divident->bits[0] = divident.bits[0];
  sub_divident->bits[1] = divident.bits[1];
  sub_divident->bits[2] = divident.bits[2];
  sub_divident->bits[3] = divident.bits[3];

  for (int i = *cursor; shift_cursor; i--) {
    *cursor = i;
    my_shift_bit(sub_divident, i, 1);
    if (my_is_greater(divider, *sub_divident)) {
      shift_cursor = true;

      sub_divident->bits[0] = divident.bits[0];
      sub_divident->bits[1] = divident.bits[1];
      sub_divident->bits[2] = divident.bits[2];
      sub_divident->bits[3] = divident.bits[3];

    } else {
      shift_cursor = false;
    }
  }
}

void my_array_add(my_decimal *array, int index, my_decimal num) {
  array[index] = num;
}

// Финальный ответ матиссы
void my_array_sum(my_decimal *answer, my_decimal *array, int exponent) {
  my_decimal sub_result = {{0, 0, 0, 0}};
  int index = exponent;
  for (int i = 0; i <= exponent; i++) {
    my_mul(array[i], my_degree_ten(index), &sub_result);
    my_add(*answer, sub_result, answer);
    index--;
  }
  answer->bits[3] = exponent << 16;
}

// возводит 10 в степень
my_decimal my_degree_ten(int degree) {
  my_decimal ten = {{10, 0, 0, 0}};
  my_decimal num = {{0, 0, 0, 0}};
  num = ten;

  if (degree == 0) {
    my_clear(&num);
    num.bits[0] = 1;
  } else if (degree > 1) {
    for (int i = 1; i < degree; i++) {
      my_mul(num, ten, &num);
    }
  }

  return num;
}

// Сдвигает decimal побитово.
// direction = 1 вправо, 0 влево.
// [95…64][63…32][31…0]
void my_shift_bit(my_decimal *num, int step, int direction) {
  if (direction) {
    for (; step > 0; step--) {
      unsigned int junior_bit_1 = my_get_bit_decimal(*num, JUNIOR_BIT_1);
      unsigned int junior_bit_2 = my_get_bit_decimal(*num, JUNIOR_BIT_2);

      num->bits[0] = num->bits[0] >> 1;
      num->bits[1] = num->bits[1] >> 1;
      num->bits[2] = num->bits[2] >> 1;

      my_set_bit_decimal(num, SENIOR_BIT_0, junior_bit_1);
      my_set_bit_decimal(num, SENIOR_BIT_1, junior_bit_2);
    }
  } else {
    for (; step > 0; step--) {
      unsigned int senior_bit_0 = my_get_bit_decimal(*num, SENIOR_BIT_0);
      unsigned int senior_bit_1 = my_get_bit_decimal(*num, SENIOR_BIT_1);

      num->bits[0] = num->bits[0] << 1;
      num->bits[1] = num->bits[1] << 1;
      num->bits[2] = num->bits[2] << 1;

      my_set_bit_decimal(num, JUNIOR_BIT_1, senior_bit_0);
      my_set_bit_decimal(num, JUNIOR_BIT_2, senior_bit_1);
    }
  }
}

// генерирует ответ деления (частное)
void my_generation_answer(my_decimal *sub_result, bool volume) {
  my_shift_bit(sub_result, 1, 0);
  my_set_bit_decimal(sub_result, 0, volume);
}

// перенос бита из делимого в под_делимое
void my_down_bit(my_decimal *sub_divident, my_decimal divident, int cursor) {
  my_shift_bit(sub_divident, 1, 0);
  bool bit = my_get_bit_decimal(divident, cursor);
  my_set_bit_decimal(sub_divident, 0, bit);
}

// генерирует масштаб для ответа
int my_generation_scale(int scale_divident, int scale_divider, int *exponent,
                         my_decimal *num) {
  int mult_result = 0;
  my_decimal ten = {{10, 0, 0, 0}};

  int tmp = (scale_divident - scale_divider) + (*exponent);

  if (tmp < 0) {
    tmp = tmp * -1;

    for (int i = tmp; i > 0; i--) {
      mult_result = my_mul(*num, ten, num);

      if (mult_result == 1) {
        i = 0;

      } else if (mult_result == 2) {
        i = 0;
      }
    }

    tmp = 0;
  }

  if (mult_result == 0) {
    *exponent = tmp;
    my_set_scale_decimal(num, *exponent);
  }
  return mult_result;
}

void my_generation_sign(my_decimal *num, bool sign_divident,
                         bool sign_divider) {
  if ((!sign_divident && sign_divider) || (sign_divident && !sign_divider)) {
    my_set_znak_decimal(num, 1);
  }
}
void my_bit_3_nool(my_decimal *divident, my_decimal *divider) {
  my_set_scale_decimal(divident, 0);
  my_set_scale_decimal(divider, 0);
  my_set_znak_decimal(divident, 0);
  my_set_znak_decimal(divider, 0);
}

void my_myn_culc(my_decimal divident, my_decimal divider,
                  my_decimal *all_sub_result, int *exponent,
                  bool div_remainder, int cursor) {
  while (div_remainder && *exponent <= 27) {
    my_decimal sub_result = {{0, 0, 0, 0}};
    my_decimal sub_divident = {{0, 0, 0, 0}};
    cursor = GLOBAL_SENIOR_BIT;
    my_get_sub_divident(&cursor, divident, &sub_divident, divider);
    my_generation_answer(&sub_result, true);
    my_sub(sub_divident, divider, &sub_divident);
    cursor--;
    while (cursor > 0 || cursor == 0) {
      my_down_bit(&sub_divident, divident, cursor);
      if (my_is_greater(divider, sub_divident)) {
        cursor--;
        my_generation_answer(&sub_result, false);
        continue;
      }
      my_generation_answer(&sub_result, true);
      my_sub(sub_divident, divider, &sub_divident);
      cursor--;
    }
    if (my_is_null(sub_divident)) {
      my_array_add(all_sub_result, *exponent, sub_result);
      div_remainder = false;
    } else {
      div_remainder = true;
      my_array_add(all_sub_result, *exponent, sub_result);
      my_generate_exponent(&sub_divident, divider, &divident, exponent);
    }
  }
}