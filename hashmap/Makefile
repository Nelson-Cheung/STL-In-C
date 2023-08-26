CC = clang-12
CFLAGS = -g -O3 -Wall

all:map_test.out example.out

example.out: exmaple.o hashmap.o
	$(CC) $(CFLAGS) $^ -o $@

exmaple.o: example.c
	$(CC) $(CFLAGS) -c $< -o $@

map_test.out: test.o hashmap.o
	$(CC) $(CFLAGS) $^ -o $@

test.o: test.c
	$(CC) $(CFLAGS) -c $< -o $@

hashmap.o: hashmap.c hashmap.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean

clean:
	rm *.o *.out
