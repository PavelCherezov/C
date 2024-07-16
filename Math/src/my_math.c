#include "my_math.h"

long double my_ceil(double x) {
  if (MY_IS_NAN(x) || MY_IS_INF(x)) return x;
  long long int intpart;
  intpart = (long long int)x;
  intpart += (x > 0 && (x - intpart));
  return (long double)intpart;
}

long double my_fabs(double x) {
  long double fabs_x = x;
  if (fabs_x < 0) {
    fabs_x = -fabs_x;
  }
  return fabs_x;
}

long double my_floor(double x) {
  long double floor_x = (long long int)x;
  if (x < 0 && x - floor_x != 0) {
    floor_x--;
  }
  return floor_x;
}

int my_abs(int x) {
  if (x < 0) {
    x = -x;
  }
  return x;
}

long double my_sqrt(double x) {
  long double sqrt_x = x;
  long double left = 0;
  long double right = my_number(x);
  long double squeeze = 0;
  if (sqrt_x < 0.) {
    squeeze = MY_NaN;
  } else if (sqrt_x == 0) {
    squeeze = 0;
  } else {
    squeeze = (left + right) / 2;
    while (squeeze - left > MY_EPS) {
      if (squeeze * squeeze > sqrt_x)
        right = squeeze;
      else
        left = squeeze;
      squeeze = (left + right) / 2;
    }
  }
  return squeeze;
}

long double my_number(double x) {
  long double num_x = x;
  long double num_ret = 0;
  if (num_x < 1.0) {
    num_ret = 1;
  } else {
    num_ret = num_x;
  }
  return num_ret;
}

long double my_fmod(double x, double y) {
  long double fmod_x = x;
  long double fmod_y = y;
  long double result = 0;
  long long int div = 0;
  if (fmod_x != MY_INF_P && fmod_x != MY_INF_N && fmod_x == fmod_x &&
      fmod_y == fmod_y && fmod_y != 0.0) {
    div = fmod_x / fmod_y;
    if (my_fabs(div) < MY_EPS) {
      result = fmod_x;
    } else {
      result = fmod_x - div * fmod_y;
    }
  } else {
    result = MY_NaN;
  }
  return result;
}

long double my_exp(double x) {
  long double exp_x = x;
  long double add_value = 1;
  long double result = 1;
  long double i = 1;
  int out = 0;
  if (exp_x != MY_INF_N && exp_x != MY_NaN) {
    while (my_fabs(add_value) > MY_EPS && !out) {
      add_value *= exp_x / i;
      i++;
      result += add_value;
      if (result > MY_MAX && exp_x > 0) {
        out = 1;
      } else if (result > MY_MAX && exp_x < 0) {
        result = 0.0;
        out = 1;
      }
    }
  } else {
    if (exp_x == MY_INF_N) result = 0;
    if (exp_x == MY_INF_P) result = MY_INF_P;
  }
  if (result < 0) result = 0.0;
  return result;
}

long double my_log(double x) {
  long double log_x = x;
  int ex_pow = 0;
  long double resul = 0;
  long double last_result = 0;
  if (log_x == log_x && log_x != MY_INF_P && log_x > 0) {
    while (log_x >= MY_EXP) {
      log_x /= MY_EXP;
      ex_pow++;
    }
    for (int i = 0; i < 1000; i++) {
      last_result = resul;
      resul = last_result + 2 * (log_x - my_exp(last_result)) /
                                (log_x + my_exp(last_result));
    }
  } else {
    if (log_x != log_x) {
      resul = MY_NaN;
    } else if (log_x == MY_INF_P) {
      resul = MY_INF_P;
    } else if (log_x < 0) {
      resul = MY_NaN;
    } else if (log_x == 0) {
      resul = MY_INF_N;
    }
  }
  return resul + ex_pow;
}

