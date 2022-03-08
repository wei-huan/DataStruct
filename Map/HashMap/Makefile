sources = *.c
target = hashmap
CC = gcc
CCFLAG = -g -fsanitize=address -fno-omit-frame-pointer

all:
	@$(CC) $(CCFLAG) $(sources) -o $(target)

run: all
	@./$(target)

.PHONY: all run