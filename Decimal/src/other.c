#include "my_decimal.h"

int my_floor(my_decimal value, my_decimal *result) {
  if (my_checking(value) || !result) {
    return 1;
  }
  int s_ost = 0;
  super_decimal itog;
  my_bleach(&itog);
  my_conversion(value, &itog);
  while (my_get_scale(itog)) {
    s_ost += my_scale_down(&itog);
  }
  if (my_get_znak(itog) && s_ost) {
    itog.bits[0] += 1;
  }
  my_conversion_decimal(itog, result);
  return 0;
}

int my_round(my_decimal value, my_decimal *result) {
  if (my_checking(value) || !result) {
    return 1;
  }
  int ost = 0;
  super_decimal itog;
  my_bleach(&itog);
  my_conversion(value, &itog);
  while (my_get_scale(itog)) {
    ost = my_scale_down(&itog);
  }
  if (ost >= 5) {
    itog.bits[0] += 1;
  }
  my_conversion_decimal(itog, result);
  return 0;
}

int my_truncate(my_decimal value, my_decimal *result) {
  if (my_checking(value) || !result) {
    return 1;
  }
  my_clear(result);
  *result = value;
  super_decimal itog;
  my_bleach(&itog);
  my_conversion(value, &itog);
  for (; my_get_scale(itog) > 0;) {
    my_scale_down(&itog);
  }
  my_conversion_decimal(itog, result);
  return 0;
}

//умножение на -1
int my_negate(my_decimal value, my_decimal *result) {
  int exit = 0;
  if (my_checking(value)) {
    exit = 1;
  } else {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }
    result->bits[3] += 1 << 31;
  }
  return exit;
}