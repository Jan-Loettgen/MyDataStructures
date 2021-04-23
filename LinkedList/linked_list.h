
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

struct entry {
	char* key;
	const void* item_ptr;
};
typedef struct entry entry;

struct node {
	entry* entry_ptr;
	struct node* next_ptr;
};
typedef struct node node;

//files required externally.

//entry functions
entry* ll_entry_create(char* key, const void* item_ptr);

void ll_entry_destroy(entry* entry_ptr);

const void* ll_entry_search(entry* entry, char* key);

//linked list functions
node* ll_create_node(char* key, const void* item_ptr);

void ll_destroy_node(node* node_ptr);

void ll_append_node(node** root, char* key, const void* item_ptr);

void ll_insert_node(node** root, char* key, const void* item_ptr);

void ll_destroy_list(node** root);

void ll_remove_element(node** root, char* key);

node* ll_search_list(node** root, char* key);

void ll_print_keys(node** root);

void ll_update_node(node** root, char* key, const void* new_item_ptr);

#endif