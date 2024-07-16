#include "string.h"

int my_sprintf(char *buff, char *format, ...) {
  *buff = 0;
  int sum = 0;
  va_list factor;
  va_start(factor, format);
  flags_parse flags = {0};
  for (; *format; format++) {
    my_parser(buff, factor, &format, &flags);
  }
  va_end(factor);
  sum = my_strlen(buff);
  return sum;
}

void my_parser(char *buff, va_list factor, char **c_form, flags_parse *flags) {
  int flag_start = 0;
  int flag_point = 0;
  if (**c_form != '%') {
    my_processing_char(**c_form, buff);
  } else {
    flag_start = 1;
    my_flag_reset(flags);
    (*c_form)++;
  }
  while (flag_start) {
    my_parser_flags(c_form, flags);
    my_NumbersParser(c_form, flags, flag_point);
    if (**c_form == '.') {
      flag_point = 1;
      (*c_form)++;
      my_NumbersParser(c_form, flags, flag_point);
    }
    my_LengthParser(c_form, flags);
    my_parser_spec(&flag_start, c_form, flags);
    if (flag_start) {
      (*c_form)++;
    } else {
      my_processing_all(factor, flags, buff, c_form);
    }
  }
}

void my_parser_spec(int *flag_start, char **c_form, flags_parse *flags) {
  if (**c_form == '%') {
    flags->spec_percent = 1;
    *flag_start = 0;
  }
  if (**c_form == 'd') {
    flags->spec_d = 1;
    *flag_start = 0;
  } else if (**c_form == 'f') {
    flags->spec_f = 1;
    *flag_start = 0;
  } else if (**c_form == 'c') {
    flags->spec_c = 1;
    *flag_start = 0;
  } else if (**c_form == 's') {
    flags->spec_s = 1;
    *flag_start = 0;
  } else if (**c_form == 'u') {
    flags->spec_u = 1;
    *flag_start = 0;
  } else if (**c_form == 'o') {
    flags->spec_o = 1;
    *flag_start = 0;
  } else if (**c_form == 'x') {
    flags->spec_x = 1;
    *flag_start = 0;
  } else if (**c_form == 'X') {
    flags->spec_X = 1;
    *flag_start = 0;
  }
}

void my_parser_flags(char **c_form, flags_parse *flags) {
  if (**c_form == '+') {
    flags->fl_plus = 1;
  }
  if (**c_form == '-') {
    flags->fl_minus = 1;
  }
  if (**c_form == ' ') {
    flags->fl_space = 1;
  }
}

void my_LengthParser(char **c_form, flags_parse *flags) {
  char c = **c_form;
  if (c == 'h') {
    flags->desc_h = 1;
  }
  if (c == 'l') {
    flags->desc_l = 1;
  }
}

void my_NumbersParser(char **c_form, flags_parse *flags, int flag_point) {
  int flag = 1;
  int flag_find_zero = 0;
  int iter = 0;
  while (flag) {
    iter++;
    char c = **c_form;
    int tmp = 0;
    int tmp_sum = 0;
    if (flag_point) {
      tmp_sum = flags->desc_precision;
    } else {
      tmp_sum = flags->desc_width;
    }
    if (c == '0' && iter == 1) {
      flag_find_zero = 1;
    }
    if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' ||
        c == '6' || c == '7' || c == '8' || c == '9') {
      tmp = c - '0';
      tmp_sum = (tmp_sum * 10) + tmp;
      if (flag_point) {
        flags->desc_precision = tmp_sum;
      } else {
        flags->desc_width = tmp_sum;
      }
      flag = 1;
      (*c_form)++;
    } else {
      flag = 0;
      if (flag_point && (tmp_sum == 0)) {
        flags->desc_precision_zero = 1;
      }
      if (!flag_point && flag_find_zero && tmp_sum) {
        flags->desc_width_zero = 1;
      }
    }
  }
}

void my_flag_reset(flags_parse *flags) {
  flags->spec_c = 0;
  flags->spec_d = 0;
  flags->spec_f = 0;
  flags->spec_s = 0;
  flags->spec_o = 0;
  flags->spec_u = 0;
  flags->spec_percent = 0;
  flags->fl_minus = 0;
  flags->fl_plus = 0;
  flags->fl_space = 0;
  flags->desc_width = 0;
  flags->desc_width_zero = 0;
  flags->desc_precision = 0;
  flags->desc_precision_zero = 0;
  flags->desc_h = 0;
  flags->desc_l = 0;
  flags->negative = 0;
}

