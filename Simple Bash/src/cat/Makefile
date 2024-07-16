CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

all:
	$(CC) $(CFLAGS) cat.c -o cat

cat: clean
	make all

test:
	sh testcat.sh

rebuild:
	make clean
	make all

clean:
	rm -rf cat
