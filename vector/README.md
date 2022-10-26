# Map

## 简介
基于动态数组的vector实现
+ 支持任意固定长度的类型，但长度需要在`vector_init`中给出。
+ 当vector不再使用后，使用`vector_clear`进行空间释放，否则会发生内存泄漏。

## 快速开始
具体用法可以参照[example.c](example.c)
```shell
make
./example.out
```

## 接口
```c

typedef void (*vector_for_each_t)(const void *item);

// create a vector
struct vector vector_init(int item_size);
// free the memory of vector
void vector_clear(struct vector *vector);
// get size of vector
int vector_size(struct vector *vector);
// get item at the given position
void *vector_at(struct vector *vector, int idx);
// get the first item
void *vector_front(struct vector *vector);
// get the last item
void *vector_back(struct vector *vector);
// insert item at the given position
int vector_insert(struct vector *vector, const void *item, int pos);
// insert item behind the last item
void vector_push_back(struct vector *vector, const void *item);
// pop the last item
void vector_pop_back(struct vector *vector);
// erase item at the given position
void vector_erase(struct vector *vector, int pos);
// traverse vector
void vector_for_each(struct vector *vector, vector_for_each_t for_each);
```

## 测试
### 随机测试
```shell
./vector_test.out
```
### 内存泄漏测试
```shell
valgrind --tool=memcheck --leak-check=full ./vector_test.out
```