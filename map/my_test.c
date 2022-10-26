#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"

struct filename_t
{
    char data[128];
};

void add_to_map(struct map *m, int pid, int fd, const char *filename)
{
    struct map *fds = map_get(m, &pid);
    if (!fds)
    {
        struct map item = map_init(sizeof(int), sizeof(struct filename_t));
        map_put(m, &pid, &item);
        fds = map_get(m, &pid);
    }

    struct filename_t name;
    strcpy(name.data, filename);

    map_put(fds, &fd, &name);
}

int get_from_map(struct map *m, int pid, int fd, char *buf)
{
    struct map *fds = map_get(m, &pid);
    if (!fds)
    {
        return -1;
    }

    struct filename_t *name_ptr = map_get(fds, &fd);
    if (!name_ptr)
    {
        return -1;
    }

    strcpy(buf, name_ptr->data);
    return 0;
}

int main()
{
    struct map m = map_init(sizeof(int), sizeof(struct map));
    add_to_map(&m, 0, 0, "0000");
    add_to_map(&m, 0, 1, "1111");

    char buf[32];
    if (!get_from_map(&m, 0, 0, buf))
    {
        printf("%s\n", buf);
    }
    if (!get_from_map(&m, 0, 1, buf))
    {
        printf("%s\n", buf);
    }
}