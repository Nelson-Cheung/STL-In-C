#ifndef _MAP_H
#define _MAP_H

#include "rbtree.h"

struct map_t
{
    struct rb_node node;
    void *key;
    void *val;
};

struct map
{
    struct rb_root root;
    int key_size;
    int val_size;
};

typedef void (*map_for_each_t)(const void *key, const void *val);

// create a map
struct map map_init(int key_size, int value_size);
// free the memory of map
void map_clear(struct map *m);
// get map item by key
void *map_get(struct map *m, const void *key);
// put an item to map
int map_put(struct map *m, const void *key, const void *val);
// delete a map item
int map_del(struct map *m, const void *key);
// traverse map
void map_for_each(struct map *m, map_for_each_t for_each);

struct map_t *_map_get(struct map *m, const void *key);
int _map_del(struct map *m, struct map_t *item);
int _map_compare(struct map *m, const void *key1, const void *key2);
void _map_clear(struct rb_node *root);

#endif