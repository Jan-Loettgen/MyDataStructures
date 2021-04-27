/*
**********************Author information*************************
*
* Author: Jan Luca Loettgen
* Created: 24/04/2021
* Date last edited: 26/04/2021
*
******************************Purpose*****************************
*
* This file provides the methods and datatypes required to form
* any binary tree. The generic binary tree stores a value, and a
* pointer to an item, the pointer can be of any datatype including
* function pointers.
*
*******************************Summary*****************************
*
* Note this library does not have methods for utilsing the tree.
* this library contains only the basic tree strucutre. Functions
* required to add or insert items into the binary tree, are provided
* in other tree specfic files such as the "heap.h" file.
*/

#include "binary_tree.h"

//dynamically allocates a treenode to be the tree root
treenode* tree_create(int label, const void* item_ptr) {
    treenode* root = malloc(sizeof(treenode));
    if (root == NULL) { return NULL; }

    root->left_child = NULL;
    root->right_child = NULL;
    root->num_stored = 1;
    root->label = label;
    root->item_ptr = item_ptr;

    return root;
}

void tree_deallocate(treenode** root) {
    //method recursively deallocates all nodes in tree.

    if ((*root) == NULL) { return; }

    if ((*root)->left_child != NULL) {
        //if left child is not deallocated, deallocate it first.
        tree_deallocate(&((*root)->left_child));
    }

    if ((*root)->right_child != NULL) {
        //if right child is not deallocated, deallocate it first.
        tree_deallocate(&((*root)->right_child));
    }

    // once both childern are deallocated deallocate root.
    free(*root);
    *root = NULL;
}

void tree_swap_node(treenode* node_A, treenode* node_B){
    //swaps only contents of nodes. i.e. values, item_ptrs, and num stored.
    //XOR swap
    node_A->label = (node_A->label) ^ (node_B->label);
    node_B->label = (node_A->label) ^ (node_B->label);
    node_A->label = (node_A->label) ^ (node_B->label);

    //standard pointer swap with temp variable.
    void const* tmp_ptr = node_A->item_ptr;
    node_A->item_ptr = node_B->item_ptr;
    node_B->item_ptr = tmp_ptr;
}