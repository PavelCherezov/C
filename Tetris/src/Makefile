.POSIX:
CC=gcc -std=c11
CFLAGS = -Wall -Wextra -Werror
INSTALL_FILES = main.c gui/cli/*.c brick_game.a -lncurses
INSTALL_TEST = brick_game/tetris/*.c gui/cli/*.c  brick_game.a -lncurses
FLAGSCH = -lcheck
TARGET = brick_game


ifeq ($(shell uname),Linux)
	FLAGSCH += -lm -lsubunit
endif
	
all: clean install

install: backend.a
	$(CC) $(CFLAGS) $(INSTALL_FILES) -o game
	./game

uninstall:
	rm -rf game

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info report *.dSYM game test *.gz *.dvi *.aux *.log

test: clean backend.a
	$(CC) $(INSTALL_TEST) --coverage tests/test.c -o test $(FLAGSCH)
	./test

backend.a: backend.o
	ar rcs $(TARGET).a *.o
	ranlib $(TARGET).a

backend.o: 
	$(CC) -c brick_game/tetris/*.c 

dist:
	tar -czvf archive.tar.gz ./*

gcov_report: test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html
	rm -rf *gcda *gcno res.info test

clang:
	clang-format -style=Google -n gui/cli/*.c
	clang-format -style=Google -n brick_game/tetris/*.c
	clang-format -style=Google -n main.c
	clang-format -style=Google -n tests/*.c
	clang-format -style=Google -n *.h

clang_instal:
	clang-format -style=Google -i gui/cli/*.c
	clang-format -style=Google -i brick_game/tetris/*.c
	clang-format -style=Google -i main.c
	clang-format -style=Google -i tests/*.c
	clang-format -style=Google -i *.h	

.PHONY: all install unistall clean test dvi dist gcov_report clang 