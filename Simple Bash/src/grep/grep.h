#ifndef GREP_H
#define GREP_H
#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000

typedef struct {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool s;
  bool f;
  bool o;
  bool q;
  bool exit;
} Grep_Opt;

typedef struct {
  char str_file[SIZE];
  char str_regex[SIZE];
  char str_file_o[SIZE];
} Grep_Str;

typedef struct {
  char file_name[SIZE];
  char file_name_l[SIZE];
  char str_quantity[SIZE];
} Grep_Input;

void options(int argc, char *argv[], Grep_Opt *opt, Grep_Str *str);
void grep_input(Grep_Opt *opt, Grep_Str *str, FILE *current_file, char *argv);
void print_n(char *last_str);
void del_last(char *str);
void opt_switch(int argc, char *argv[], Grep_Opt *opt, Grep_Str *str);
void flag_f(Grep_Str *str);
void flag_o(Grep_Str *str, Grep_Input *name, regex_t reg, regmatch_t start);
void flag_n(Grep_Input *name);

#endif