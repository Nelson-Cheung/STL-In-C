#include "vector.h"
#include <stdio.h>
#include <string.h>

struct item_t
{
    char name[128];
    int age;
    int weight;
    int height;
};

void for_each(const void *item)
{
    struct item_t *item_ptr = (struct item_t *)item;

    printf("name: %s, age: %d, height: %d, weight: %d\n", item_ptr->name, item_ptr->age, item_ptr->height, item_ptr->weight);
}

int main()
{
    struct vector v = vector_init(sizeof(struct item_t));
    struct item_t item;

    strcpy(item.name, "Nelson Cheung");
    item.age = 22;
    item.weight = 180;
    item.height = 180;
    vector_push_back(&v, &item);

    strcpy(item.name, "Junyu Zhang");
    item.age = 18;
    item.weight = 220;
    item.height = 175;
    vector_push_back(&v, &item);

    strcpy(item.name, "Kwanyu Cheung");
    item.age = 20;
    item.weight = 200;
    item.height = 178;
    vector_insert(&v, &item, 1);

    printf("Insert 3 items\n");
    vector_for_each(&v, for_each);

    printf("size of vector: %d\n", vector_size(&v));

    struct item_t *item_ptr = NULL;

    item_ptr = vector_at(&v, 1);
    printf("name: %s, age: %d, height: %d, weight: %d\n", item_ptr->name, item_ptr->age, item_ptr->height, item_ptr->weight);

    item_ptr = vector_front(&v);
    printf("name: %s, age: %d, height: %d, weight: %d\n", item_ptr->name, item_ptr->age, item_ptr->height, item_ptr->weight);

    item_ptr = vector_back(&v);
    printf("name: %s, age: %d, height: %d, weight: %d\n", item_ptr->name, item_ptr->age, item_ptr->height, item_ptr->weight);

    vector_erase(&v, 1);
    printf("Erase vector[1]\n");
    vector_for_each(&v, for_each);

    vector_pop_back(&v);
    printf("Pop back\n");
    vector_for_each(&v, for_each);

    vector_clear(&v);

}