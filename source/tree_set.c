#include "tree_set.h"

key_type *tree_set_get_key(data_type *data)
{
    return data;
}

tree_set *init_tree_set(size_t data_size,
                        int (*cmp_func)(void *a, void *b))
{
    tree_set *tset = (tree_set *)malloc(sizeof(tree_set));
    tset->data_size = data_size;
    tset->length = 0;
    tset->cmp_func = cmp_func;
    tset->rbt = init_red_black_tree(data_size, cmp_func, tree_set_get_key);
    return tset;
}
size_t tree_set_get_length(tree_set *tset)
{
    return tset->length;
}

int tree_set_is_empty(tree_set *tset)
{
    return tset->length == 0;
}

void tree_set_put(tree_set *tset, data_type *data)
{
    rbt_insert(tset->rbt, data);
    tset->length = tset->rbt->node_count;
    return;
}

void _tree_set_to_array(tree_set *tset, rbt_node *root, array_list *arr)
{
    if (root == NULL || root->is_null_leaf)
    {
        return;
    }
    _tree_set_to_array(tset, root->left, arr);
    array_list_push_back(arr, root->data);
    _tree_set_to_array(tset, root->right, arr);
}

array_list *tree_set_to_array(tree_set *tset)
{
    array_list *arr = init_array_list(tset->data_size);
    _tree_set_to_array(tset, tset->rbt->root, arr);
    return arr;
}

void tree_set_delete(tree_set *tset, data_type *data)
{
    rbt_delete(tset->rbt, data);
    tset->length = tset->rbt->node_count;
    return;
}

void destory_tree_set(tree_set **tset_ptr)
{
    tree_set *tset = *tset_ptr;
    destory_red_black_tree(&tset->rbt);
    free(tset);
    *tset_ptr = NULL;
    return;
}