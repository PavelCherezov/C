#ifndef my_STRING_H
#define my_STRING_H
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define my_NULL ((void *)0)
#define MID 512
#define SMALL 256
#define MAX 1024

typedef unsigned long int my_size_t;

typedef struct Flags {
  int spec_c;
  int spec_d;
  int spec_f;
  int spec_s;
  int spec_u;
  int spec_o;
  int spec_x;
  int spec_X;
  int spec_percent;

  int fl_plus;
  int fl_minus;
  int fl_space;

  int desc_width;
  int desc_width_zero;  // заполняющий ноль %08.2f
  int desc_precision;
  int desc_precision_zero;  // нулевая точность, например %.0f

  int desc_h;
  int desc_l;

  int negative;  // число отрицательное

  // int fl_i;
  // int fl_e;
  // int fl_E;
  // int fl_g;
  // int fl_G;
  // int fl_o;
  // int fl_p;
  // int fl_n;
  // int fl_sharp;
  // int fl_zero;
  // int fl_len_L;
} flags_parse;

void *my_memchr(const void *str, int c, size_t n);             ///+++++
void *my_memcpy(void *dest, const void *src, size_t n);        ///++++
void *my_memset(void *ptr, int value, size_t num);             ///++++++
int my_memcmp(const void *str1, const void *str2, size_t n);   ///+++
char *my_strncat(char *dest, const char *source, size_t n);    ///+++
char *my_strchr(const char *str, int c);                       //+++++
int my_strncmp(const char *str1, const char *str2, size_t n);  //++++
char *my_strncpy(char *dest, const char *src, size_t n);       //++++
size_t my_strcspn(const char *str1, const char *str2);         ///++++
char *my_strerror(int errnum);                                 //++++
size_t my_strlen(const char *str);                             ////+++++
char *my_strpbrk(const char *str1, const char *str2);          /////++++
char *my_strrchr(const char *str, int c);                      ///////++++
char *my_strstr(const char *haystack, const char *needle);     ////++++
char *my_strtok(char *str, const char *delim);                 ////+++++
//функции шарп
void *my_to_upper(const char *str);                                     //+++++
void *my_to_lower(const char *str);                                     //+++++
void *my_insert(const char *src, const char *str, size_t start_index);  //++++
void *my_trim(const char *src, const char *trim_chars);                 //+++++
// sprintf

int my_sprintf(char *buff, char *format, ...);
void my_parser(char *buff, va_list factor, char **c_form, flags_parse *flags);
void my_parser_flags(char **c_form, flags_parse *flags);
void my_parser_spec(int *flag_start, char **c_form, flags_parse *flags);

void my_flag_reset(flags_parse *flags);
void my_LengthParser(char **c_form, flags_parse *flags);
void my_NumbersParser(char **c_form, flags_parse *flags, int flag_point);

void my_processing_all(va_list factor, flags_parse *flags, char *buff,
                        char **c_form);
void my_processing_char(char c, char *buff);
void my_processing_spec_d(va_list factor, char *buff, flags_parse *flags);
void my_processing_spec_f(double f, char *buff, flags_parse *flags);
void my_spec_f_width(char *aggregate_str, int *add_char, int *len_sub_buff,
                      char *sub_buff, flags_parse *flags);

void intToString(long long num, char *str);
void floatToString(double f, char *sub_buff, flags_parse *flags);
void my_floatToString_no_precision_zero(char *str_fractional, char *str_all,
                                         int *zero_point, flags_parse *flags);

void add_minus(char *sub_buff);
void add_plus(char *sub_buff);
void add_space(char *sub_buff);

void my_processing_spec_c(va_list factor, flags_parse *flags, char *buff);
void my_processing_spec_s(va_list factor, flags_parse *flags, char *buff);
void my_processing_spec_percent(flags_parse *flags, char *buff);
void my_print_str(flags_parse *flags, char *str, char *buff);
void my_format_output(char *str, char *buff, flags_parse *flags);
void my_processing_spec_x(long long int x, char *buff, char **c_form,
                           flags_parse *flags);
void my_processing_spec_o(long long int o, char *buff, flags_parse *flags);

char *my_strcat(char *dest, const char *src);
char *my_strcpy(char *dest, const char *src);
char *my_strdup(const char *s);

#endif