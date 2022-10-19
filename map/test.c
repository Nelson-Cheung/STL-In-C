#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "map.h"

#define TEST_EXAMPLE 1000
#define RANDOM_RETRIEVE_TEST 10
#define RANDOM_DELETE_TEST 10

int counter = 0;
void for_each(const void *key, const void *val)
{
    printf("%d: [%d] -> [%d]\n", counter++, *((int *)key), *((int *)val));
}

int main()
{
    srand((unsigned)time(NULL));

    int keys[TEST_EXAMPLE];
    for (int k = 0; k < TEST_EXAMPLE; ++k)
        keys[k] = k;

    for (int k = 0; k < TEST_EXAMPLE; ++k)
    {
        int i = rand() % TEST_EXAMPLE;
        int j = rand() % TEST_EXAMPLE;
        if (i != j)
        {
            int tmp = keys[i];
            keys[i] = keys[j];
            keys[j] = tmp;
        }
    }

    int values[TEST_EXAMPLE];
    for (int k = 0; k < TEST_EXAMPLE; ++k)
        values[k] = k;

    for (int k = 0; k < TEST_EXAMPLE; ++k)
    {
        int i = rand() % TEST_EXAMPLE;
        int j = rand() % TEST_EXAMPLE;
        if (i != j)
        {
            int tmp = values[i];
            values[i] = values[j];
            values[j] = tmp;
        }
    }

    printf("Begin (int -> int) map test\n");
    printf("Adding %d examples to map\n", TEST_EXAMPLE);

    struct map int2int_map = map_init(sizeof(int), sizeof(int));
    for (int i = 0; i < TEST_EXAMPLE; ++i)
    {
        map_put(&int2int_map, &keys[i], &values[i]);
    }

    printf("Begin random retrieve test...\n");
    for (int k = 0; k < RANDOM_RETRIEVE_TEST; ++k)
    {
        int i = rand() % TEST_EXAMPLE;
        int *val_ptr = map_get(&int2int_map, &keys[i]);
        if (val_ptr && *val_ptr == values[i])
        {
            printf("pass retrieve test %d: key = %d, value = %d\n", k, keys[i], values[i]);
        }
        else
        {
            if (!val_ptr)
            {
                printf("fail retrieve test %d: key = %d not found\n", k, keys[i]);
            }
            else
            {
                printf("fail retrieve test %d: key = %d, map[key] = %d, real value = %d\n", k, keys[i], *val_ptr, values[i]);
            }
        }
    }

    printf("Begin random delete test...\n");
    for (int k = 0; k < RANDOM_DELETE_TEST; ++k)
    {
        int i = rand() % TEST_EXAMPLE;
        map_del(&int2int_map, &keys[i]);
        if (map_get(&int2int_map, &keys[i])) {
            printf("fail delete test %d: key = %d\n", k, keys[i]);
        } else {
            printf("pass delete test %d: key = %d\n", k, keys[i]);
        }
    }

    printf("Begin for each test...\n");
    counter = 0;
    map_for_each(&int2int_map, for_each);

    printf("Begin clear test...\n");
    map_clear(&int2int_map);
    counter = 0;
    map_for_each(&int2int_map, for_each);
    if (counter != 0) {
        printf("fail clear test\n");
    } else {
        printf("pass clear test\n");
    }
}