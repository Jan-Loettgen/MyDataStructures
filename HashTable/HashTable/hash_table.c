/*
**********************Author information*************************
*
* Author: Jan Luca Loettgen
* Created: 22/04/2021
* Date last edited: 22/04/2021
*
******************************Purpose*****************************
*
* The functiosn within this program in combination with the generic
* linked list functions make up a generic hash table.
*
*
*******************************Summary*****************************
*
* The generic hash table is capable of storing pointers to any 
* datatype. Elements are stored in the hash table as a key-value 
* pairs. Elements can be accessed via the corresponding key. 
* The hash table makes use of backwards chaining to handle collions. 
* In its current form the hash table does not support rehashing, 
* and has a fixed size. The hash table makes uses of dynamically
* allocated memory, call "hash_deallocate" to free memory after use.
*
*/


#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>


struct hash_table {
	node** root_arr;
	int table_size;
};

typedef struct hash_table hash_table;

long long hash_func_poly(char* key) {
	int g = 31;
	long long hash = 0;
	for (int i = 0; i < strlen(key); i++) {
		hash = g * hash + (int)key[i];
	}
	return hash;
}

hash_table* hash_table_init(int table_size) {
	hash_table* hash_table = malloc(sizeof(struct hash_table));

	hash_table->table_size = table_size;

	hash_table->root_arr = malloc(table_size * sizeof(node*));

	for (int i = 0; i < table_size; i++) {
		hash_table->root_arr[i] = NULL;
	}
	return hash_table;
}

void hash_add_item(hash_table** hash_table, char* key, const void* ptr) {
	int index = (hash_func_poly(key) % ((*hash_table)->table_size));

	if ((*hash_table)->root_arr[index] == NULL) {
		(*hash_table)->root_arr[index] = ll_create_node(key, ptr);
	}
	else {
		ll_insert_node(&((*hash_table)->root_arr[index]), key, ptr);
	}
}

void hash_print_table(hash_table** hash_table) {

	for (int i = 0; i < ((*hash_table)->table_size); i++) {
		if ((*hash_table)->root_arr[i] != NULL) {
			printf("[%d] ->", i);
			ll_print_keys(&((*hash_table)->root_arr[i]));
		}
	}
	printf("%s\n", "===========================================");
}

const void* hash_find_item(hash_table** hash_table, char* key) {
	int index = (hash_func_poly(key) % ((*hash_table)->table_size));

	node* node_ptr = ll_search_list(&((*hash_table)->root_arr[index]), key);

	return node_ptr->entry_ptr->item_ptr;
}

const void* hash_deallocate(hash_table** hash_table) {

	for (int i = 0; i < (*hash_table)->table_size; i++) {
		if ((*hash_table)->root_arr[i] != NULL) {
			ll_destroy_list(&((*hash_table)->root_arr[i]));
		}
	}

	free((*hash_table)->root_arr);
	free(*hash_table);
	*hash_table = NULL;
}

void hash_remove_item(hash_table** hash_table, char* key) {
	int index = (hash_func_poly(key) % (*hash_table)->table_size);

	ll_remove_element(&((*hash_table)->root_arr[index]), key);
}