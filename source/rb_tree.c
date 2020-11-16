#include "rb_tree.h"

rbt_node *init_black_node(data_type *data, size_t data_size)
{
    rbt_node *node = (rbt_node *)malloc(sizeof(rbt_node));
    node->is_null_leaf = 0;
    node->data = (void *)malloc(data_size);
    shift_data(data, node->data, data_size);
    node->color = RBT_BLACK;
    //TODO:
    node->parent = NULL;
    //
    node->left = init_null_leaf_node(node);
    node->right = init_null_leaf_node(node);
    return node;
}

rbt_node *init_red_node(data_type *data, size_t data_size, rbt_node *parent)
{
    rbt_node *node = (rbt_node *)malloc(sizeof(rbt_node));
    node->is_null_leaf = 0;
    node->data = (void *)malloc(data_size);
    shift_data(data, node->data, data_size);
    node->color = RBT_RED;
    node->parent = parent;
    node->left = init_null_leaf_node(node);
    node->right = init_null_leaf_node(node);
    return node;
}

rbt_node *init_null_leaf_node(rbt_node *parent)
{
    rbt_node *leaf = (rbt_node *)malloc(sizeof(rbt_node));
    leaf->is_null_leaf = 1;
    leaf->data = NULL;
    leaf->color = RBT_BLACK;
    leaf->left = NULL;
    leaf->right = NULL;
    return leaf;
}

void destory_rbt_node(rbt_node **node_ptr)
{
    rbt_node *node = *node_ptr;
    free(node->data);
    free(node);
    *node_ptr = NULL;
    return;
}

red_black_tree *init_red_black_tree(size_t data_size,
                                    int (*cmp_func)(void *a, void *b),
                                    key_type *(*get_key)(data_type *data))
{
    red_black_tree *rbt = (red_black_tree *)malloc(sizeof(red_black_tree));
    rbt->data_size = data_size;
    rbt->node_count = 0;
    rbt->root = NULL;
    rbt->cmp_func = cmp_func;
    rbt->get_key = get_key;
    return rbt;
}

int rbt_is_empty(red_black_tree *rbt)
{
    return rbt->node_count == 0;
}

void rbt_insert(red_black_tree *rbt, data_type *data)
{
    rbt->root = _rbt_insert(rbt, rbt->root, NULL, data);
    log("insert success..\n\n");
    rbt->node_count++;
    return;
}

rbt_node *_rbt_insert(red_black_tree *rbt,
                      rbt_node *root, rbt_node *parent,
                      data_type *data)
{
    log("start insert.\n");
    if (root == NULL || root->is_null_leaf)
    {
        log("root is null or leaf.\n");
        if (parent != NULL)
        {
            log("root is leaf. end insert.\n");
            return init_red_node(data, rbt->data_size, parent);
        }
        else
        {
            log("root is null. end insert.\n");
            return init_black_node(data, rbt->data_size);
        }
    }
    key_type *root_key = rbt->get_key(root->data);
    key_type *key = rbt->get_key(data);
    if (rbt->cmp_func(root_key, key) == 0)
    {
        //printf("warning: duplicate happened!\n");
        shift_data(data, root->data, rbt->data_size);
        rbt->node_count--;
        return root;
    }
    int is_left = 0;
    if (rbt->cmp_func(root_key, key) > 0)
    {
        rbt_node *left = _rbt_insert(rbt, root->left, root, data);
        if (left == root->parent)
        {
            return left;
        }
        root->left = left;
        is_left = 1;
    }
    else
    {
        rbt_node *right = _rbt_insert(rbt, root->right, root, data);
        if (right == root->parent)
        {
            return right;
        }
        root->right = right;
        is_left = 0;
    }
    if (is_left)
    {
        log("inserted node is left.\n");
        if (root->color == RBT_RED && root->left->color == RBT_RED)
        {
            rbt_node *sibling = rbt_find_sibling(rbt, root);
            if (sibling == NULL || sibling->color == RBT_BLACK)
            {
                if (root->parent->left == root)
                {
                    rbt_right_rotate(rbt, root, 1);
                }
                else
                {
                    rbt_right_rotate(rbt, root->left, 0);
                    root = root->parent;
                    rbt_left_rotate(rbt, root, 1);
                }
            }
            else
            {
                root->color = RBT_BLACK;
                sibling->color = RBT_BLACK;
                if (root->parent->parent != NULL)
                {
                    root->parent->color = RBT_RED;
                }
            }
        }
    }
    else
    {
        log("inserted node is right.\n");
        if (root->color == RBT_RED && root->right->color == RBT_RED)
        {
            rbt_node *sibling = rbt_find_sibling(rbt, root);
            if (sibling == NULL || sibling->color == RBT_BLACK)
            {
                if (root->parent->right == root)
                {
                    rbt_left_rotate(rbt, root, 1);
                }
                else
                {
                    rbt_left_rotate(rbt, root->right, 0);
                    root = root->parent;
                    rbt_right_rotate(rbt, root, 1);
                }
            }
            else
            {
                root->color = RBT_BLACK;
                sibling->color = RBT_BLACK;
                if (root->parent->parent != NULL)
                {
                    root->parent->color = RBT_RED;
                }
            }
        }
    }
    log("end insert.\n");
    return root;
}

