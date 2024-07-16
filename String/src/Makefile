CC = gcc -Wall -Werror -Wextra -std=c11
OS = $(shell uname)

ifeq ($(OS),Linux)
    Flags = -lcheck  -lm -lrt -lpthread -lsubunit
else
    Flags = -lcheck -lm -lpthread
endif

all: clean string.a

string: clean string.a test

string.a:
	$(CC) -c *.c $(Flags)
	ar rcs string.a *.o
	ranlib string.a
	rm *.o

test:
	$(CC) --coverage *.c test_dir/*.c -o test $(Flags)
	./test

gcov_report: test
	./test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html

clean:
	rm -rf *.a *.o test *.gcno *.gcda report *.info


cn: 
	clang-format -style=Google -n *.c *.h


