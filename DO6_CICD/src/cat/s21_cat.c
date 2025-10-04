#include "s21_cat.h"

int main(int argc, char *argv[]) {
  struct options flags = {0};
  char *short_options = "beEnstTv";
  int error = 0;
  int indexOfArgv = 0;

  indexOfArgv = parser(argc, argv, short_options, long_options, &flags, &error);

  if (error == 1) {
    fprintf(stderr, "ERROR");
  } else {
    while (indexOfArgv < argc) {
      char *currentArg = argv[indexOfArgv];
      reader(currentArg, &flags);
      indexOfArgv++;
    }
  }
  return 0;
}

int parser(int argc, char *argv[], char *short_options,
           struct option long_options[], options *flags, int *error) {
  int c;
  int ind = 0;

  while ((c = getopt_long(argc, argv, short_options, long_options, &ind)) !=
         -1) {
    switch (c) {
      case 'b':
        flags->b = 1;
        break;
      case 'e':
        flags->e = 1;
        flags->v = 1;
        break;
      case 'E':
        flags->e = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 't':
        flags->t = 1;
        flags->v = 1;
        break;
      case 'T':
        flags->t = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      default:
        *error = 1;
        break;
    }
  }
  return optind;
}

void reader(char *currentArg, options *flags) {
  int symbol;
  char lastSymbol;
  int currentLine = 1, squeeze = 0;
  FILE *f = fopen(currentArg, "r");

  if (f != NULL) {
    for (lastSymbol = '\n'; (symbol = fgetc(f)) != EOF; lastSymbol = symbol) {
      if (flags->s) {
        if (lastSymbol == '\n' && symbol == '\n') {
          if (squeeze == 1) continue;
          squeeze++;
        } else
          squeeze = 0;
      }

      if (flags->n && flags->b == 0) {
        if (lastSymbol == '\n') {
          printf("%6d\t", currentLine);
          currentLine++;
        }
      }

      if (flags->b) {
        if (lastSymbol == '\n' && symbol != '\n') {
          printf("%6d\t", currentLine);
          currentLine++;
        }
      }

      if (flags->e && symbol == '\n') {
        if (flags->b && lastSymbol == '\n' && symbol == '\n') {
          printf("      \t$");
        } else {
          printf("$");
        }
      }
      if (flags->t && symbol == '\t') {
        printf("^I");
      } else if (flags->v == 1) {
        if ((symbol >= 0 && symbol <= 31) && symbol != '\t' && symbol != '\n') {
          printf("^%c", symbol + 64);
        } else if (symbol == 127) {
          printf("^?");
        } else if ((symbol >= 128 && symbol < 128 + 32) && symbol != '\t' &&
                   symbol != '\n') {
          printf("M-^%c", symbol - 64);
        } else {
          putchar(symbol);
        }

      } else {
        putchar(symbol);
      }
    }
    fclose(f);
  } else
    fprintf(stderr, "No such file or directory: %s\n", currentArg);
}