data_type *rbt_search(red_black_tree *rbt,
                      key_type *key)
{
    return _rbt_search(rbt, rbt->root, key);
}

data_type *_rbt_search(red_black_tree *rbt,
                       rbt_node *root,
                       key_type *key)
{
    if (root == NULL || root->is_null_leaf)
    {
        return NULL;
    }
    key_type *data_key = rbt->get_key(root->data);
    if (rbt->cmp_func(data_key, key) == 0)
    {
        return root->data;
    }
    if (rbt->cmp_func(data_key, key) < 0)
    {
        return _rbt_search(rbt, root->right, key);
    }
    else
    {
        return _rbt_search(rbt, root->left, key);
    }
}

void rbt_delete(red_black_tree *rbt, key_type *key)
{
    _rbt_delete(rbt, rbt->root, key);
    rbt->node_count--;
    if (rbt->root == NULL)
    {
        return;
    }
    if (rbt->root->is_null_leaf)
    {
        free(rbt->root);
        rbt->root = NULL;
    }
    return;
}

void _rbt_delete(red_black_tree *rbt, rbt_node *root, key_type *key)
{
    if (root == NULL || root->is_null_leaf)
    {
        rbt->node_count++;
        return;
    }
    key_type *root_key = rbt->get_key(root->data);
    if (rbt->cmp_func(root_key, key) == 0)
    {
        if (root->right->is_null_leaf || root->left->is_null_leaf)
        {
            rbt_delete_one_child(rbt, root);
        }
        else
        {
            rbt_node *inorder_successor = rbt_find_smallest(rbt, root->right);
            shift_data(inorder_successor->data, root->data, rbt->data_size);
            _rbt_delete(rbt, root->right,
                        rbt->get_key(inorder_successor->data));
        }
    }
    else if (rbt->cmp_func(root_key, key) < 0)
    {
        _rbt_delete(rbt, root->right, key);
    }
    else
    {
        _rbt_delete(rbt, root->left, key);
    }
    return;
}

rbt_node *rbt_find_smallest(red_black_tree *rbt, rbt_node *root)
{
    rbt_node *prev = NULL;
    while (root != NULL && !root->is_null_leaf)
    {
        prev = root;
        root = root->left;
    }
    return prev != NULL ? prev : root;
}

void rbt_delete_one_child(red_black_tree *rbt,
                          rbt_node *node_to_be_deleted)
{
    rbt_node *child =
        node_to_be_deleted->right->is_null_leaf ? node_to_be_deleted->left : node_to_be_deleted->right;

    rbt_color del_color = node_to_be_deleted->color;
    rbt_replace_node(rbt, &node_to_be_deleted, child);

    if (del_color == RBT_BLACK)
    {
        if (child->color == RBT_RED)
        {
            child->color = RBT_BLACK;
        }
        else
        {
            rbt_delete_case1(rbt, child);
        }
    }
    return;
}

/*double black node becomes root then we are done. Turning it into single black*/
void rbt_delete_case1(red_black_tree *rbt,
                      rbt_node *double_black_node)
{
    if (double_black_node->parent == NULL)
    {
        rbt->root = double_black_node;
        return;
    }
    rbt_delete_case2(rbt, double_black_node);
    return;
}

/*sibling is red and parent and sibling's children are black then rotate it
 so that sibling becomes black. double black node is still double black so need further 
 processing.*/
