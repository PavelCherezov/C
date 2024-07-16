#ifndef MY_MATH_H
#define MY_MATH_H
#include <float.h>
#include <stdio.h>

#define MY_PI 3.141592653589793238462643383L
#define MY_EXP 2.7182818284590452353602874713527L
#define MY_EPS 0.00000000000001L
#define MY_MAX 999999999999999999999999999999999.9L
#define MY_INF_P (1.0) / (+0.0)
#define MY_INF_N (1.0) / (-0.0)
#define MY_NaN (0.0) / (0.0)

#define MY_IS_NAN(x) (x != x)
#define MY_IS_INF(x) (x == MY_INF_N || x == MY_INF_P)

int my_abs(int x);
long double my_acos(double x);
long double my_asin(double x);
long double my_atan(double x);
long double my_ceil(double x);
long double my_cos(double x);
long double my_exp(double x);
long double my_fabs(double x);
long double my_floor(double x);
long double my_fmod(double x, double y);
long double my_log(double x);
long double my_pow(double base, double exp);
long double my_sin(double x);
long double my_sqrt(double x);
long double my_tan(double x);

long double my_number(double x);
long double my_factorial(int x);
long double my_pow_int(double base, int exp);

#endif