void my_processing_all(va_list factor, flags_parse *flags, char *buff,
                        char **c_form) {
  if (flags->spec_percent) {
    my_processing_spec_percent(flags, buff);
  }
  if (flags->spec_c) {
    my_processing_spec_c(factor, flags, buff);
  }
  if (flags->spec_s) {
    my_processing_spec_s(factor, flags, buff);
  }
  if (flags->spec_d == 1) {
    my_processing_spec_d(factor, buff, flags);
  }
  if (flags->spec_u) {
    my_processing_spec_d(factor, buff, flags);
  }
  if (flags->spec_f == 1) {
    double f;
    f = va_arg(factor, double);
    my_processing_spec_f(f, buff, flags);
  }
  if (flags->spec_o == 1) {
    long long int o = va_arg(factor, long long);
    my_processing_spec_o(o, buff, flags);
  }
  if (flags->spec_x || flags->spec_X == 1) {
    long long int x = va_arg(factor, long long);
    my_processing_spec_x(x, buff, c_form, flags);
  }
}

void my_processing_char(char c, char *buff) {
  char str[2];
  str[0] = c;
  str[1] = '\0';
  my_strcat(buff, str);
}

void my_processing_spec_d(va_list factor, char *buff, flags_parse *flags) {
  long int d;
  if (flags->desc_h) {
    d = va_arg(factor, int);
  } else if (flags->desc_l) {
    d = va_arg(factor, unsigned long int);
  } else if (flags->spec_u && flags->desc_l) {
    d = va_arg(factor, unsigned int);
  } else {
    d = va_arg(factor, int);
  }
  flags->fl_space = flags->fl_plus ? 0 : flags->fl_space;
  char str[SMALL];
  char str_znak[2] = {d > 0 ? '+' : '-', '\0'};
  char str_zero[MAX] = "\0";
  char str_prob[MAX] = "\0";
  int flag_znak = d > 0 ? 1 : 0;
  d = d > 0 ? d : -d;
  intToString(d, str);
  int d_size = my_strlen(str);
  int razn = flags->desc_precision > d_size ? flags->desc_precision : d_size;
  if (flags->fl_space && !flags->fl_plus && flag_znak) {
    my_strcat(buff, " ");
  }
  if (flags->desc_width > razn && !flags->fl_minus) {
    for (int i = flags->desc_width - razn - flags->fl_plus - flags->fl_space;
         i != 0; i--) {
      my_strcat(str_prob, " ");
    }
    my_strcat(buff, str_prob);
  }
  if (flags->fl_plus || !flag_znak) {
    my_strcat(buff, str_znak);
  }
  if (d_size < flags->desc_precision) {
    for (int i = flags->desc_precision - d_size; i != 0; i--) {
      my_strcat(str_zero, "0");
    }
    my_strcat(buff, str_zero);
  }

  my_strcat(buff, str);
  if (flags->desc_width > razn && flags->fl_minus) {
    for (int i = flags->desc_width - razn - flags->fl_plus; i != 0; i--) {
      my_strcat(str_prob, " ");
    }
    my_strcat(buff, str_prob);
  }
}

void my_processing_spec_f(double f, char *buff, flags_parse *flags) {
  int add_char = 0;
  int len_sub_buff = 0;
  char sub_buff[MID];
  sub_buff[0] = '\0';
  char aggregate_str[] = "N";
  floatToString(f, sub_buff, flags);
  if (!flags->desc_width) {
    if (flags->negative) add_minus(sub_buff);
    if (!flags->negative && flags->fl_plus) add_plus(sub_buff);
  }
  my_spec_f_width(aggregate_str, &add_char, &len_sub_buff, sub_buff, flags);
  if (flags->fl_space && !flags->negative && !flags->fl_plus)
    add_space(sub_buff);
  my_strcat(buff, sub_buff);
}

void my_spec_f_width(char *aggregate_str, int *add_char, int *len_sub_buff,
                      char *sub_buff, flags_parse *flags) {
  if (flags->desc_width) {
    for (int i = 0; sub_buff[i] != '\0'; i++) {
      (*len_sub_buff)++;
    }
    *add_char = flags->desc_width - (*len_sub_buff);
    if (flags->negative || flags->fl_space || flags->fl_plus) {
      *add_char -= 1;
    }
    if (!flags->fl_minus && flags->negative && !flags->desc_width_zero)
      add_minus(sub_buff);
    if (!flags->fl_minus && !flags->negative && !flags->desc_width_zero &&
        flags->fl_plus)
      add_plus(sub_buff);
    if (!flags->fl_minus) {
      if (flags->desc_width_zero) {
        aggregate_str[0] = '0';
      } else {
        aggregate_str[0] = ' ';
      }
      char zero_line[MID];
      zero_line[0] = '\0';
      for (int i = 0; i < *add_char; i++) {
        my_strcat(zero_line, aggregate_str);
      }
      my_strcat(zero_line, sub_buff);
      sub_buff[0] = '\0';
      my_strcat(sub_buff, zero_line);
      if (flags->negative && flags->desc_width_zero) add_minus(sub_buff);
      if (!flags->negative && flags->desc_width_zero && flags->fl_plus)
        add_plus(sub_buff);
    } else {
      if (flags->negative) add_minus(sub_buff);
      if (!flags->negative && flags->fl_plus) add_plus(sub_buff);
      aggregate_str[0] = ' ';
      char zero_line[MID];
      zero_line[0] = '\0';
      for (int i = 0; i < *add_char; i++) {
        my_strcat(zero_line, aggregate_str);
      }
      my_strcat(sub_buff, zero_line);
    }
  }
}

