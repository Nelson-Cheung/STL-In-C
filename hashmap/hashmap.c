#include "hashmap.h"
#include "xxhash32.h"
#include <stdlib.h>
#include <string.h>

struct hashmap hashmap_init(int key_size, int value_size)
{
    struct hashmap hashmap;

    hashmap.table_size = MAP_TABLE_SIZE;
    hashmap.table = malloc(sizeof(struct hashmap_t) * hashmap.table_size);
    hashmap.key_size = key_size;
    hashmap.val_size = value_size;
    hashmap.size = 0;

    for (int i = 0; i < hashmap.table_size; ++i)
    {
        hashmap.table[i].next = NULL;
    }

    return hashmap;
}

void hashmap_clear(struct hashmap *m)
{
    for (int i = 0; i < m->table_size; ++i)
    {
        struct hashmap_t *current = m->table[i].next;
        struct hashmap_t *next = NULL;
        while (current)
        {
            next = current->next;
            free(current);
            current = next;
        }
    }
    free(m->table);

    m->table = NULL;
    m->size = 0;
    m->key_size = 0;
    m->val_size = 0;
    m->table_size = 0;
}

static inline unsigned int hashmap_index(struct hashmap *m, const void *key)
{
    return xxhash32(key, m->key_size, 0) % m->table_size;
}

static inline unsigned int hashmap_compare(struct hashmap *m, const void *x, const void *y)
{
    return memcmp(x, y, m->key_size) ? 0 : 1;
}

static inline struct hashmap_t *hashmap_find(struct hashmap *m, const void *key)
{
    unsigned int i = hashmap_index(m, key);
    struct hashmap_t *current = m->table[i].next;

    while (current)
    {
        if (hashmap_compare(m, key, current->key))
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void *hashmap_get(struct hashmap *m, const void *key)
{
    struct hashmap_t *item = hashmap_find(m, key);
    return item ? item->val : NULL;
}

void hashmap_put(struct hashmap *m, const void *key, const void *val)
{
    struct hashmap_t *item = hashmap_find(m, key);
    if (item)
    {
        memcpy(item->val, val, m->val_size);
    }
    else
    {
        unsigned int i = hashmap_index(m, key);
        struct hashmap_t *item = malloc(sizeof(struct hashmap_t));
        item->key = malloc(m->key_size);
        item->val = malloc(m->val_size);
        item->next = m->table[i].next;
        m->table[i].next = item;
        memcpy(item->key, key, m->key_size);
        memcpy(item->val, val, m->val_size);
        m->size += 1;
    }
}

void hashmap_del(struct hashmap *m, const void *key)
{
    unsigned int i = hashmap_index(m, key);
    struct hashmap_t *current = m->table[i].next;
    struct hashmap_t *prev = &(m->table[i]);

    while (current)
    {
        if (hashmap_compare(m, key, current->key))
        {
            prev->next = current->next;
            free(current);
            m->size -= 1;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void hashmap_for_each(struct hashmap *m, hashmap_for_each_t for_each, void *contex)
{
    for (int i = 0; i < m->table_size; ++i)
    {
        struct hashmap_t *current = m->table[i].next;
        while (current)
        {
            for_each(contex, current->key, current->val);
            current = current->next;
        }
    }
}

unsigned int hashmap_size(struct hashmap *m)
{
    return m->size;
}