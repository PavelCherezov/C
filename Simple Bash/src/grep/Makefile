CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

all:
	$(CC) $(CFLAGS) grep.c -o grep

grep: clean
	make all

test:
	sh testgrep.sh

rebuild:
	make clean
	make all

clean:
	rm -rf grep
