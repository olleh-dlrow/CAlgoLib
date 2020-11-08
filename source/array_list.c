#include <stdio.h>
#include <stdlib.h>

#include "array_list.h"

array_list *init_array_list()
{
    array_list *arr = (array_list *)malloc(sizeof(array_list));
    arr->capacity = 16;
    arr->array = (array_list_node *)calloc(arr->capacity, sizeof(array_list_node));
    arr->length = 0;
}

void array_list_add_capacity(array_list *arr)
{
    arr->capacity <<= 1;
    array_list_node *tmp =
        (array_list_node *)calloc(arr->capacity, sizeof(array_list_node));
    for (int i = 0; i < arr->length; i++)
    {
        tmp[i] = arr->array[i];
    }
    free(arr->array);
    arr->array = tmp;
    tmp = NULL;
    return;
}

int array_list_is_empty(array_list *arr)
{
    return arr->length == 0;
}

int array_list_get_length(array_list *arr)
{
    return arr->length;
}

void array_list_push_back(array_list *arr, data_type *data, size_t data_size)
{
    if (arr->capacity <= arr->length)
    {
        array_list_add_capacity(arr);
    }
    array_list_node *node = &arr->array[arr->length];
    node->data = (data_type *)malloc(data_size);
    char *bytes = (char *)data;
    for (size_t i = 0; i < data_size; i++)
    {
        *(char *)(node->data + i) = bytes[i];
    }
    arr->length++;
    return;
}

void array_list_pop_back(array_list *arr)
{
    if (array_list_is_empty(arr))
    {
        printf("array_list pop_back error: array_list is empty!\n");
        exit(1);
    }
    array_list_node *node = &arr->array[arr->length - 1];
    node->data = NULL;
    arr->length--;
    return;
}

data_type *array_list_get_data(array_list *arr, int index)
{
    if (index < 0)
    {
        printf("array_list get data error: index < 0!\n");
        exit(1);
    }
    if (index >= arr->length)
    {
        printf("array_list get data error: index >= length!\n");
        exit(1);
    }
    array_list_node *node = &arr->array[index];
    return node->data;
}

void array_list_insert(array_list *arr, data_type *data, size_t data_size, int index)
{
    if (index < 0)
    {
        printf("array_list insert error: index < 0!\n");
        exit(1);
    }
    if (index > arr->length)
    {
        printf("array_list insert error: index > length!\n");
        exit(1);
    }
    if (arr->capacity <= arr->length)
    {
        array_list_add_capacity(arr);
    }
    if (index == arr->length)
    {
        array_list_push_back(arr, data, data_size);
        return;
    }
    int i = arr->length - 1;
    array_list_node *p = &arr->array[i];
    array_list_node *post = &arr->array[i + 1];
    while (i >= index)
    {
        post->data = p->data;
        i--;
        p = &arr->array[i];
        post = &arr->array[i + 1];
    }
    array_list_node *node = &arr->array[index];
    //new data
    node->data = (data_type *)malloc(data_size);
    char *bytes = (char *)data;
    for (size_t i = 0; i < data_size; i++)
    {
        *(char *)(node->data + i) = bytes[i];
    }
    arr->length++;
    return;
}

void array_list_delete(array_list *arr, int index)
{
    if (index < 0)
    {
        printf("array_list delete error: index < 0!\n");
        exit(1);
    }
    if (index >= arr->length)
    {
        printf("array_list delete error: index >= length!\n");
        exit(1);
    }
    int i = index + 1;
    array_list_node *pre = &arr->array[i - 1];
    array_list_node *post = &arr->array[i];
    free(pre->data);
    while (i <= arr->length - 1)
    {
        pre->data = post->data;
        i++;
        pre = &arr->array[i - 1];
        post = &arr->array[i];
    }
    pre->data = NULL;
    arr->length--;
    return;
}

void destory_array_list(array_list **arr_ptr)
{
    array_list *arr = *arr_ptr;
    for (size_t i = 0; i < arr->length; i++)
    {
        array_list_node *node = &arr->array[i];
        free(node->data);
    }
    free(arr->array);
    free(arr);
    *arr_ptr = NULL;
    return;
}
