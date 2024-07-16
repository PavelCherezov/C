#ifndef CAT_H
#define CAT_H
#define _GNU_SOURCE

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool v;
  bool exit;
} Cat_Opt;

static const struct option Long_Cat_Opt[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {NULL, 0, NULL, 0}};

void options(int argc, char *argv[], Cat_Opt *opt);
void cat_input(Cat_Opt *opt, FILE *current_file);

#endif