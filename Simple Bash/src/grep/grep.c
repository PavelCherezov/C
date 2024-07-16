#include "grep.h"

int main(int argc, char *argv[]) {
  Grep_Opt opt = {false};
  Grep_Str str = {0};
  options(argc, argv, &opt, &str);
  if (argc - optind > 1 && !opt.h) {
    opt.q = true;
  }
  if (!opt.exit) {
    for (int i = optind; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (file != NULL) {
        grep_input(&opt, &str, file, argv[i]);
        fclose(file);
      } else if (!opt.s) {
        printf("grep: %s: No such file or directory\n", argv[i]);
      }
    }
  }
  return 0;
}

void options(int argc, char *argv[], Grep_Opt *opt, Grep_Str *str) {
  opt_switch(argc, argv, opt, str);
  if (!opt->e && !opt->f && argc > optind) {
    strcat(str->str_regex, argv[optind]);
    optind++;
  }
  if (opt->e || opt->f) {
    del_last(str->str_regex);
  }
  if (opt->v || opt->c || opt->l) {
    opt->o = false;
  }
}

void opt_switch(int argc, char *argv[], Grep_Opt *opt, Grep_Str *str) {
  char current_Grep_Opt;
  while ((current_Grep_Opt =
              getopt_long(argc, argv, "e:ivclnhsf:o", NULL, 0)) != -1) {
    switch (current_Grep_Opt) {
      case 'e':
        opt->e = true;
        strcat(str->str_regex, optarg);
        strcat(str->str_regex, "|");
        break;
      case 'i':
        opt->i = true;
        break;
      case 'v':
        opt->v = true;
        break;
      case 'c':
        opt->c = true;
        break;
      case 'l':
        opt->l = true;
        break;
      case 'n':
        opt->n = true;
        break;
      case 'h':
        opt->h = true;
        break;
      case 's':
        opt->s = true;
        break;
      case 'f':
        opt->f = true;
        flag_f(str);
        break;
      case 'o':
        opt->o = true;
        break;
      default:
        opt->exit = true;
    }
  }
}

void flag_f(Grep_Str *str) {
  FILE *f_patern = fopen(optarg, "r");
  char f_str[SIZE];
  while (fgets(f_str, SIZE, f_patern)) {
    strcat(str->str_regex, f_str);
    if (str->str_regex[strlen(str->str_regex) - 1] == '\n' &&
        strlen(f_str) > 1) {
      del_last(str->str_regex);
    }
    strcat(str->str_regex, "|");
  }
  fclose(f_patern);
}

void grep_input(Grep_Opt *opt, Grep_Str *str, FILE *current_file, char *argv) {
  Grep_Input name;
  strcpy(name.file_name, "");
  strcpy(name.file_name_l, argv);
  strcpy(name.str_quantity, "");
  regex_t reg;
  regmatch_t start;
  int match = 0;
  size_t match_quantity = 0;
  if (opt->q) {
    strcpy(name.file_name, argv);
    strcat(name.file_name, ":");
  }
  if (opt->i) {
    regcomp(&reg, str->str_regex, REG_EXTENDED | REG_ICASE);
  } else {
    regcomp(&reg, str->str_regex, REG_EXTENDED);
  }
  while (fgets(str->str_file, SIZE, current_file)) {
    match = regexec(&reg, str->str_file, 1, &start, 0);
    if (opt->n) {
      flag_n(&name);
    }
    if (opt->v) {
      match = !match;
    }
    if (opt->c && !match) {
      match_quantity++;
    }
    if (opt->l && !match) {
      break;
    }
    if (!match && !opt->c && !opt->o) {
      printf("%s%s%s", name.file_name, name.str_quantity, str->str_file);
      print_n(str->str_file);
    }
    if (opt->o && !match) {
      flag_o(str, &name, reg, start);
    }
  }
  if (opt->c) {
    printf("%s%ld\n", name.file_name, match_quantity);
  }
  if (opt->l && !match) {
    printf("%s\n", name.file_name_l);
  }
  regfree(&reg);
}

void flag_n(Grep_Input *name) {
  int num;
  if (name->str_quantity[strlen(name->str_quantity) - 1] == ':') {
    del_last(name->str_quantity);
  }
  num = atoi(name->str_quantity);
  num++;
  sprintf(name->str_quantity, "%d", num);
  strcat(name->str_quantity, ":");
}

void flag_o(Grep_Str *str, Grep_Input *name, regex_t reg, regmatch_t start) {
  char *str_o;
  strcpy(str->str_file_o, str->str_file);
  bool flag = true;
  str_o = str->str_file_o;
  while (regexec(&reg, str_o, 1, &start, 0) == 0) {
    if (flag) {
      printf("%s%s%.*s\n", name->file_name, name->str_quantity,
             (int)(start.rm_eo - start.rm_so), str_o + start.rm_so);
      str_o += start.rm_eo;
      flag = false;
    } else {
      printf("%.*s\n", (int)(start.rm_eo - start.rm_so), str_o + start.rm_so);
      str_o += start.rm_eo;
    }
  }
}

void print_n(char *last_str) {
  size_t i = strlen(last_str) - 1;
  if (last_str[i] != '\n') {
    printf("\n");
  }
}

void del_last(char *str) {
  size_t i = strlen(str) - 1;
  str[i] = '\0';
}