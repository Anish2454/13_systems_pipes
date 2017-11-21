all: pipes.c
	gcc -g -o pipes pipes.c

run: all
	./pipes
