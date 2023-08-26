#include "queue.h"
#include <stdlib.h>
#include <string.h>

struct queue queue_init(unsigned int val_size)
{
    struct queue q;
    q.head.next = &(q.tail);
    q.tail.prev = &(q.head);
    q.size = 0;
    q.val_size = val_size;
    return q;
}

void queue_clear(struct queue *q)
{
    while (queue_pop(q, NULL))
    {
    }
}

void queue_push(struct queue *q, const void *val)
{
    struct queue_t *item = malloc(sizeof(struct queue_t));
    q->tail.prev->next = item;
    item->prev = q->tail.prev;
    item->next = &(q->tail);
    item->val = malloc(q->val_size);
    memcpy(item->val, val, q->val_size);

    q->tail.prev = item;
    if (!q->size)
    {
        q->head.next = item;
    }

    q->size += 1;
}

unsigned int queue_pop(struct queue *q, void *val)
{
    if (!q->size)
        return 0;

    memcpy(val, q->head.next->val, q->val_size);
    struct queue_t *next = q->head.next;
    q->head.next = next->next;
    next->next->prev = &(q->head);
    free(next->val);
    free(next);
    q->size -= 1;
    return 1;
}

unsigned int queue_size(struct queue *q)
{
    return q->size;
}

void queue_for_each(struct queue *q, queue_for_each_t for_each, void *context)
{
    struct queue_t *current = q->head.next;
    while (current != (&(q->tail)))
    {
        for_each(context, current->val);
        current = current->next;
    }
}