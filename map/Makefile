all:map_test
CFLAGS=-g -O0 -Wall

map_test.out: test.o rbtree.o map.o
	gcc $(CFLAGS) $^ -o $@

test.o: test.c
	gcc $(CFLAGS) -c $< -o $@

rbtree.o: rbtree.c rbtree.h
	gcc $(CFLAGS) -c $< -o $@

map.o: map.c map.h
	gcc $(CFLAGS) -c $< -o $@

.PHONY:clean

clean:
	rm *.o *.out