void add_minus(char *sub_buff) {
  char point_minus[MID];
  point_minus[0] = '-';
  point_minus[1] = '\0';
  my_strcat(point_minus, sub_buff);
  sub_buff[0] = '\0';
  my_strcat(sub_buff, point_minus);
}

void add_plus(char *sub_buff) {
  char point_plus[MID];
  point_plus[0] = '+';
  point_plus[1] = '\0';
  my_strcat(point_plus, sub_buff);
  sub_buff[0] = '\0';
  my_strcat(sub_buff, point_plus);
}

void add_space(char *sub_buff) {
  char point_space[MID];
  point_space[0] = ' ';
  point_space[1] = '\0';
  my_strcat(point_space, sub_buff);
  sub_buff[0] = '\0';
  my_strcat(sub_buff, point_space);
}

void intToString(long long num, char *str) {
  int i = 0;
  int isNegative = 0;
  if (num < 0) {
    isNegative = 1;
    num = -num;
  }
  do {
    int digit = num % 10;
    str[i++] = digit + '0';
    num /= 10;
  } while (num > 0);
  if (isNegative) {
    str[i++] = '-';
  }
  str[i] = '\0';
  for (int j = 0; j < i / 2; j++) {
    char temp = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = temp;
  }
}

void floatToString(double f, char *sub_buff, flags_parse *flags) {
  long long whole = 0;
  long double fractional = 0;
  int precision = 6;
  char str_all[SMALL];
  str_all[0] = '\0';
  char str_whole[SMALL];
  char str_fractional[SMALL];
  sub_buff[0] = '\0';
  int zero_point = 0;
  double tmp_f = f;
  if (tmp_f < 0) {
    flags->negative = 1;
    tmp_f = -tmp_f;
  }
  if (flags->desc_precision || flags->desc_precision_zero) {
    if (flags->desc_precision_zero) {
      precision = 0;
    } else {
      precision = flags->desc_precision;
    }
    tmp_f = tmp_f * pow(10, precision);
    tmp_f = round(tmp_f);
    tmp_f = tmp_f / pow(10, precision);
  }
  whole = (long long)tmp_f;
  fractional = tmp_f - (long double)whole;
  while (((round(fractional * pow(10, precision)) / pow(10, precision)) < 1) &&
         (fractional != 0)) {
    fractional = fractional * 10;
    zero_point++;
  }
  zero_point--;
  fractional = fractional / 10;
  precision = precision - zero_point;
  fractional = fractional * pow(10, precision);
  long long int_fractional = (long long)(fractional + 0.5);
  intToString(whole, str_whole);
  intToString(int_fractional, str_fractional);
  my_strcat(str_all, str_whole);
  my_floatToString_no_precision_zero(str_fractional, str_all, &zero_point,
                                      flags);
  my_strcat(sub_buff, str_all);
}

void my_floatToString_no_precision_zero(char *str_fractional, char *str_all,
                                         int *zero_point, flags_parse *flags) {
  if (!flags->desc_precision_zero) {
    char point_c[2];
    point_c[0] = '.';
    point_c[1] = '\0';
    char point_zero[] = "N";
    point_zero[0] = '0';
    my_strcat(str_all, point_c);
    if (*zero_point > 0) {
      for (int i = 0; i < *zero_point; i++) {
        my_strcat(str_all, point_zero);
      }
    }
    my_strcat(str_all, str_fractional);
  }
}

void my_processing_spec_c(va_list factor, flags_parse *flags, char *buff) {
  char c[2];
  c[0] = va_arg(factor, int);
  c[1] = '\0';
  my_print_str(flags, c, buff);
}

void my_processing_spec_s(va_list factor, flags_parse *flags, char *buff) {
  char *jopa = va_arg(factor, char *);
  int srat = 0;
  if (!jopa) {
    jopa = calloc(MAX, sizeof(char));
    if (jopa) {
      srat = 1;
      my_strcat(jopa, "(null)");
    }
  }
  char s[my_strlen(jopa)];
  if (flags->desc_precision || flags->desc_precision_zero) {
    if (flags->desc_precision < (int)my_strlen(jopa)) {
      for (int i = 0; i < flags->desc_precision; i++) {
        s[i] = jopa[i];
      }
      s[flags->desc_precision] = '\0';
    } else
      my_strcpy(s, jopa);
  } else
    my_strcpy(s, jopa);
  my_print_str(flags, s, buff);
  if (srat) {
    free(jopa);
  }
}

