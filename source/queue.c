#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

/**
 * queue_node
*/

queue_node *init_queue_node(data_type *data,
                            size_t data_size,
                            queue_node *last)
{
    queue_node *node = (queue_node *)malloc(sizeof(queue_node));
    //node->data = data
    node->data = (data_type *)malloc(data_size);
    char *bytes = (char *)data;
    for (size_t i = 0; i < data_size; i++)
    {
        *(char *)(node->data + i) = bytes[i];
    }
    //
    node->last = last;
    return node;
}

void destory_queue_node(queue_node **node_ptr)
{
    queue_node *node = *node_ptr;
    free(node->data);
    free(node);
    *node_ptr = NULL;
    return;
}

/**
 * queue
*/

queue *init_queue()
{
    queue *qu = (queue *)malloc(sizeof(queue));
    qu->tail = init_queue_node(NULL, 0, NULL);
    qu->p_head = qu->tail;
    qu->length = 0;
    return qu;
}

int queue_is_empty(queue *qu)
{
    return qu->length == 0;
}

void queue_push_front(queue *qu, data_type *data, size_t data_size)
{
    queue_node *node = init_queue_node(data, data_size, NULL);
    qu->p_head->last = node;
    qu->p_head = node;
    qu->length++;
    return;
}

void queue_pop_back(queue *qu)
{
    if (queue_is_empty(qu))
    {
        printf("queue pop back error: queue is empty!\n");
        exit(1);
    }
    queue_node *node = qu->tail->last;
    qu->tail->last = node->last;
    destory_queue_node(&node);
    qu->length--;
    if (queue_get_length(qu) == 0)
    {
        qu->p_head = qu->tail;
    }
    return;
}

int queue_get_length(queue *qu)
{
    return qu->length;
}

data_type *queue_get_back(queue *qu)
{
    return qu->tail->last->data;
}

void destory_queue(queue **qu_ptr)
{
    queue *qu = *qu_ptr;
    while (!queue_is_empty(qu))
    {
        queue_pop_back(qu);
    }
    destory_queue_node(&qu->tail);
    free(qu);
    *qu_ptr = NULL;
    return;
}