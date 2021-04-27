#ifndef Binary_TREE_H
#define Binary_TREE_H

#include <stdlib.h>

struct treenode {
    struct treenode* left_child;
    struct treenode* right_child;
    int num_stored;
    int label;
    const void* item_ptr;  
};

typedef struct treenode treenode;

treenode* tree_create(int label, const void* item_ptr);

void tree_deallocate(treenode** root);

void tree_swap_node(treenode* node_A, treenode* node_B);

#endif