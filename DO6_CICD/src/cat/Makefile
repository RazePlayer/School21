SHELL := /bin/bash

CC = gcc
CC_FLAGS = -c -Wall -Werror -Wextra -std=c11
BUILD_NAME = s21_cat

all: s21_cat test

rebuild: clean s21_cat

s21_cat: s21_cat.o
	${CC} s21_cat.o -o ${BUILD_NAME}

s21_cat.o: s21_cat.c
	${CC} s21_cat.c ${CC_FLAGS} -o s21_cat.o

clean:
	rm -rf ./*.o
	rm -rf ./${BUILD_NAME}

test:
	-diff <(./s21_cat -e test.txt) <(cat -e test.txt)
	-diff <(./s21_cat -v test.txt) <(cat -v test.txt)	
	-diff <(./s21_cat -s test.txt) <(cat -s test.txt)
	-diff <(./s21_cat -n test.txt) <(cat -n test.txt)	
	-diff <(./s21_cat -t test.txt) <(cat -t test.txt)
	-diff <(./s21_cat -b test.txt) <(cat -b test.txt)
