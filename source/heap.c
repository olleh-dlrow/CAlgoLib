#include "heap.h"

//a < b, 小根堆
heap *init_heap(size_t data_size, int (*cmp_func)(void *a, void *b))
{
    heap *hp = (heap *)malloc(sizeof(heap));
    hp->length = 0;
    hp->capacity = MIN_CAPACITY;
    hp->data_size = data_size;
    hp->cmp_func = cmp_func;
    hp->array = (heap_node *)calloc(hp->capacity, sizeof(heap_node));
    return hp;
}

int heap_is_empty(heap *hp)
{
    return hp->length == 0;
}

void heap_add(heap *hp, data_type *data)
{
    if (hp->capacity <= hp->length)
    {
        expand_capacity((void **)&hp->array, &hp->capacity, sizeof(heap_node));
    }
    size_t data_size = hp->data_size;
    size_t i = hp->length;
    while (i > 0)
    {
        size_t parent_i = (i - 1) / 2;
        if (hp->cmp_func(hp->array[parent_i].data, data) <= 0)
        {
            break;
        }
        hp->array[i].data = hp->array[parent_i].data;
        i = parent_i;
    }
    hp->array[i].data = (data_type *)malloc(data_size);
    shift_data(data, hp->array[i].data, data_size);
    hp->length++;
    return;
}

data_type *heap_get_peek(heap *hp)
{
    if (heap_is_empty(hp))
    {
        printf("heap get peek error: heap is empty!\n");
        exit(1);
    }
    return hp->array[0].data;
}

size_t heap_get_length(heap *hp)
{
    return hp->length;
}

void heap_pop(heap *hp)
{
    if (heap_is_empty(hp))
    {
        printf("heap pop error: heap is empty!\n");
        exit(1);
    }
    size_t size = hp->data_size;
    free(hp->array[0].data);
    hp->array[0].data = NULL;
    data_type *x = hp->array[hp->length - 1].data;
    // shift_data(hp->array[hp->length - 1].data, x, size);
    size_t i = 0;
    while (i <= (hp->length - 2) / 2)
    {
        size_t left = i * 2 + 1;
        size_t right = i * 2 + 2;
        size_t min = left;
        if (right <= hp->length - 1 && hp->cmp_func(hp->array[right].data, hp->array[min].data) < 0)
        {
            min = right;
        }
        if (hp->cmp_func(hp->array[min].data, x) >= 0)
        {
            break;
        }
        hp->array[i].data = hp->array[min].data;
        i = min;
    }
    hp->array[i].data = x;
    hp->length--;
    return;
}

void destory_heap(heap **hp_ptr)
{
    heap *hp = *hp_ptr;
    for (size_t i = 0; i < hp->length; i++)
    {
        free(hp->array[i].data);
    }
    free(hp->array);
    free(hp);
    *hp_ptr = NULL;
    return;
}