void rbt_delete_case2(red_black_tree *rbt,
                      rbt_node *double_black_node)
{
    rbt_node *sibling_node = rbt_find_sibling(rbt, double_black_node);
    if (sibling_node->color == RBT_RED)
    {
        if (sibling_node == sibling_node->parent->left)
        {
            rbt_right_rotate(rbt, sibling_node, 1);
        }
        else
        {
            rbt_left_rotate(rbt, sibling_node, 1);
        }
        if (sibling_node->parent == NULL)
        {
            rbt->root = sibling_node;
        }
    }
    rbt_delete_case3(rbt, double_black_node);
    return;
}

/**
* If sibling, sibling's children and parent are all black then turn sibling
* into red. This reduces black node for both the paths from parent. Now parent
* is new double black node which needs further processing by going back to
* case1.
*/
void rbt_delete_case3(red_black_tree *rbt,
                      rbt_node *double_black_node)
{
    rbt_node *sibling_node = rbt_find_sibling(rbt, double_black_node);
    if (double_black_node->parent->color == RBT_BLACK && sibling_node->color == RBT_BLACK && sibling_node->left->color == RBT_BLACK && sibling_node->right->color == RBT_BLACK)
    {
        sibling_node->color = RBT_RED;
        rbt_delete_case1(rbt, double_black_node->parent);
    }
    else
    {
        rbt_delete_case4(rbt, double_black_node);
    }
}

/**
* If sibling color is black, parent color is red and sibling's children color
* is black then swap color b/w sibling and parent. This increases one black
* node on double black node path but does not affect black node count on
* sibling path. We are done if we hit this situation.
*/
void rbt_delete_case4(red_black_tree *rbt,
                      rbt_node *double_black_node)
{
    rbt_node *sibling_node = rbt_find_sibling(rbt, double_black_node);
    if (double_black_node->parent->color == RBT_RED && sibling_node->color == RBT_BLACK && sibling_node->left->color == RBT_BLACK && sibling_node->right->color == RBT_BLACK)
    {
        sibling_node->color = RBT_RED;
        double_black_node->parent->color = RBT_BLACK;
        return;
    }
    else
    {
        rbt_delete_case5(rbt, double_black_node);
    }
}

/**
* If sibling is black, double black node is left child of its parent, siblings
* right child is black and sibling's left child is red then do a right rotation
* at siblings left child and swap colors. This converts it to delete case6. It
* will also have a mirror case.
*/
void rbt_delete_case5(red_black_tree *rbt,
                      rbt_node *double_black_node)
{
    rbt_node *sibling_node = rbt_find_sibling(rbt, double_black_node);
    if (sibling_node->color == RBT_BLACK)
    {
        if (double_black_node->parent->left == double_black_node && sibling_node->right->color == RBT_BLACK && sibling_node->left->color == RBT_RED)
        {
            rbt_right_rotate(rbt, sibling_node->left, 1);
        }
        else if (double_black_node->parent->left != double_black_node && sibling_node->left->color == RBT_BLACK && sibling_node->right->color == RBT_RED)
        {
            rbt_left_rotate(rbt, sibling_node->right, 1);
        }
    }
    rbt_delete_case6(rbt, double_black_node);
}

/**
* If sibling is black, double black node is left child of its parent, sibling
* left child is black and sibling's right child is red, sibling takes its
* parent color, parent color becomes black, sibling's right child becomes black
* and then do left rotation at sibling without any further change in color.
* This removes double black and we are done. This also has a mirror condition.
*/
void rbt_delete_case6(red_black_tree *rbt,
                      rbt_node *double_black_node)
{
    rbt_node *sibling_node = rbt_find_sibling(rbt, double_black_node);
    sibling_node->color = sibling_node->parent->color;
    sibling_node->parent->color = RBT_BLACK;
    if (double_black_node->parent->left == double_black_node)
    {
        sibling_node->right->color = RBT_BLACK;
        rbt_left_rotate(rbt, sibling_node, 0);
    }
    else
    {
        sibling_node->left->color = RBT_BLACK;
        rbt_right_rotate(rbt, sibling_node, 0);
    }
    if (sibling_node->parent == NULL)
    {
        rbt->root = sibling_node;
    }
    return;
}