void my_processing_spec_percent(flags_parse *flags, char *buff) {
  char percent[2];
  percent[0] = '%';
  percent[1] = '\0';
  my_print_str(flags, percent, buff);
}

void my_print_str(flags_parse *flags, char *str, char *buff) {
  if (flags->fl_minus) {
    flags->desc_width_zero = 0;
  }
  int start = flags->desc_width - my_strlen(str);
  if (start >= 0) {
    if (flags->desc_width) {
      if (flags->fl_minus) {
        for (size_t i = 0; i < flags->desc_width - my_strlen(str); i++) {
          if (i == 0) {
            my_strcat(buff, str);
          }
          my_strcat(buff, " ");
        }
      } else if (flags->desc_width_zero) {
        for (size_t i = 0; i < flags->desc_width - my_strlen(str); i++) {
          my_strcat(buff, "0");
        }
        my_strcat(buff, str);
      } else {
        for (size_t i = 0; i < flags->desc_width - my_strlen(str); i++) {
          my_strcat(buff, " ");
        }
        my_strcat(buff, str);
      }
    }
  } else
    my_strcat(buff, str);
}

void my_processing_spec_o(long long int o, char *buff, flags_parse *flags) {
  int k = 0;
  char *str = calloc(2000, sizeof(char));
  if (o > 0) {
    while (o != 0) {
      str[k] = (o % 8) + '0';
      o = o / 8;
      k++;
    }
    for (int j = 0; j < k / 2; j++) {
      char temp = str[j];
      str[j] = str[k - j - 1];
      str[k - j - 1] = temp;
    }
    str[k] = '\0';
  } else if (o == 0 && flags->desc_precision) {
    str[0] = '0';
    str[1] = '\0';
  }
  my_format_output(str, buff, flags);
}

void my_processing_spec_x(long long int x, char *buff, char **c_form,
                           flags_parse *flags) {
  char hex[100];
  int i = 0;
  int reg = 0;
  char *str = calloc(2000, sizeof(char));
  if (**c_form == 'X') {
    reg = 55;
  } else if (**c_form == 'x') {
    reg = 87;
  }
  if (x != 0) {
    while (x != 0) {
      int temp = 0;
      temp = x % 16;
      if (temp < 10) {
        hex[i] = temp + 48;
      } else {
        hex[i] = temp + reg;
      }

      x = x / 16;
      i++;
    }
    for (int j = 0; j < i / 2; j++) {
      char temp = hex[j];
      hex[j] = hex[i - j - 1];
      hex[i - j - 1] = temp;
    }
    for (my_size_t i = 0; i < my_strlen(hex); i++) {
      str[i] = hex[i];
    }
    str[i] = '\0';
  } else if (x == 0 && flags->desc_precision) {
    str[0] = '0';
    str[1] = '\0';
  }
  my_format_output(str, buff, flags);
}

void my_format_output(char *str, char *buff, flags_parse *flags) {
  char *str2 = calloc(2000, sizeof(char));
  char *str3 = calloc(2000, sizeof(char));
  if (str && str2 && str3) {
    int arg_len = my_strlen(str);
    if (!flags->fl_minus) {
      if (flags->desc_precision > arg_len) {
        flags->desc_precision -= arg_len;
      } else {
        flags->desc_precision = 0;
      }
      int i = 0;
      for (; i < flags->desc_precision; i++) {
        str2[i] = '0';
      }
      my_strcat(str2, str);
      char valve = (flags->desc_width_zero) ? '0' : ' ';
      if (flags->desc_width > (int)my_strlen(str2)) {
        flags->desc_width -= (int)my_strlen(str2);
      } else {
        flags->desc_width = 0;
      }
      for (int i = 0; i < flags->desc_width; i++) {
        str3[i] = valve;
      }
      my_strcat(str3, str2);
      my_strcat(buff, str3);
    }

    if (flags->fl_minus) {
      if (flags->desc_precision > arg_len) {
        flags->desc_precision -= arg_len;
      } else {
        flags->desc_precision = 0;
      }
      for (int i = 0; i < flags->desc_precision; i++) str2[i] = '0';
      my_strcat(str2, str);
      flags->desc_width = (flags->desc_width > (int)my_strlen(str2))
                              ? flags->desc_width - my_strlen(str2)
                              : 0;
      for (int i = my_strlen(str2), j = 0; j < flags->desc_width; i++, j++)
        str2[i] = ' ';
      my_strcat(buff, str2);
    }
    buff[my_strlen(buff) + 1] = '\0';
    free(str);
    free(str2);
    free(str3);
  }
}
