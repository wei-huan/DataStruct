sources = *.c
target = multikeysort
CC = gcc
CCFLAG = -g -Wall -fsanitize=address -fno-omit-frame-pointer 

all: 
	$(CC) $(CCFLAG) $(sources) -o $(target)

clean:
	rm -f $(target)