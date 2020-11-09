#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#define data_type void

typedef struct queue_node
{
    data_type *data;
    size_t data_size;
    struct queue_node *last;
} queue_node;

queue_node *init_queue_node(data_type *data,
                            size_t data_size,
                            queue_node *last);

void destory_queue_node(queue_node **node_ptr);

//node1(p_head) <- node2 <- node3 <- tail
typedef struct queue
{
    queue_node *p_head;
    queue_node *tail;
    int length;
} queue;

queue *init_queue();

int queue_is_empty(queue *qu);

void queue_push_front(queue *qu, data_type *data, size_t data_size);

void queue_pop_back(queue *qu);

int queue_get_length(queue *qu);

data_type *queue_get_back(queue *qu);

void destory_queue(queue **qu_ptr);

#endif