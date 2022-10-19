# Map

## 简介
基于红黑树的map实现，功能如下。
+ 支持任意固定长度的类型，但长度需要在`map_init`中给出。
+ 当map不再使用后，使用`map_clear`进行空间释放，否则会发生内存泄漏。

## 快速开始
具体用法可以参照[example.c](example.c)
```shell
make
./example.out
```

## 接口
```c
// 遍历时在每个元素上进行的操作
typedef void (*map_for_each_t)(const void *key, const void *val);

// 创建map
struct map map_init(int key_size, int value_size);
// 释放map
void map_clear(struct map *m);
// 获取map元素
void *map_get(struct map *m, const void *key);
// 插入或修改map元素
int map_put(struct map *m, const void *key, const void *val);
// 删除map元素
int map_del(struct map *m, const void *key);
// 遍历map
void map_for_each(struct map *m, map_for_each_t for_each);
```

## 测试
### 随机测试
```shell
./map_test.out
```
### 内存泄漏测试
```shell
valgrind --tool=memcheck --leak-check=full ./map_test.out
```