#include "common.h"

void shift_data(data_type *src_data, data_type *dst_data, size_t data_size)
{
    char *bytes = src_data;
    for (size_t i = 0; i < data_size; i++)
    {
        *(char *)(dst_data + i) = bytes[i];
    }
    return;
}

void expand_capacity(void **arr_ptr, size_t *src_capacity, size_t elem_size)
{
    if (*src_capacity == MAX_CAPACITY)
    {
        printf("add capacity error: capacity over INT_MAX!\n");
        exit(1);
    }
    void *arr = *arr_ptr;
    size_t length = *src_capacity;
    *src_capacity = ((*src_capacity) << 1) | 0x1;
    void *tmp = (void *)calloc(*src_capacity, elem_size);
    char *p = tmp;
    char *q = arr;
    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = 0; j < elem_size; j++)
        {
            *p = *q;
            p++;
            q++;
        }
    }
    free(arr);
    *arr_ptr = tmp;
    tmp = NULL;
    return;
}
