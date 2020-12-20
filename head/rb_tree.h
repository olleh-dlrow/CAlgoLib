#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include "common.h"

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

#endif