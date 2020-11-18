#include "array_list.h"

array_list *init_array_list(size_t data_size)
{
    array_list *arr = (array_list *)malloc(sizeof(array_list));
    arr->capacity = MIN_CAPACITY;
    arr->array = (array_list_node *)calloc(arr->capacity, sizeof(array_list_node));
    arr->length = 0;
    arr->data_size = data_size;
    return arr;
}

int array_list_is_empty(array_list *arr)
{
    return arr->length == 0;
}

size_t array_list_get_length(array_list *arr)
{
    return arr->length;
}

void array_list_push_back(array_list *arr, data_type *data)
{
    size_t data_size = arr->data_size;
    if (arr->capacity <= arr->length)
    {
        expand_capacity((void **)&arr->array, &arr->capacity, sizeof(array_list_node));
    }
    array_list_node *node = &arr->array[arr->length];
    node->data = (data_type *)malloc(data_size);
    shift_data(data, node->data, data_size);
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

data_type *array_list_get_data(array_list *arr, size_t index)
{
    if (index >= arr->length)
    {
        printf("array_list get data error: index >= length!\n");
        exit(1);
    }
    array_list_node *node = &arr->array[index];
    return node->data;
}

void array_list_set_data(array_list *arr, data_type *data, size_t index)
{
    if (index >= arr->length)
    {
        printf("array_list set data error: index >= length!\n");
        exit(1);
    }
    shift_data(data, arr->array[index].data, arr->data_size);
    return;
}

void array_list_insert(array_list *arr, data_type *data, size_t index)
{
    if (index > arr->length)
    {
        printf("array_list insert error: index > length!\n");
        exit(1);
    }

    size_t data_size = arr->data_size;
    if (arr->capacity <= arr->length)
    {
        expand_capacity((void **)&arr->array, &arr->capacity, sizeof(array_list_node));
    }
    if (index == arr->length)
    {
        array_list_push_back(arr, data);
        return;
    }
    size_t i = arr->length - 1;
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
    shift_data(data, node->data, data_size);
    arr->length++;
    return;
}

void array_list_delete(array_list *arr, size_t index)
{
    if (index >= arr->length)
    {
        printf("array_list delete error: index >= length!\n");
        exit(1);
    }
    size_t i = index + 1;
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
