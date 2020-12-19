#ifndef _MYUTIL_H
#define _MYUTIL_H

#include <stdio.h>
#include <stdlib.h>

// #define DBG

#ifdef DBG
#define log(fmt, args...) printf(fmt, ##args)
#else
#define log(fmt, args...)
#endif

#define MAX_CAPACITY (~(size_t)0)

#define MIN_CAPACITY ((size_t)0xf)

typedef void data_type;

typedef void key_type;

typedef void value_type;

void shift_data(data_type *src_data, data_type *dst_data, size_t data_size);

void expand_capacity(void **arr_ptr, size_t *src_capacity, size_t elem_size);

char *read_string(size_t len);




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

void array_list_set_data(array_list *arr, data_type *data, size_t index);

void array_list_insert(array_list *arr, data_type *data, size_t index);

void array_list_delete(array_list *arr, size_t index);

void destory_array_list(array_list **arr_ptr);




typedef struct heap_node
{
    data_type *data;
} heap_node;

typedef struct heap
{
    heap_node *array;
    size_t length;
    size_t capacity;
    size_t data_size;
    int (*cmp_func)(void *a, void *b);
} heap;

heap *init_heap(size_t data_size, int (*cmp_func)(void *a, void *b));

int heap_is_empty(heap *hp);

void heap_add(heap *hp, data_type *data);

data_type *heap_get_peek(heap *hp);

size_t heap_get_length(heap *hp);

void heap_pop(heap *hp);

void destory_heap(heap **hp_ptr);




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

void linked_list_insert(linked_list *ls, data_type *data, size_t index);

void linked_list_push_back(linked_list *ls, data_type *data);

void linked_list_delete(linked_list *ls, size_t index);

void linked_list_pop_back(linked_list *ls);

data_type *linked_list_get_data(linked_list *ls, size_t index);

void linked_list_set_data(linked_list *ls, data_type *data, size_t index);

size_t linked_list_get_length(linked_list *ls);

void destory_linked_list(linked_list **ls_ptr);




typedef struct my_string{
    size_t length;
    array_list *str;
}my_string;

my_string *init_my_string();

void my_string_read(my_string *s, FILE *stream);

size_t my_string_get_length(my_string *s);

char my_string_index_of(my_string *s, size_t index);

int my_string_is_empty(my_string *s);

int my_string_compare(my_string *s1, my_string *s2);

void my_string_replace(my_string *s, char ch, size_t index);

void my_string_insert(my_string *s, char ch, size_t index);

void my_string_push(my_string *s, char ch);

void my_string_delete(my_string *s, size_t index);

char *my_string_to_char_array(my_string *s);

void destory_my_string(my_string **s_ptr);




typedef struct queue_node
{
    data_type *data;
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
    size_t length;
    size_t data_size;
} queue;

queue *init_queue(size_t data_size);

int queue_is_empty(queue *qu);

void queue_push_front(queue *qu, data_type *data);

void queue_pop_back(queue *qu);

size_t queue_get_length(queue *qu);

data_type *queue_get_back(queue *qu);

void destory_queue(queue **qu_ptr);




typedef enum
{
    RBT_RED,
    RBT_BLACK
} rbt_color;

/*rbt means red black tree*/
typedef struct rbt_node
{
    data_type *data;
    rbt_color color;
    struct rbt_node *left;
    struct rbt_node *right;
    struct rbt_node *parent;
    int is_null_leaf;
} rbt_node;

rbt_node *init_black_node(data_type *data, size_t data_size);

rbt_node *init_red_node(data_type *data, size_t data_size, rbt_node *parent);

rbt_node *init_null_leaf_node(rbt_node *parent);

void destory_rbt_node(rbt_node **node_ptr);

typedef struct red_black_tree
{
    rbt_node *root;
    size_t data_size;
    size_t node_count;
    int (*cmp_func)(void *a, void *b);
    key_type *(*get_key)(data_type *data);
} red_black_tree;

red_black_tree *init_red_black_tree(size_t data_size,
                                    int (*cmp_func)(void *a, void *b),
                                    key_type *(*get_key)(data_type *data));

int rbt_is_empty(red_black_tree *rbt);

void rbt_insert(red_black_tree *rbt, data_type *data);

rbt_node *_rbt_insert(red_black_tree *rbt, rbt_node *root, rbt_node *parent, data_type *data);

data_type *rbt_search(red_black_tree *rbt,
                      key_type *key);

