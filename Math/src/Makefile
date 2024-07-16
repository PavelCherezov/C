CC = gcc -Wall -Werror -Wextra -std=c11
OS = $(shell uname)

ifeq ($(OS),Linux)
	Flags = -lcheck  -lm -lrt -lpthread -lsubunit
else
	Flags = -lcheck -lm -lpthread
endif

all: clean my_math.a test

my_math: clean my_math.a test

my_math.a:
	$(CC) -c my_math.c -o my_math.o
	ar rcs my_math.a *.o
	ranlib my_math.a
	rm *.o

test:
	$(CC) --coverage my_math.c my_math_test.c -o test $(Flags)

gcov_report: test
	./test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html

clang:
	clang-format -style=Google -n *.c *.h

clean:
	rm -rf *.a *.o test *.gcno *.gcda *.info report

rebuild:
	clean all
