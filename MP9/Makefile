CC=gcc
CFLAGS=-Wall -Wextra -std=c99 

grader: maze.o
	$(CC) $(CFLAGS) maze.o -o grader

maze.o: maze.c
	$(CC) $(CFLAGS) -c maze.c

clean:
	rm -f maze.o grader.o grader
