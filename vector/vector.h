#ifndef _VECTOR_H
#define _VECTOR_H

#ifndef NULL
#define NULL 0
#endif

struct vector {
    int size;
    int capacity;
    char *data;
    int item_size;
};

typedef void (*vector_for_each_t)(const void *item);

// create a vector
struct vector vector_init(int item_size);
// free the memory of vector
void vector_clear(struct vector *vector);
// get size of vector
int vector_size(struct vector *vector);
// get item at the given position
void *vector_at(struct vector *vector, int idx);
// get the first item
void *vector_front(struct vector *vector);
// get the last item
void *vector_back(struct vector *vector);
// insert item at the given position
int vector_insert(struct vector *vector, const void *item, int pos);
// insert item behind the last item
void vector_push_back(struct vector *vector, const void *item);
// pop the last item
void vector_pop_back(struct vector *vector);
// erase item at the given position
void vector_erase(struct vector *vector, int pos);
// traverse vector
void vector_for_each(struct vector *vector, vector_for_each_t for_each);

#endif