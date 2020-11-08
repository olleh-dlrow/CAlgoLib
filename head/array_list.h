#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H

#define data_type void

typedef struct array_list_node
{
    data_type *data;
    size_t data_size;
} array_list_node;

typedef struct array_list
{
    array_list_node *array;
    int capacity;
    int length;
} array_list;

array_list *init_array_list();

void array_list_add_capacity(array_list *arr);

int array_list_is_empty(array_list *arr);

int array_list_get_length(array_list *arr);

void array_list_push_back(array_list *arr, data_type *data, size_t data_size);

void array_list_pop_back(array_list *arr);

data_type *array_list_get_data(array_list *arr, int index);

void array_list_insert(array_list *arr, data_type *data, size_t data_size, int index);

void array_list_delete(array_list *arr, int index);

void destory_array_list(array_list **arr_ptr);

#endif