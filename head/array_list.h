#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H

#include "common.h"

typedef struct array_list_node
{
    data_type *data;
} array_list_node;

typedef struct array_list
{
    array_list_node *array;
    size_t capacity;
    size_t length;
    size_t data_size;
} array_list;

array_list *init_array_list(size_t data_size);

int array_list_is_empty(array_list *arr);

size_t array_list_get_length(array_list *arr);

void array_list_push_back(array_list *arr, data_type *data);

void array_list_pop_back(array_list *arr);

data_type *array_list_get_data(array_list *arr, size_t index);

void array_list_insert(array_list *arr, data_type *data, size_t index);

void array_list_delete(array_list *arr, size_t index);

void destory_array_list(array_list **arr_ptr);

#endif