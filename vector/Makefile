CFLAGS = -g -O0 -Wall
CC = gcc
all: vector_test.out example.out

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) $< -c -o $@

vector_test.o: test.c
	$(CC) $(CFLAGS) $< -c -o $@

vector_test.out: vector.o vector_test.o
	$(CC) $(CFLAGS) $^ -o $@

example.o: example.c 
	$(CC) $(CFLAGS) $< -c -o $@

example.out: example.o vector.o
	$(CC) $(CFLAGS) $^ -o $@
	
.PHONY:clean

clean:
	rm *.o *.out
