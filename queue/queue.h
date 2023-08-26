#ifndef QUEUE_H
#define QUEUE_H

struct queue_t
{
    void *val;
    struct queue_t *prev;
    struct queue_t *next;
};

struct queue
{
    struct queue_t head;
    struct queue_t tail;
    unsigned int size;
    unsigned int val_size;
};

typedef void (*queue_for_each_t)(void *context, const void *item);

struct queue queue_init(unsigned int val_size);
void queue_clear(struct queue *q);
void queue_push(struct queue *q, const void *val);
unsigned int queue_pop(struct queue *q, void *val);
unsigned int queue_size(struct queue *q);
void queue_for_each(struct queue*q, queue_for_each_t for_each, void *context);
#endif