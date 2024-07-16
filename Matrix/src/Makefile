CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 

ifeq ($(shell uname),Linux)
	Flags = -lcheck  -lm -lrt -lpthread -lsubunit
else
    Flags = -lcheck -lm -lpthread
endif

TEST_C = all_test_matrix.c
LIB_C = my_*.c
LIB_O = $(LIB_C:.c=.o)

all: clean my_matrix.a test gcov_report

clang:
	clang-format -style=Google -n $(LIB_C) $(TEST_C) *.h

test: clean
	$(CC) $(CFLAGS) --coverage $(LIB_C) $(TEST_C) -o $@ $(Flags)
	./test

my_matrix.a: clean
	$(CC) $(CFLAGS) -c $(LIB_C) $(Flags)
	ar rcs $@ *.o
	ranlib $@
	rm *.o

.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

gcov_report: test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html

clean:
	rm -rf *.out *.o *.a test *.gc* *.info report *.dSYM

rebuild: clean all