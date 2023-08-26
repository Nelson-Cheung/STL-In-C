CFLAGS = -g -O3 -Wall
CC = gcc

all: queue_test.out

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) $< -c -o $@

queue_test.o: test.c
	$(CC) $(CFLAGS) $< -c -o $@

queue_test.out: queue.o queue_test.o
	$(CC) $(CFLAGS) $^ -o $@
	
.PHONY:clean

clean:
	rm *.o *.out
