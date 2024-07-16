#include "my_decimal.h"

int my_comparison(my_decimal value_1, my_decimal value_2) {
  int flag = 0;
  super_decimal num_1, num_2, summ;
  my_bleach(&num_2);
  my_bleach(&num_1);
  my_bleach(&summ);
  my_conversion(value_1, &num_1);
  my_conversion(value_2, &num_2);
  my_coice(&num_1, &num_2);
  my_coice(&num_1, &num_2);
  if (my_is_null(value_1) && my_is_null(value_2)) {
    flag = 0;
  } else if (my_get_znak(num_1) && !my_get_znak(num_2)) {
    flag = 2;
  } else if (!my_get_znak(num_1) && my_get_znak(num_2)) {
    flag = 1;
  } else {
    for (int i = 2; i >= 0; i--) {
      if (num_1.bits[i] < num_2.bits[i]) {
        flag = 2;
        break;
      } else if (num_1.bits[i] > num_2.bits[i]) {
        flag = 1;
        break;
      }
    }
  }
  if (my_get_znak(num_1) && my_get_znak(num_2) && flag) {
    if (flag == 1) {
      flag = 2;
    } else {
      flag = 1;
    }
  }
  return flag;
}

// ==
int my_is_equal(my_decimal num_1, my_decimal num_2) {
  int res = my_comparison(num_1, num_2);
  if (res > 0) {
    res = 0;
  } else {
    res = 1;
  }
  return res;
}

// !=
int my_is_not_equal(my_decimal num_1, my_decimal num_2) {
  return my_is_equal(num_1, num_2) ? 0 : 1;
}

//<
int my_is_less(my_decimal num_1, my_decimal num_2) {
  return my_is_greater(num_2, num_1);
}

//>
int my_is_greater(my_decimal num_1, my_decimal num_2) {
  int res = my_comparison(num_1, num_2);
  if (res == 2) {
    res = 0;
  }
  return res;
}

// >=
int my_is_greater_or_equal(my_decimal num_1, my_decimal num_2) {
  int res = my_comparison(num_1, num_2);
  if (res == 0 || res == 1) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}

// <=
int my_is_less_or_equal(my_decimal num_1, my_decimal num_2) {
  int res = my_comparison(num_1, num_2);
  if (res == 0 || res == 2) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}