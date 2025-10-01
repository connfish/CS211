
CC=gcc
CFLAG = -fsanitize=address,undefined -Og -g -Wall -Werror -std=c11 

first: first.c 
	$(CC) -o first first.c $(CFLAG)
clean: first
	rm -f first