void rbt_replace_node(red_black_tree *rbt, rbt_node **root_ptr, rbt_node *child)
{
    rbt_node *root = *root_ptr;
    child->parent = root->parent;
    if (root->parent == NULL)
    {
        rbt->root = child;
    }
    else
    {
        if (root->parent->left == root)
        {
            root->parent->left = child;
        }
        else
        {
            root->parent->right = child;
        }
    }
    free(root->data);
    free(root);
    *root_ptr = NULL;
    return;
}

rbt_node *rbt_find_sibling(red_black_tree *rbt, rbt_node *root)
{
    rbt_node *parent = root->parent;
    if (parent->left == root)
    {
        if (parent->right->is_null_leaf)
        {
            return NULL;
        }
        else
        {
            return parent->right;
        }
    }
    else
    {
        if (parent->left->is_null_leaf)
        {
            return NULL;
        }
        else
        {
            return parent->left;
        }
    }
}

void rbt_right_rotate(red_black_tree *rbt, rbt_node *root, int change_color)
{
    rbt_node *parent = root->parent;
    root->parent = parent->parent;
    if (parent->parent != NULL)
    {
        if (parent->parent->right == parent)
        {
            parent->parent->right = root;
        }
        else
        {
            parent->parent->left = root;
        }
    }
    rbt_node *right = root->right;
    root->right = parent;
    parent->parent = root;
    parent->left = right;
    if (right != NULL)
    {
        right->parent = parent;
    }
    if (change_color)
    {
        root->color = RBT_BLACK;
        parent->color = RBT_RED;
    }
    return;
}

void rbt_left_rotate(red_black_tree *rbt, rbt_node *root, int change_color)
{
    rbt_node *parent = root->parent;
    root->parent = parent->parent;
    if (parent->parent != NULL)
    {
        if (parent->parent->right == parent)
        {
            parent->parent->right = root;
        }
        else
        {
            parent->parent->left = root;
        }
    }
    rbt_node *left = root->left;
    root->left = parent;
    parent->parent = root;
    parent->right = left;
    if (left != NULL)
    {
        left->parent = parent;
    }
    if (change_color)
    {
        root->color = RBT_BLACK;
        parent->color = RBT_RED;
    }
    return;
}

void _destory_red_black_tree(red_black_tree *rbt, rbt_node **root_ptr)
{
    rbt_node *root = *root_ptr;
    if (root == NULL)
    {
        return;
    }
    if (root->is_null_leaf)
    {
        free(root);
        *root_ptr = NULL;
        return;
    }
    _destory_red_black_tree(rbt, &root->left);
    _destory_red_black_tree(rbt, &root->right);
    free(root);
    *root_ptr = NULL;
    return;
}

void destory_red_black_tree(red_black_tree **rbt_ptr)
{
    red_black_tree *rbt = *rbt_ptr;
    _destory_red_black_tree(rbt, &rbt->root);
    *rbt_ptr = NULL;
    return;
}

int rbt_is_validate(red_black_tree *rbt)
{
    rbt_node *root = rbt->root;
    if (root == NULL)
    {
        return 1;
    }
    if (root->color != RBT_BLACK)
    {
        printf("root is not black!\n");
        return 0;
    }
    size_t b = 0;
    if (!black_nodes_count_is_same(root, &b, 0))
    {
        printf("nodes count not same!\n");
        return 0;
    }
    if (!no_red_red_parent_child(root, RBT_BLACK))
    {
        printf("has red red child!\n");
        return 0;
    }
    return 1;
    //return black_nodes_count_is_same(root, &b, 0) && no_red_red_parent_child(root, RBT_BLACK);
}

int black_nodes_count_is_same(rbt_node *root, size_t *black_count, size_t cur_count)
{
    if (root->color == RBT_BLACK)
    {
        cur_count++;
    }
    if (root->left == NULL && root->right == NULL)
    {
        if (*black_count == 0)
        {
            *black_count = cur_count;
            return 1;
        }
        else
        {
            return cur_count == *black_count;
        }
    }
    return black_nodes_count_is_same(root->left, black_count, cur_count) && black_nodes_count_is_same(root->right, black_count, cur_count);
}

int no_red_red_parent_child(rbt_node *root, rbt_color parent_color)
{
    if (root == NULL)
    {
        return 1;
    }
    if (root->color == RBT_RED && parent_color == RBT_RED)
    {
        return 0;
    }
    return no_red_red_parent_child(root->left, root->color) && no_red_red_parent_child(root->right, root->color);
}
