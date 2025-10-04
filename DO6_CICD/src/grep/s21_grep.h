#ifndef S21_GREP_H
#define S21_GREP_H
#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct options {
  int e;  // работает
  int i;  // работает
  int v;  // работает
  int c;  // работает
  int l;  // работает
  int n;  // работает
  int h;  // работает
  int s;  // работает
  int f;  // работает
  int o;  // работает
  char *pattern;
  int len_pattern;
  int mem_pattern;
} options;

void pattern_add(options *flags, char *pattern);
void add_reg_from_file(options *flags, char *filepath);
options options_parser(int argc, char **argv);
void output_line(char *line, int n);
void processFile(options flags, char *path, regex_t *reg);
void output(options flags, int argc, char **argv);

#endif
