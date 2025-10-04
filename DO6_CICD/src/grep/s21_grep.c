#include "s21_grep.h"

int main(int argc, char **argv) {
  options flags = options_parser(argc, argv);
  output(flags, argc, argv);
  free(flags.pattern);
  return 0;
}

void pattern_add(options *flags, char *pattern) {
  if (pattern != NULL) {
    int n = strlen(pattern);
    if (flags->len_pattern == 0) {
      flags->pattern = malloc(1024 * sizeof(char));
      // flags->pattern = '\0';
      flags->mem_pattern = 1024;
    }
    if (flags->mem_pattern < flags->len_pattern + n) {
      flags->pattern = realloc(flags->pattern, flags->mem_pattern * 2);
    }
    if (flags->len_pattern != 0) {
      strcat(flags->pattern + flags->len_pattern, "|");
      flags->len_pattern++;
    }
    flags->len_pattern +=
        sprintf(flags->pattern + flags->len_pattern, "(%s)", pattern);
  } else {
    fprintf(stderr,
            "usage: grep [-abcdDEFGHhIiJLlMmnOopqRSsUVvwXxZz] [-A num] [-B "
            "num] [-C[num]]\n\t[-e pattern] [-f file] [--binary-files=value] "
            "[--color=when]\n\t[--context[=num]] [--directories=action] "
            "[--label] [--line-buffered]\n\t[--null] [pattern] [file ...]");
    exit(0);
  }
}

void add_reg_from_file(options *flags, char *filepath) {
  FILE *f = fopen(filepath, "r");
  if (f == NULL) {
    if (!flags->s)
      fprintf(stderr, "grep: %s: No such file or directory", filepath);
  } else {
    char *line = NULL;
    int read = 0;
    size_t memlen = 0;
    read = getline(&line, &memlen, f);
    while (read != -1) {
      if (line[read - 1] == '\n') line[read - 1] = '\0';
      pattern_add(flags, line);
      read = getline(&line, &memlen, f);
    }

    free(line);
    fclose(f);
  }
}
options options_parser(int argc, char **argv) {
  options flags = {0};
  int opt = 0;

  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        flags.e = 1;
        pattern_add(&flags, optarg);
        break;
      case 'i':
        flags.i = REG_ICASE;
        break;
      case 'v':
        flags.v = 1;
        break;
      case 'c':
        flags.c = 1;
        break;
      case 'l':
        flags.l = 1;
        break;
      case 'n':
        flags.n = 1;
        break;
      case 'h':
        flags.h = 1;
        break;
      case 's':
        flags.s = 1;
        break;
      case 'f':
        flags.f = 1;
        add_reg_from_file(&flags, optarg);
        break;
      case 'o':
        flags.o = 1;
        break;
    }
  }
  if ((flags.v == 1 || flags.c == 1 || flags.l == 1) && (flags.o == 1)) {
    flags.o = 0;
  }
  if (flags.len_pattern == 0) {
    pattern_add(&flags, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    flags.h = 1;
  }
  return flags;
}

// вывод символов строки
void output_line(char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

void print_match(regex_t *re, char *line) {
  regmatch_t math;
  int offset = 0;
  while (1) {
    int result =
        regexec(re, line + offset, 1, &math, 0);  // что совпадение найдено

    if (result != 0) {
      break;
    }
    for (int i = math.rm_so; i < math.rm_eo; i++) {
      putchar(line[i]);
    }
    putchar('\n');
    offset += math.rm_eo;
  }
}

// обработка файла
void processFile(options flags, char *path, regex_t *reg) {
  FILE *f = fopen(path, "r");

  if (f == NULL) {
    if (!flags.s) fprintf(stderr, "grep: %s: No such file or directory", path);
  } else {
    char *line = NULL;
    size_t memlen = 0;
    int read = 0;
    int line_count = 1;
    int c = 0;
    read = getline(&line, &memlen, f);
    //?
    while (read != -1) {
      int result = regexec(reg, line, 0, NULL, 0);
      if ((result == 0 && !flags.v) || (flags.v && result != 0)) {
        if (!flags.c && !flags.l) {
          if (!flags.h) printf("%s:", path);
          if (flags.n) printf("%d:", line_count);
          if (flags.o) {
            print_match(reg, line);
          } else {
            output_line(line, read);
          }
        }
        c++;
      }
      read = getline(&line, &memlen, f);
      line_count++;
    }

    free(line);
    if (flags.c && !flags.l) {
      if (!flags.h) printf("%s:", path);
      printf("%d\n", c);
    }
    if (flags.l && c > 0) printf("%s\n", path);

    fclose(f);
  }
}

// вывод из всех файлов
void output(options flags, int argc, char **argv) {
  regex_t re;
  // printf("%s", flags.pattern);
  int error = regcomp(&re, flags.pattern, REG_EXTENDED | flags.i);
  if (error) perror("Error");

  for (int i = optind; i < argc; i++) {
    processFile(
        flags, argv[i],
        &re);  // будем вызывть эту функцию для каждого файла в командной строке
  }
  regfree(&re);
}
