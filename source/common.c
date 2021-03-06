#include "common.h"

void shift_data(data_type *src_data, data_type *dst_data, size_t data_size)
{
    size_t tail_size = data_size;
    size_t *dst_ptr = dst_data;
    size_t *src_ptr = src_data;
    while (tail_size / 8 != 0)
    {
        *dst_ptr = *src_ptr;
        dst_ptr++;
        src_ptr++;
        tail_size -= 8;
    }
    char *_dst_ptr = (char *)dst_ptr;
    char *_src_ptr = (char *)src_ptr;
    while (tail_size != 0)
    {
        *_dst_ptr = *_src_ptr;
        _dst_ptr++;
        _src_ptr++;
        tail_size--;
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

char *read_string(size_t len)
{
    char *str = (char *)calloc(len + 1, sizeof(char));
    char ch = '\0';
    size_t i = 0;
    while ((ch = getchar()) != '\n' && i < len)
    {
        str[i] = ch;
        ++i;
    }
    str[len] = '\0';
    return str;
}
