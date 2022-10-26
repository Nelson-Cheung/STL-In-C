#include "vector.h"
#include <stdlib.h>
#include <string.h>

struct vector vector_init(int item_size)
{

    struct vector vector;

    vector.capacity = 0;
    vector.size = 0;
    vector.item_size = item_size;
    vector.data = NULL;

    return vector;
}

void _vector_init(struct vector *vector)
{
    vector->data = malloc(16 * vector->item_size);
    if (!vector->data)
    {
        return;
    }

    vector->capacity = 16;
    vector->size = 0;
}

void vector_clear(struct vector *vector)
{
    if (vector->data)
        free(vector->data);

    vector->capacity = 0;
    vector->size = 0;
    vector->data = NULL;
}

int vector_size(struct vector *vector)
{
    return vector->size;
}

void *vector_at(struct vector *vector, int idx)
{
    if (idx >= vector->size || idx < 0)
    {
        return NULL;
    }

    return (vector->data + idx * (vector->item_size));
}

void *vector_front(struct vector *vector)
{
    return vector_at(vector, 0);
}

void *vector_back(struct vector *vector)
{
    return vector_at(vector, vector->size - 1);
}

int vector_insert(struct vector *vector, const void *item, int pos)
{
    if (pos > vector->size || pos < 0)
    {
        return -1;
    }

    if (!vector->data)
    {
        _vector_init(vector);
        if (!vector->data)
        {
            return -1;
        }
    }

    if (vector->size == vector->capacity)
    {
        char *new_data = malloc(2 * vector->capacity * vector->item_size);
        if (!new_data)
        {
            return -1;
        }

        memcpy(new_data, vector->data, vector->capacity * vector->item_size);
        free(vector->data);
        vector->data = new_data;
        vector->capacity = 2 * vector->capacity;
    }

    for (int i = vector->size - 1; i >= pos; --i)
    {
        memcpy(vector->data + (i + 1) * vector->item_size,
               vector->data + i * vector->item_size,
               vector->item_size);
    }

    memcpy(vector->data + pos * vector->item_size, item, vector->item_size);
    vector->size += 1;

    return 0;
}

void vector_push_back(struct vector *vector, const void *item)
{
    vector_insert(vector, item, vector->size);
}

void vector_erase(struct vector *vector, int pos)
{
    if (pos >= vector->size || pos < 0)
    {
        return;
    }

    if (pos < vector->size - 1)
    {
        for (int i = pos; i < vector->size; ++i)
        {
            memcpy(vector->data + i * vector->item_size,
                   vector->data + (i + 1) * vector->item_size,
                   vector->item_size);
        }
    }

    vector->size -= 1;
}

void vector_pop_back(struct vector *vector)
{
    vector_erase(vector, vector->size - 1);
}

void vector_for_each(struct vector *vector, vector_for_each_t for_each)
{
    for (int i = 0; i < vector->size; ++i)
    {
        for_each(vector->data + i * vector->item_size);
    }
}
