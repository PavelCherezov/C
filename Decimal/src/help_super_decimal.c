#include "my_decimal.h"

// функция взятия отдельного бита
uint64_t my_get_bit(super_decimal num, int index) {
  uint64_t mask = (uint64_t)1 << index % 64;
  return num.bits[index / 64] & mask ? 1 : 0;
}

// функция возращает знак 0-плюс, 1-минус
int my_get_znak(super_decimal num) { return num.scale & 1 << 31; }

// функция возращает скейл
int my_get_scale(super_decimal num) {
  int scale = num.scale >> 16 & 0xFF;
  return scale;
}

// функция вставки бита
void my_set_bit(super_decimal *num, int index, int znach) {
  int bytes = index / 64;
  int shift = index % 64;

  if (znach) {
    num->bits[bytes] |= (uint64_t)1 << shift;
  } else {
    num->bits[bytes] &= ~((uint64_t)1 << shift);
  }
}

//функция изменения скейла
void my_set_scale(super_decimal *num, int scale) {
  int znak = my_get_znak(*num);
  num->scale = scale << 16;
  my_set_znak(num, znak);
}

//функция изменения знака
void my_set_znak(super_decimal *num, int znak) { my_set_bit(num, 415, znak); }

// функция полной очистки биг децимал
void my_bleach(super_decimal *num) {
  for (int i = 0; i < 6; i++) {
    num->bits[i] = 0;
  }
  num->scale = 0;
}

//функция выбора  какое число нормализовать
void my_coice(super_decimal *num_1, super_decimal *num_2) {
  if (my_get_scale(*num_1) > my_get_scale(*num_2)) {
    my_normalization(num_2, my_get_scale(*num_1) - my_get_scale(*num_2));
  } else if (my_get_scale(*num_1) < my_get_scale(*num_2)) {
    my_normalization(num_1, my_get_scale(*num_2) - my_get_scale(*num_1));
  }
}

//функция нормализации
void my_normalization(super_decimal *result, int scale) {
  super_decimal num_1 = *result;
  super_decimal num_2 = *result;
  for (int j = scale; j > 0; j--) {
    for (int i = 0; i < 6; i++) {
      num_1.bits[i] = result->bits[i] << 1;
      num_2.bits[i] = result->bits[i] << 3;
      if (i > 0) {
        num_1.bits[i] = (result->bits[i - 1] >> 63) | num_1.bits[i];
        num_2.bits[i] = (result->bits[i - 1] >> 61) | num_2.bits[i];
      }
    }
    my_summa(num_1, num_2, result);
    my_get_overflow(result);
  }
  my_set_scale(result, scale + my_get_scale(*result));
}

//функция конвертации децимал в супер децимал
void my_conversion(my_decimal num, super_decimal *result) {
  for (int i = 0; i < 3; i++) {
    result->bits[i] = num.bits[i] & MAX;
  }
  my_set_scale(result, my_get_scale_decimal(num));
  my_set_znak(result, my_get_znak_decimal(num));
}

//функция проверяющая на переполнение (0 - нет переполнения, 1 - есть
//переполнение)
int my_get_overflow(super_decimal *num) {
  uint64_t overflow = 0;
  int result = 0;
  for (int i = 0; i < 6; i++) {
    num->bits[i] += overflow;
    overflow = num->bits[i] >> 32;
    num->bits[i] &= MAX;
  }
  if (overflow != 0 || num->bits[3] != 0 || num->bits[4] != 0 ||
      num->bits[5] != 0) {
    result = 1;
  }
  return result;
}

void my_summa(super_decimal num_1, super_decimal num_2, super_decimal *summ) {
  for (int i = 0; i < 6; i++) {
    summ->bits[i] = num_1.bits[i] + num_2.bits[i];
  }
}

//деление на 10
uint64_t my_scale_down(super_decimal *num) {
  uint64_t buff = 0;
  for (int i = 5; i >= 0; i--) {
    num->bits[i] += buff << 32;
    buff = num->bits[i] % 10;
    num->bits[i] /= 10;
  }
  my_set_scale(num, my_get_scale(*num) - 1);
  return buff;
}

//банковское округление
void my_bank(super_decimal *num, int ost, int s_ost) {
  if (ost > 5 || ((num->bits[0] % 10) % 2 == 1 && ost == 5) ||
      (ost == 5 && s_ost)) {
    num->bits[0] += 1;
  }
}

void my_preparation(super_decimal *num_1, super_decimal *num_2,
                     super_decimal *itog, my_decimal value_1,
                     my_decimal value_2) {
  my_bleach(num_1);
  my_bleach(num_2);
  my_bleach(itog);
  my_conversion(value_1, num_1);
  my_conversion(value_2, num_2);
}

//Сдвиг мантисы на i бит
void my_left(super_decimal num, super_decimal *result, int i) {
  int j = 0;
  for (; i < 384; i++) {
    my_set_bit(result, i, my_get_bit(num, j));
    j++;
  }
  my_get_overflow(result);
}

void my_conversion_decimal(super_decimal num, my_decimal *result) {
  for (int i = 0; i < 3; i++) {
    result->bits[i] = num.bits[i] & MAX;
  }
  result->bits[3] = my_is_null(*result) ? 0 : num.scale;
}