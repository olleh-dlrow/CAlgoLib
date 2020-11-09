#include "stack.h"

/**
 * stack_node
*/

stack_node *init_stack_node(data_type *data, size_t data_size, stack_node *last)
{
    stack_node *sn = (stack_node *)malloc(sizeof(stack_node));
    sn->data = (data_type *)malloc(data_size);
    shift_data(data, sn->data, data_size);
    sn->last = last;
    return sn;
}

void destory_stack_node(stack_node **node_ptr)
{
    stack_node *node = *node_ptr;
    free(node->data);
    free(node);
    *node_ptr = NULL;
}

/**
 * stack
*/

stack *init_stack(size_t data_size)
{
    stack *st = (stack *)malloc(sizeof(stack));
    st->head = init_stack_node(NULL, 0, NULL);
    st->top = st->head;
    st->length = 0;
    st->data_size = data_size;
    return st;
}

int stack_is_empty(stack *st)
{
    return st->length == 0;
}

void stack_push(stack *st, data_type *data)
{
    stack_node *node = init_stack_node(data, st->data_size, st->top);
    st->top = node;
    st->length++;
    return;
}

void stack_pop(stack *st)
{
    if (stack_is_empty(st))
    {
        printf("stack pop error: stack is empty!\n");
        exit(1);
    }
    stack_node *tmp = st->top;
    st->top = st->top->last;
    destory_stack_node(&tmp);
    st->length--;
    return;
}

data_type *stack_get_peek(stack *st)
{
    if (stack_is_empty(st))
    {
        printf("stack get peek error: stack is empty!\n");
        exit(1);
    }
    return st->top->data;
}

size_t stack_get_length(stack *st)
{
    return st->length;
}

void destory_stack(stack **st_ptr)
{
    stack *st = *st_ptr;
    while (!stack_is_empty(st))
    {
        stack_pop(st);
    }
    destory_stack_node(&st->head);
    free(st);
    *st_ptr = NULL;
    return;
}
