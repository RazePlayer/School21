#ifndef S21_CAT_H
#define S21_CAT_H
#define _GNU_SOURCES
#include <getopt.h>
#include <stdio.h>

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} options;

struct option long_options[] = {{"number-nonblank", 0, NULL, 'b'},
                                {"number", 0, NULL, 'n'},
                                {"squeeze-blank", 0, NULL, 's'},
                                {0, 0, 0, 0}};

int parser(int argc, char *argv[], char *short_options,
           struct option long_options[], options *flags, int *error);
void reader(char *currentArg, options *flags);

#endif