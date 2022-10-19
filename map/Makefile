CFLAGS = -g -O0 -Wall

all:map_test.out example.out

example.out: exmaple.o rbtree.o map.o
	gcc $(CFLAGS) $^ -o $@

exmaple.o: example.c
	gcc $(CFLAGS) -c $< -o $@

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
