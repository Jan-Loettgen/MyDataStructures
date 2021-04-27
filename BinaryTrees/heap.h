#ifndef HEAP_H
#define HEAP_H

#include "binary_tree.h"
#include <math.h>
#include <stdio.h>

int heap_insert(treenode** root, int label, const void* item_ptr);

const void* heap_get_max(treenode** root);

#endif