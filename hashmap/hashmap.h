#ifndef _HASHMAP_H
#define _HASHMAP_H

#define MAP_TABLE_SIZE 8191

struct hashmap_t
{
    void *key;
    void *val;
    struct hashmap_t *next;
};

struct hashmap
{
    struct hashmap_t *table;
    int table_size;
    int key_size;
    int val_size;
    int size;
};

typedef void (*hashmap_for_each_t)(void *contex, const void *key, const void *val);

// create a map
struct hashmap hashmap_init(int key_size, int value_size);
// free the memory of map
void hashmap_clear(struct hashmap *m);
// get map item by key
void *hashmap_get(struct hashmap *m, const void *key);
// put an item to map
void hashmap_put(struct hashmap *m, const void *key, const void *val);
// delete a map item
void hashmap_del(struct hashmap *m, const void *key);
// traverse map
void hashmap_for_each(struct hashmap *m, hashmap_for_each_t for_each, void *contex);
// get map size
unsigned int hashmap_size(struct hashmap *m);


#endif