long double my_pow(double base, double exp) {
  long double result = 0;
  long double pow_base = base;
  if ((exp > MY_MAX && pow_base >= 1) || (pow_base == 0 && exp < 0)) {
    result = MY_INF_P;
  } else if (exp == 0) {
    result = 1;
  } else if ((exp != exp || pow_base != pow_base) ||
             (exp < MY_MAX && exp > 0 && pow_base > -1 && pow_base < 0 &&
              pow_base != MY_INF_N)) {
    result = MY_NaN;
  } else if ((pow_base < -1 && exp < -1) ||
             (pow_base == MY_INF_N && exp < 0 && exp > -1)) {
    result = 0.0;
  } else if (((pow_base < 0 && exp > -1 && exp < 1) && pow_base != MY_INF_N) ||
             pow_base != pow_base) {
    result = MY_NaN;
  } else if (exp > MY_MAX && ((pow_base < 1 && pow_base >= 0) ||
                               (pow_base > -1 && pow_base <= 0))) {
    result = 0.0;
  } else if ((pow_base == MY_INF_N && exp < 1 && exp > 0) ||
             (exp == MY_INF_N && pow_base < 1 && pow_base >= 0)) {
    result = MY_INF_P;
  } else if ((pow_base == MY_INF_N && exp == MY_INF_P) ||
             (pow_base == MY_INF_N && exp != 0)) {
    result = MY_INF_P;
  } else if ((exp == MY_INF_N && pow_base < 0 && pow_base >= -1) ||
             (exp > MY_MAX && pow_base < 0)) {
    result = MY_INF_P;
  } else if ((exp == MY_INF_N && pow_base > 1) ||
             (exp == MY_INF_N && pow_base < -1)) {
    result = 0.0;
  } else if (pow_base < 0) {
    pow_base = my_fabs(pow_base);
    result = my_exp(exp * my_log(pow_base));
    if (my_fmod(exp, 2) != 0) {
      result = -result;
    }
  } else {
    result = my_exp(exp * my_log(pow_base));
  }
  if (result != result && (pow_base < -1 && exp > 1)) {
    result = MY_INF_P;
  }
  return result;
}

long double my_atan(double x) {
  long double atan_x = x;
  long double result = 0;
  if (atan_x == 1 || atan_x == -1) {
    result = (MY_PI / 4) * atan_x;
  } else if (atan_x > -1 && atan_x < 1) {
    for (int i = 0; i < 1000; i++) {
      result += (my_pow(-1, i) * my_pow_int(atan_x, 1 + 2 * i)) / (1 + 2 * i);
    }
  } else {
    for (int i = 0; i < 1000; i++) {
      result += (my_pow_int(-1, i) * my_pow_int(atan_x, -(1 + 2 * i))) /
                (1 + 2 * i);
    }
    result =
        ((MY_PI * my_sqrt(my_pow_int(atan_x, 2))) / (2 * atan_x)) - result;
  }
  return result;
}

long double my_pow_int(double base, int exp) {
  long double result = 1;
  int exp_f = my_fabs(exp);
  for (int j = 0; j < exp_f; j++) {
    result *= base;
  }
  if (my_fmod(exp, 2) != 0 && exp < 0) {
    result = 1 / result;
  }
  return result;
}

long double my_asin(double x) {
  long double asin_x = x;
  long double result = 0;
  if (asin_x > -1 && asin_x < 1) {
    result = my_atan(asin_x / (my_sqrt(1 - my_pow_int(asin_x, 2))));
  } else if (asin_x == -1 || asin_x == 1 || asin_x == 0) {
    result = MY_PI / 2 * asin_x;
  } else {
    result = MY_NaN;
  }
  return result;
}

long double my_acos(double x) {
  long double acos_x = x;
  long double result = 0;
  if (acos_x > 0 && acos_x < 1) {
    result = my_atan((my_sqrt(1 - my_pow_int(acos_x, 2))) / acos_x);
  } else if (acos_x > -1 && acos_x < 0) {
    result = MY_PI + my_atan((my_sqrt(1 - my_pow_int(acos_x, 2))) / acos_x);
  } else if (acos_x == -1 || acos_x == 1 || acos_x == 0) {
    result = MY_PI / 2 - (MY_PI / 2 * acos_x);
  } else {
    result = MY_NaN;
  }
  return result;
}

long double my_sin(double x) {
  long double result = 0;
  if ((x != x) || my_fabs(x) == MY_INF_P || my_fabs(x) == MY_INF_N) {
    result = MY_NaN;
  }
  x = my_fmod(x, 2 * MY_PI);
  if (x < 0) x += MY_PI * 2;
  long double taylor_row = x;
  long double i = 1;
  while (my_fabs(taylor_row) > MY_EPS) {
    result = result + taylor_row;
    taylor_row = taylor_row * (-1) * (x * x) / ((2 * i + 1) * (2 * i));
    i++;
  }
  return result;
}

long double my_cos(double x) {
  long double result = 0;
  if ((x != x) || my_fabs(x) == MY_INF_P || my_fabs(x) == MY_INF_N) {
    result = MY_NaN;
  } else {
    result = my_sin(MY_PI / 2 - x);
  }
  return result;
}

long double my_tan(double x) { return (my_sin(x) / my_cos(x)); }