data_type *_rbt_search(red_black_tree *rbt,
                       rbt_node *root,
                       key_type *key);

void rbt_delete(red_black_tree *rbt, key_type *key);

void _rbt_delete(red_black_tree *rbt, rbt_node *root, key_type *key);

rbt_node *rbt_find_smallest(red_black_tree *rbt, rbt_node *root);

void rbt_delete_one_child(red_black_tree *rbt,
                          rbt_node *node_to_be_deleted);

void rbt_delete_case1(red_black_tree *rbt,
                      rbt_node *double_black_node);

void rbt_delete_case2(red_black_tree *rbt,
                      rbt_node *double_black_node);

void rbt_delete_case3(red_black_tree *rbt,
                      rbt_node *double_black_node);

void rbt_delete_case4(red_black_tree *rbt,
                      rbt_node *double_black_node);

void rbt_delete_case5(red_black_tree *rbt,
                      rbt_node *double_black_node);

void rbt_delete_case6(red_black_tree *rbt,
                      rbt_node *double_black_node);

void rbt_replace_node(red_black_tree *rbt, rbt_node **root_ptr, rbt_node *child);

rbt_node *rbt_find_sibling(red_black_tree *rbt, rbt_node *root);

void rbt_right_rotate(red_black_tree *rbt, rbt_node *root, int change_color);

void rbt_left_rotate(red_black_tree *rbt, rbt_node *root, int change_color);

//destory_tree
void _destory_red_black_tree(red_black_tree *rbt, rbt_node **root_ptr);

void destory_red_black_tree(red_black_tree **rbt_ptr);

//check red_black_tree

int rbt_is_validate(red_black_tree *rbt);

int black_nodes_count_is_same(rbt_node *root, size_t *black_count, size_t cur_count);

int no_red_red_parent_child(rbt_node *root, rbt_color parent_color);




typedef struct stack_node
{
    data_type *data;
    struct stack_node *last;
} stack_node;

stack_node *init_stack_node(data_type *data, size_t data_size, stack_node *last);

void destory_stack_node(stack_node **node_ptr);

typedef struct stack
{
    stack_node *top;
    stack_node *head;
    size_t length;
    size_t data_size;
} stack;

stack *init_stack(size_t data_size);

int stack_is_empty(stack *st);

void stack_push(stack *st, data_type *data);

void stack_pop(stack *st);

data_type *stack_get_peek(stack *st);

size_t stack_get_length(stack *st);

void destory_stack(stack **st_ptr);




typedef void pair_type;

typedef struct tree_map
{
    red_black_tree *rbt;
    size_t pair_size;
    size_t length;
    //get key and compare key
    key_type *(*get_key)(pair_type *piar);
    int (*cmp_func)(void *a, void *b);
    //get value
    value_type *(*get_value)(pair_type *pair);
} tree_map;

tree_map *init_tree_map(size_t pair_size,
                        int (*cmp_func)(void *a, void *b),
                        key_type *(*get_key)(pair_type *pair),
                        value_type *(*get_value)(pair_type *pair));

size_t tree_map_get_length(tree_map *tmap);

int tree_map_is_empty(tree_map *tmap);

void tree_map_put(tree_map *tmap, pair_type *pair);

int tree_map_has_key(tree_map *tmap, key_type *key);

pair_type *tree_map_get_pair(tree_map *tmap, key_type *key);

value_type *tree_map_get_value(tree_map *tmap, key_type *key);

void _tree_map_to_array(tree_map *tmap, rbt_node *root, array_list *arr);

array_list *tree_map_to_array(tree_map *tmap);

void tree_map_delete_pair(tree_map *tmap, key_type *key);

void destory_tree_map(tree_map **tmap_ptr);




typedef struct tree_set
{
    size_t data_size;
    size_t length;
    int (*cmp_func)(void *a, void *b);
    red_black_tree *rbt;
} tree_set;

key_type *tree_set_get_key(data_type *data);

tree_set *init_tree_set(size_t data_size,
                        int (*cmp_func)(void *a, void *b));

size_t tree_set_get_length(tree_set *tset);

int tree_set_is_empty(tree_set *tset);

void tree_set_put(tree_set *tset, data_type *data);

int tree_set_has_data(tree_set *tset, data_type *data);

void _tree_set_to_array(tree_set *tset, rbt_node *root, array_list *arr);

array_list *tree_set_to_array(tree_set *tset);

void tree_set_delete(tree_set *tset, data_type *data);

void destory_tree_set(tree_set **tset_ptr);


#endif
