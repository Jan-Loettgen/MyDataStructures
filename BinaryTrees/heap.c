
/*
**********************Author information*************************
*
* Author: Jan Luca Loettgen
* Created: 25/04/2021
* Date last edited: 27/04/2021
*
******************************Purpose*****************************
*
* This file provides the insert and get max functions required
* in addition to the generic binary tree file to make a max heap.
* The heap is implemented using pointers and nodes as opposed to
* the more efficient version where the heap is represetned as an
* array. This is because this version is more challenging to 
* implement, and I wanted to pratice more with recursion and 
* and checking return values in recursive functions
* 
*******************************Summary*****************************
* 
* Both the heap_insert and the heap_get_max functions keep the heap
* strucutre intact and also keep the max heap strucutre of the heap.
* 
*/

#include "heap.h"

/* This functions recursively moves down the tree towards the position
*  where the new node needs to be added. Once it has reached the bottom
*  of the tree it creates a new node there. As the recursion returns to
*  call point (moving back up the tree) the functions compares each node
*  to its child along the way back up and swaps if the child is larger than
*  its parent. This function handles both inserting and sorting of max heap in an 
*  during same recursive call. time complexity to add and sort O(log(n)).
*/
int heap_insert(treenode** root, int label, const void* item_ptr) {

    if ((*root)->num_stored == 1) {//if tree has only 1 element then it has no childern->create left.

        (*root)->left_child = tree_create(label, item_ptr);
        if ((*root)->left_child == NULL) { return 0; }

        (*root)->num_stored++;

        //if after the new node was created the child is larger than pararent then swap
        if ((*root)->label < (*root)->left_child->label) {
            tree_swap_node(*root, (*root)->left_child);
        }
        return 1;
    }

    else if ((*root)->num_stored == 2) {//if the root has 2 elements then it has a left child -> create right child.

        (*root)->right_child = tree_create(label, item_ptr);
        if ((*root)->right_child == NULL) { return 0; }

        (*root)->num_stored++;

        //if after the new node was created the child is larger than pararent then swap
        if ((*root)->label < (*root)->right_child->label) {
            tree_swap_node(*root, (*root)->right_child);
        }
        return 1;
    }

    int k = log2((*root)->num_stored + 1);//tree depth
    int left_max = pow(2, k) + pow(2, k - 1) - 1;//furthest right element at depth k after going left once.

    //if true need to move left to get to pointer new node will be placed
    if ((*root)->num_stored + 1 >= pow(2, k) && (*root)->num_stored + 1 <= left_max) {
        if (heap_insert(&((*root)->left_child), label, item_ptr) != 0) {
            (*root)->num_stored++;

            //if after the new node was created the child is larger than pararent then swap
            if ((*root)->label < (*root)->left_child->label) {
                tree_swap_node(*root, (*root)->left_child);
            }
            return 1;
        }
        else { return 0; }
    }
    else {//didnt need to go left to get to new node position so go right.
        if (heap_insert(&((*root)->right_child), label, item_ptr) != 0) {
            (*root)->num_stored++;

            //if after the new node was created the child is larger than pararent then swap
            if ((*root)->label < (*root)->right_child->label) {
                tree_swap_node(*root, (*root)->right_child);
            }
            return 1;
        }
        else { return 0; }
    }
}

/* This function recursively swaps the top value of the tree down the tree. 
*  On the way down the max heap property of parent > child is kept in tact.
*  Once at the bottom the top node is destroyed and the ptr to the item stored
*  at the top node is returned back up the tree. While passing the item ptr up
*  the tree the number of nodes stored in each node is reduced by 1.
*/
const void* heap_get_max(treenode** root) {

    if (*root == NULL) { return NULL; }

    if ((*root)->num_stored == 3) {
        //if root has 3 elements then will be removing the right child.
        const void* return_ptr = (*root)->right_child->item_ptr;
        free((*root)->right_child);
        (*root)->right_child = NULL;

        return return_ptr;
    }
    else if ((*root)->num_stored == 2) {
        //if root has 2 elements then will be removing the left child.
        const void* return_ptr = (*root)->left_child->item_ptr;
        free((*root)->left_child);
        (*root)->left_child = NULL;

        return return_ptr;
    }

    int k = log2((*root)->num_stored);//tree depth
    int left_max = pow(2, k) + pow(2, k - 1) - 1;//furthest right element at depth k after going left once.

    //if the num stored in root is in this range then delete position is to the left.
    if ((*root)->num_stored >= pow(2, k) && (*root)->num_stored <= left_max) {
        //if delete position is to the left then swap root and left child.
        tree_swap_node(*root, (*root)->left_child);

        if ((*root)->right_child != NULL) {
            if ((*root)->label < (*root)->right_child->label) {
                // if right child is greater than new root value, then swap to keep max heap structure. 
                tree_swap_node(*root, (*root)->right_child);
            }
        }
        (*root)->num_stored--;
        return heap_get_max(&(*root)->left_child);
    }
    else {//if delete positon wasnt to the left then it must be to the right.
        tree_swap_node(*root, (*root)->right_child);

        if ((*root)->left_child != NULL) {
            if ((*root)->label < (*root)->left_child->label) {
                tree_swap_node(*root, (*root)->left_child);
            }
        }
        (*root)->num_stored--;
        return heap_get_max(&(*root)->right_child);
    }
}
