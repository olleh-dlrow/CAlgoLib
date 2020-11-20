#include "linked_list.h"

/**
 * linked_list_node
*/
linked_list_node *init_linked_list_node(data_type *data,
                                        size_t data_size,
                                        linked_list_node *next,
                                        linked_list_node *last)
{
    linked_list_node *node = (linked_list_node *)malloc(sizeof(linked_list_node));
    //node->data = data
    node->data = (data_type *)malloc(data_size);
    shift_data(data, node->data, data_size);
    //
    node->next = next;
    node->last = last;
    return node;
}

void destory_linked_list_node(linked_list_node **node_ptr)
{
    linked_list_node *node = *node_ptr;
    free(node->data);
    free(node);
    *node_ptr = NULL;
    return;
}

/**
 * linked_list
*/
linked_list *init_linked_list(size_t data_size)
{
    linked_list *ls = (linked_list *)malloc(sizeof(linked_list));
    ls->head = init_linked_list_node(NULL, 0, NULL, NULL);
    ls->tail = init_linked_list_node(NULL, 0, ls->head, ls->head);
    ls->head->next = ls->tail;
    ls->head->last = ls->tail;
    ls->length = 0;
    ls->data_size = data_size;
    return ls;
}

int linked_list_is_empty(linked_list *ls)
{
    return ls->length == 0;
}

void linked_list_insert(linked_list *ls, data_type *data, size_t index)
{
    if (index > ls->length)
    {
        printf("linked_list insert error: index > length!\n");
        exit(1);
    }
    size_t data_size = ls->data_size;
    linked_list_node *p = ls->head; //-1
    if (index != 0)
    {
        p = ls->head->next;
        size_t i = 0;
        while (i < index - 1)
        {
            p = p->next;
            i++;
        }
    }
    //p pointers to the pre node of inserting node
    linked_list_node *post = p->next;
    //new node
    linked_list_node *node = init_linked_list_node(data, data_size, post, p);
    p->next = node;
    post->last = node;
    //length++
    ls->length++;
    return;
}

void linked_list_push_back(linked_list *ls, data_type *data)
{
    linked_list_insert(ls, data, ls->length);
}

void linked_list_delete(linked_list *ls, size_t index)
{
    if (index >= ls->length)
    {
        printf("linked_list delete error: index >= length!\n");
        exit(1);
    }
    linked_list_node *p = ls->head; //-1
    if (index != 0)
    {
        p = ls->head->next;
        size_t i = 0;
        while (i < index - 1)
        {
            p = p->next;
            i++;
        }
    }
    linked_list_node *node = p->next;
    linked_list_node *post = node->next;
    p->next = post;
    post->last = p;
    destory_linked_list_node(&node);
    ls->length--;
    return;
}

void linked_list_pop_back(linked_list *ls)
{
    linked_list_delete(ls, ls->length - 1);
}

data_type *linked_list_get_data(linked_list *ls, size_t index)
{
    if (index >= ls->length)
    {
        printf("linked_list get data error: index >= length!\n");
        exit(1);
    }
    linked_list_node *p = ls->head->next;
    size_t i = 0;
    while (i < index)
    {
        p = p->next;
        i++;
    }
    return p->data;
}

void linked_list_set_data(linked_list *ls, data_type *data, size_t index)
{
    if (index > ls->length)
    {
        printf("linked_list set data error: index > length!\n");
        exit(1);
    }
    linked_list_node *p = ls->head->next;
    size_t i = 0;
    while (i < index)
    {
        p = p->next;
        ++i;
    }
    shift_data(data, p->data, ls->data_size);
    return;
}

size_t linked_list_get_length(linked_list *ls)
{
    return ls->length;
}

void destory_linked_list(linked_list **ls_ptr)
{
    linked_list *ls = *ls_ptr;
    while (!linked_list_is_empty(ls))
    {
        linked_list_delete(ls, 0);
    }
    destory_linked_list_node(&ls->head);
    destory_linked_list_node(&ls->tail);
    free(*ls_ptr);
    *ls_ptr = NULL;
    return;
}
