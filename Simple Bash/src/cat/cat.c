#include "cat.h"

int main(int argc, char *argv[]) {
  Cat_Opt opt = {false};
  options(argc, argv, &opt);
  if (!opt.exit) {
    for (int i = optind; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        printf("cat: %s: No such file or directory\n", argv[i]);
        continue;
      }
      cat_input(&opt, file);
      fclose(file);
    }
  }
  return 0;
}

void options(int argc, char *argv[], Cat_Opt *opt) {
  char current_Cat_Opt;
  while ((current_Cat_Opt =
              getopt_long(argc, argv, "+beEnstT", Long_Cat_Opt, 0)) != -1) {
    switch (current_Cat_Opt) {
      case 'b':
        opt->b = true;
        break;
      case 'e':
        opt->e = true;
        opt->v = true;
        break;
      case 'E':
        opt->e = true;
        break;
      case 'n':
        opt->n = true;
        break;
      case 's':
        opt->s = true;
        break;
      case 't':
        opt->t = true;
        opt->v = true;
        break;
      case 'T':
        opt->t = true;
        break;
      default:
        opt->exit = true;
    }
  }
  if (opt->b) {
    opt->n = false;
  }
}

void cat_input(Cat_Opt *opt, FILE *current_file) {
  char last_char = '\n';
  int current_str = 1;
  int flag_s = 0;
  int current_char = fgetc(current_file);
  while (current_char != EOF) {
    if (opt->s && current_char == '\n' && last_char == '\n') {
      ++flag_s;
    } else if (opt->s) {
      flag_s = 0;
    }
    if (flag_s < 2) {
      if (opt->n && last_char == '\n') {
        printf("%6d\t", current_str);
        ++current_str;
      }
      if (opt->b && last_char == '\n' && current_char != '\n') {
        printf("%6d\t", current_str);
        ++current_str;
      }
      if (opt->e && current_char == '\n') {
        printf("$");
      }
      if (opt->t && current_char == '\t') {
        printf("^I");
        last_char = current_char;
        current_char = fgetc(current_file);
        continue;
      }
      if (opt->v && current_char != '\n' && current_char != '\t') {
        if (current_char > 127 && current_char < 160) {
          printf("M-^");
        }
        if (current_char < 32 || current_char == 127) {
          printf("^");
        }
        if (current_char < 32 || (current_char > 126 && current_char < 160)) {
          current_char =
              current_char > 126 ? current_char - 128 + 64 : current_char + 64;
        }
      }
      printf("%c", current_char);
    }
    last_char = current_char;
    current_char = fgetc(current_file);
  }
}