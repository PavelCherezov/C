#include "my_decimal.h"

int my_from_decimal_to_float(my_decimal src, float *dst) {
  if (my_checking(src) != 0 || !dst) {
    return 1;
  } else {
    int value = 0;
    double temp = 0.0;
    for (int i = 0; i <= 95; i++) {
      if (my_get_bit_decimal(src, i)) {
        temp += pow(2.0, i);
      }
    }
    double power = pow(10.0, my_get_scale_decimal(src));
    temp /= power;
    if (my_get_znak_decimal(src)) {
      temp = -temp;
    }
    *dst = temp;
    return value;
  }
}

int my_checking_float(float value) {
  int result = 0;
  if (isinf(value) || isnan(value)) {
    result = 1;
  }
  if (fabs(value) > my_MAX_FLOAT) {
    result = 1;
  }
  if (fabs(value) < my_MIN_FLOAT && value != 0) {
    result = 1;
  }
  return result;
}

void my_conversion_float(float src, unsigned int *mantissa, int *scale) {
  char array[BUF] = {0}, temp[BUF] = {0};
  sprintf(array, "%.6E", src);
  temp[0] = array[0];
  for (int i = 2; i <= 7; i++) {
    temp[i - 1] = array[i];
  }
  *mantissa = atoi(temp);
  memset(temp, 0, BUF);
  for (int i = 9; i <= 11; i++) {
    temp[i - 9] = array[i];
  }
  temp[3] = '\0';
  *scale = atoi(temp) - 6;
}

int my_scale_checking(my_decimal *dst, int scale) {
  int value = 0;
  if (scale < 0) {
    int ost = 0;
    scale *= -1;
    while ((dst->bits[0] % 10 == 0 && scale) || scale > 28) {
      ost = dst->bits[0] % 10;
      dst->bits[0] /= 10;
      scale--;
    }
    if (ost >= 5) {
      dst->bits[0] += 1;
    }
    my_set_scale_decimal(dst, scale);
  } else {
    while (scale > 0) {
      my_decimal temp = {{0, 0, 0, 0}};
      value = my_mul(*dst, (my_decimal){{10, 0, 0, 0}}, &temp);
      *dst = temp;
      scale--;
    }
  }
  return value;
}

int my_from_float_to_decimal(float src, my_decimal *dst) {
  if (!dst) {
    return 1;
  }
  int value = my_checking_float(src);
  my_clear(dst);

  if (value == 0) {
    if (src < 0.0f) {
      my_set_bit_decimal(dst, 127, 1);
      src = -src;
    }
    unsigned int mantissa = 0;
    int scale = 0;
    my_conversion_float(src, &mantissa, &scale);
    dst->bits[0] = mantissa;
    my_scale_checking(dst, scale);
  }

  return value == 0 ? 0 : 1;
}

int my_from_decimal_to_int(my_decimal src, int *dst) {
  if (my_checking(src) != 0) {
    return 1;
  } else {
    int value = 0;
    my_decimal result = {{0, 0, 0, 0}};
    my_truncate(src, &result);
    if ((result.bits[0] <= my_MAX_INT || result.bits[0] == 0x80000000) &&
        result.bits[1] == 0 && result.bits[2] == 0) {
      *dst = result.bits[0];
      if (my_get_znak_decimal(src)) *dst *= -1;
    } else {
      value = 1;
    }
    return value;
  }
}

int my_from_int_to_decimal(int src, my_decimal *dst) {
  if (!dst) {
    return 1;
  }
  my_clear(dst);
  int value = 0;
  int sign = 0;
  if (src < 0) {
    sign = 1;
    src *= -1;
  }
  dst->bits[0] = src;
  my_set_bit_decimal(dst, 127, sign);
  return value;
}
