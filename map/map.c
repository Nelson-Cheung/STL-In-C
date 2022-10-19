#include "map.h"
#include "rbtree.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct map map_init(int key_size, int val_size)
{
    struct map m = {
        .root = RB_ROOT,
        .key_size = key_size,
        .val_size = val_size,
    };

    return m;
}

void map_clear(struct map *m)
{
    struct rb_node *node = rb_first(&(m->root));
    struct map_t *item = NULL;

    while (node) {
        item = rb_entry(node, struct map_t, node);
        _map_del(m, item);
        node = rb_first(&(m->root));
    }

    m->root = RB_ROOT;
}

int _map_compare(struct map *m, const void *key1, const void *key2)
{
    char *i = (char *)key1;
    char *j = (char *)key2;

    for (int k = 0; k < m->key_size; ++k)
    {
        if (i[k] > j[k])
            return 1;
        else if (i[k] < j[k])
            return -1;
    }

    return 0;
}

void *map_get(struct map *m, const void *key)
{
    struct map_t *item = _map_get(m, key);
    return item ? item->val : NULL;
}

int map_put(struct map *m, const void *key, const void *val)
{
    struct rb_node **new_node = &(m->root.rb_node);
    struct rb_node *parent = NULL;

    while (*new_node) {
        struct map_t *this_node = rb_entry(*new_node, struct map_t, node);
        int cmp = _map_compare(m, key, this_node->key);
        parent = *new_node;

        if (cmp < 0) {
            new_node = &((*new_node)->rb_left);
        } else if (cmp > 0) {
            new_node = &((*new_node)->rb_right);
        } else {
            memcpy(this_node->val, val, m->val_size);
            return 0;
        }
    }

    struct map_t *item = (struct map_t *)malloc(sizeof(struct map_t));
    item->key = malloc(m->key_size);
    memcpy(item->key, key, m->key_size);
    item->val = malloc(m->val_size);
    memcpy(item->val, val, m->val_size);

    rb_link_node(&item->node, parent, new_node);
    rb_insert_color(&item->node, &(m->root));

    return 0;
}

int _map_del(struct map *m, struct map_t *item)
{
    rb_erase(&(item->node), &(m->root));
    free(item->key);
    free(item->val);
    free(item);    

    return 0;
}

int map_del(struct map *m, const void *key)
{
    struct map_t *item = _map_get(m, key);
    if (!item) {
        return -1;
    }

    _map_del(m, item);
    return 0;
}

void map_for_each(struct map *m, map_for_each_t for_each)
{
    struct rb_node *node = rb_first(&(m->root));
    while(node) {
        struct map_t *item = rb_entry(node, struct map_t, node);
        for_each(item->key, item->val);
        node = rb_next(node);
    }
}

struct map_t *_map_get(struct map *m, const void *key)
{
    struct rb_node *node = m->root.rb_node;
    while (node)
    {
        struct map_t *item = rb_entry(node, struct map_t, node);
        int cmp = _map_compare(m, key, item->key);
        if (cmp < 0) {
            node  = node->rb_left;
        } else if (cmp > 0) {
            node = node->rb_right;
        } else {
            return item;
        }
    }
    return NULL;
}