#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "vector.h"

#define TEST_EXAMPLE 1000
#define RANDOM_RETRIEVE_TEST 10
#define RANDOM_DELETE_TEST 10

int counter = 0;
void for_each(const void *item)
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

    struct vector int_vector = vector_init(sizeof(int));

    {
        printf("Begin [push_back] test...\n");

        printf("Adding %d examples to map\n", TEST_EXAMPLE);
        for (int i = 0; i < TEST_EXAMPLE; ++i)
        {
            vector_push_back(&int_vector, &items[i]);
        }

        if (vector_size(&int_vector) != TEST_EXAMPLE)
        {
            printf("failed push_back test...\n");
            return 0;
        }

        printf("pass [push_back] test...\n");
    }

    {
        printf("Begin [at] test...\n");
        for (int i = 0; i < vector_size(&int_vector); ++i)
        {
            int *ptr = (int *)vector_at(&int_vector, i);
            if (*ptr != items[i])
            {
                printf("failed [at] test at index %d\n", i);
                return 0;
            }
        }

        printf("pass [at] test\n");
    }

    {
        printf("Begin [at] test...\n");
        for (int i = 0; i < vector_size(&int_vector); ++i)
        {
            int *ptr = (int *)vector_at(&int_vector, i);
            if (*ptr != items[i])
            {
                printf("failed [at] test at index %d\n", i);
                return 0;
            }
        }

        printf("pass [at] test\n");
    }

    {
        printf("Begin [front] test\n");
        int *ptr = (int *)vector_front(&int_vector);
        if (*ptr != items[0])
        {
            printf("failed [front] test\n");
            return 0;
        }
        printf("pass [front] test\n");
    }

    {
        printf("Begin [back] test\n");
        int *ptr = (int *)vector_back(&int_vector);
        if (*ptr != items[TEST_EXAMPLE - 1])
        {
            printf("failed [back] test\n");
            return 0;
        }
        printf("pass [back] test\n");
    }

    {
        int pos1 = 0;
        int pos2 = TEST_EXAMPLE / 128;
        int pos3 = TEST_EXAMPLE / 64;
        int pos4 = TEST_EXAMPLE / 32;
        int pos5 = TEST_EXAMPLE / 16;
        int pos6 = TEST_EXAMPLE / 8;
        int item = -1;

        printf("Begin [insert] test\n");

        vector_insert(&int_vector, &item, pos1);
        vector_insert(&int_vector, &item, pos2);
        vector_insert(&int_vector, &item, pos3);
        vector_insert(&int_vector, &item, pos4);
        vector_insert(&int_vector, &item, pos5);
        vector_insert(&int_vector, &item, pos6);

        int *ptr = NULL;

        ptr = vector_at(&int_vector, pos1);
        if (*ptr != -1)
        {
            printf("failed [insert] test\n");
            return 0;
        }

        ptr = vector_at(&int_vector, pos2);
        if (*ptr != -1)
        {
            printf("failed [insert] test\n");
            return 0;
        }

        ptr = vector_at(&int_vector, pos3);
        if (*ptr != -1)
        {
            printf("failed [insert] test\n");
            return 0;
        }

        ptr = vector_at(&int_vector, pos4);
        if (*ptr != -1)
        {
            printf("failed [insert] test\n");
            return 0;
        }

        ptr = vector_at(&int_vector, pos5);
        if (*ptr != -1)
        {
            printf("failed [insert] test\n");
            return 0;
        }

        ptr = vector_at(&int_vector, pos6);
        if (*ptr != -1)
        {
            printf("failed [insert] test\n");
            return 0;
        }

        printf("pass [insert] test\n");

        printf("Begin [erase] test\n");

        vector_erase(&int_vector, pos6);
        vector_erase(&int_vector, pos5);
        vector_erase(&int_vector, pos4);
        vector_erase(&int_vector, pos3);
        vector_erase(&int_vector, pos2);
        vector_erase(&int_vector, pos1);

        ptr = vector_at(&int_vector, pos1);
        if (*ptr != items[pos1])
        {
            printf("failed [insert] test\n");
            return 0;
        }

        ptr = vector_at(&int_vector, pos2);
        if (*ptr != items[pos2])
        {
            printf("failed [insert] test\n");
            return 0;
        }

        ptr = vector_at(&int_vector, pos3);
        if (*ptr != items[pos3])
        {
            printf("failed [insert] test\n");
            return 0;
        }

        ptr = vector_at(&int_vector, pos4);
        if (*ptr != items[pos4])
        {
            printf("failed [insert] test\n");
            return 0;
        }

        ptr = vector_at(&int_vector, pos5);
        if (*ptr != items[pos5])
        {
            printf("failed [insert] test\n");
            return 0;
        }

        ptr = vector_at(&int_vector, pos6);
        if (*ptr != items[pos6])
        {
            printf("failed [insert] test\n");
            return 0;
        }

        printf("pass [erase] test\n");
    }

    {
        printf("Begin [for_each] test...\n");

        vector_for_each(&int_vector, for_each);
    }

    {
        printf("Begin [pop_back] test...\n");

        for (int i = 0; i < TEST_EXAMPLE; ++i)
        {
            vector_pop_back(&int_vector);
        }

        if (vector_size(&int_vector) != 0)
        {
            printf("failed pop_back test...\n");
            return 0;
        }

        printf("pass [pop_back] test...\n");
    }

    vector_clear(&int_vector);
}