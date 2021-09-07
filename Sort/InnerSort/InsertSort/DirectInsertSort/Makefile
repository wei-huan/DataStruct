sources = *.c 
target = directinsertsort
CC = gcc
CCFLAG = -g -Wall -fsanitize=address -fno-omit-frame-pointer

all: 
	$(CC) $(CCFLAG) $(sources) -o $(target)

clean:
	rm -f $(target)