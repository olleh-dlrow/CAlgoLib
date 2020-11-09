#ifndef _HEAP_H
#define _HEAP_H

#include "common.h"

typedef struct heap_node
{
    data_type *data;
} heap_node;

typedef struct heap
{
    heap_node *array;
    size_t length;
    size_t capacity;
    size_t data_size;
    int (*cmp_func)(void *a, void *b);
} heap;

heap *init_heap(size_t data_size, int (*cmp_func)(void *a, void *b));

int heap_is_empty(heap *hp);

void heap_add(heap *hp, data_type *data);

data_type *heap_get_peek(heap *hp);

size_t heap_get_length(heap *hp);

void heap_pop(heap *hp);

void destory_heap(heap **hp_ptr);

#endif