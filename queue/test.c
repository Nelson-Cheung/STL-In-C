#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "queue.h"

#define TEST_EXAMPLE 1000
#define RANDOM_RETRIEVE_TEST 10
#define RANDOM_DELETE_TEST 10

int counter = 0;
void for_each(void *context, const void *item)
{
    printf("%d: %d\n", counter++, *((int *)item));
}

int main()
{
    srand((unsigned)time(NULL));

    int items[TEST_EXAMPLE];
    for (int k = 0; k < TEST_EXAMPLE; ++k)
        items[k] = k;

    for (int k = 0; k < TEST_EXAMPLE; ++k)
    {
        int i = rand() % TEST_EXAMPLE;
        int j = rand() % TEST_EXAMPLE;
        if (i != j)
        {
            int tmp = items[i];
            items[i] = items[j];
            items[j] = tmp;
        }
    }

    struct queue int_queue = queue_init(sizeof(int));

    {
        printf("Begin [push] test...\n");

        printf("Adding %d examples to queue\n", TEST_EXAMPLE);
        for (int i = 0; i < TEST_EXAMPLE; ++i)
        {
            queue_push(&int_queue, &items[i]);
        }

        if (queue_size(&int_queue) != TEST_EXAMPLE)
        {
            printf("failed push test...\n");
            return 0;
        }

        printf("pass [push] test...\n");
    }

    {
        printf("Begin [for_each] test...\n");

        queue_for_each(&int_queue, for_each, NULL);
    }

    {
        printf("Begin [pop] test...\n");

        for (int i = 0; i < TEST_EXAMPLE; ++i)
        {
            int item;
            queue_pop(&int_queue, &item);
            if (item != items[i])
            {
                printf("failed pop test...\n");
                return 0;
            }
        }

        if (queue_size(&int_queue) != 0)
        {
            printf("failed pop test...\n");
            return 0;
        }

        printf("pass [pop] test...\n");
    }

    queue_clear(&int_queue);
}