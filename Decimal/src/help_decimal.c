#include "my_decimal.h"

// функция возвращает бит под индексом index из числа num
int my_get_bit_decimal(my_decimal num, int index) {
  int mask = 1 << index % 32;
  return num.bits[index / 32] & mask ? 1 : 0;
}

//функция возращает знак для децимал (0-плюс, 1-минус)
int my_get_znak_decimal(my_decimal num) {
  return my_get_bit_decimal(num, 127);
}

// функция возращает скейл заданного числа num
int my_get_scale_decimal(my_decimal num) {
  int scale = num.bits[3] >> 16 & 0xFF;
  return scale;
}

// функция вставки бита
void my_set_bit_decimal(my_decimal *num, int index, int znach) {
  int bytes = index / 32;
  int shift = index % 32;

  if (znach) {
    num->bits[bytes] |= 1 << shift;
  } else {
    num->bits[bytes] &= ~(1 << shift);
  }
}

//функция изменения знака для децимал
void my_set_znak_decimal(my_decimal *num, int znak) {
  my_set_bit_decimal(num, 127, znak);
}

// функция полной отчистки децимал
void my_clear(my_decimal *num) {
  for (int i = 0; i < 4; i++) {
    num->bits[i] = (num->bits[i] | ~num->bits[i]) + 1;
  }
}

//функция проверки является-ли мантиса 0 (если 0 вернет 1)
int my_is_null(my_decimal num) {
  int flag = 0;
  for (int i = 0; i < 3; i++) {
    if (num.bits[i] == 0) {
      flag += 1;
    }
  }
  return flag / 3;
}

//функция изменения скейла
void my_set_scale_decimal(my_decimal *num, int scale) {
  int znak = my_get_znak_decimal(*num);
  num->bits[3] = scale << 16;
  my_set_znak_decimal(num, znak);
}

void my_sub_nool(my_decimal value_1, my_decimal value_2,
                  my_decimal *result) {
  if (my_is_null(value_1) == 1 && my_is_null(value_2) == 1)
    my_clear(result);
  else if (my_is_null(value_1) == 1 && my_is_null(value_2) == 0) {
    *result = value_2;
    my_set_znak_decimal(result, my_get_znak_decimal(value_2) ? 0 : 1);
  } else if (my_is_null(value_1) == 0 && my_is_null(value_2) == 1)
    *result = value_1;
}