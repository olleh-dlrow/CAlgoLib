#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include "common.h"

typedef struct linked_list_node
{
    data_type *data;
    struct linked_list_node *next;
    struct linked_list_node *last;
} linked_list_node;

linked_list_node *init_linked_list_node(data_type *data,
                                        size_t data_size,
                                        linked_list_node *next,
                                        linked_list_node *last);

void destory_linked_list_node(linked_list_node **node_ptr);

typedef struct linked_list
{
    linked_list_node *head;
    linked_list_node *tail;
    size_t length;
    size_t data_size;
} linked_list;

linked_list *init_linked_list(size_t data_size);

int linked_list_is_empty(linked_list *ls);

linked_list_node *linked_list_next(linked_list *ls, linked_list_node *node);

linked_list_node *linked_list_last(linked_list *ls, linked_list_node *node);

linked_list_node *linked_list_delete_node(linked_list *ls, linked_list_node *node);

void linked_list_insert_node(linked_list *ls, linked_list_node *node, data_type *data);

void linked_list_set_node_data(linked_list *ls, linked_list_node *node, data_type *data);

linked_list_node *linked_list_get_head(linked_list *ls);

linked_list_node *linked_list_get_tail(linked_list *ls);

data_type *linked_list_get_node_data(linked_list *ls, linked_list_node *node);

void linked_list_insert(linked_list *ls, data_type *data, size_t index);

void linked_list_push_back(linked_list *ls, data_type *data);

void linked_list_delete(linked_list *ls, size_t index);

void linked_list_pop_back(linked_list *ls);

data_type *linked_list_get_data(linked_list *ls, size_t index);

void linked_list_set_data(linked_list *ls, data_type *data, size_t index);

size_t linked_list_get_length(linked_list *ls);

void destory_linked_list(linked_list **ls_ptr);

#endif
