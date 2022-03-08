sources = *.c
target = avltree
CC = gcc
CCFLAG = -g -fsanitize=address -fno-omit-frame-pointer

all:
	$(CC) $(CCFLAG) $(sources) -o $(target)
