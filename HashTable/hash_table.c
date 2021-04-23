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
#include "hash_table.h"

long long hash_func_poly(char* key) {
	int g = 31;
	long long hash = 0;
	for (int i = 0; i < strlen(key); i++) {
		hash = g * hash + (int)key[i];
	}
	return hash;
}

hash_table* hash_table_manu_init(int table_size, hash_func hash_func) {

	hash_table* hash_table = malloc(sizeof(struct hash_table));
	if (hash_table == NULL) { exit(101); }

	hash_table->root_arr = malloc(table_size * sizeof(node*));
	if (hash_table->root_arr == NULL) { exit(102); }

	hash_table->automatic = 0; //false.

	hash_table->hash_func = hash_func;
	hash_table->table_size = table_size;
	hash_table->num_stored = 0;

	for (int i = 0; i < table_size; i++) {
		hash_table->root_arr[i] = NULL;
	}
	return hash_table;
}

hash_table* hash_table_auto_init(int table_size, hash_func hash_func, float load_factor, float growth_factor) {

	hash_table* hash_table = malloc(sizeof(struct hash_table));
	if (hash_table == NULL) { exit(103); }

	hash_table->root_arr = malloc(table_size * sizeof(node*));
	if (hash_table->root_arr == NULL) { exit(104); }

	hash_table->automatic = 1;//automatically managed hash table.
	hash_table->load_factor = load_factor; //maximum load factor.
	hash_table->growth_factor = growth_factor;//growth factor of table.

	hash_table->hash_func = hash_func;
	hash_table->table_size = table_size;
	hash_table->num_stored = 0;

	for (int i = 0; i < table_size; i++) {
		hash_table->root_arr[i] = NULL;
	}
	return hash_table;
}

void hash_add_item(hash_table** hash_table, char* key, const void* ptr) {
	int index = ((*hash_table)->hash_func(key) % ((*hash_table)->table_size));

	if ((*hash_table)->root_arr[index] == NULL) {
		//if nothing is stored at this index yet.
		(*hash_table)->root_arr[index] = ll_create_node(key, ptr);
		((*hash_table)->num_stored)++;
	}
	else {
		if (ll_search_list(&((*hash_table)->root_arr[index]), key) == NULL) {
			//linked list already at index but node with given key doesnt exist
			ll_insert_node(&((*hash_table)->root_arr[index]), key, ptr);
			((*hash_table)->num_stored)++;
		}
		else {
			//linked list already exists and node with key already exists.
			ll_update_node(&((*hash_table)->root_arr[index]), key, ptr);
		}
	}

	if ((*hash_table)->automatic == 1) {
		if (((*hash_table)->load_factor) <= (((*hash_table)->num_stored) / (*hash_table)->table_size)) {
			float new_table_size = ((*hash_table)->table_size) * (1.0 + ((*hash_table)->growth_factor));
			hash_rehash(hash_table, new_table_size, (*hash_table)->hash_func);
		}
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

	int index = ((*hash_table)->hash_func(key) % ((*hash_table)->table_size));

	node* node_ptr = ll_search_list(&((*hash_table)->root_arr[index]), key);

	if (node_ptr == NULL) { return NULL; }

	return node_ptr->entry_ptr->item_ptr;
}

void hash_deallocate(hash_table** hash_table) {
	if (*hash_table == NULL) { return; }//handles case where there is no hash table to deallocate

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
	int index = ((*hash_table)->hash_func(key) % (*hash_table)->table_size);

	ll_remove_element(&((*hash_table)->root_arr[index]), key);
	((*hash_table)->num_stored)--;
}

void hash_rehash(hash_table** hash_table, float new_table_size, hash_func hash_func) {

	struct hash_table* new_hash_table;

	if ((*hash_table)->automatic == 0) {
		new_hash_table = hash_table_manu_init(new_table_size, hash_func);
	}
	else {
		new_hash_table = hash_table_auto_init(new_table_size, (*hash_table)->hash_func, (*hash_table)->load_factor, (*hash_table)->growth_factor);
	}

	hash_copy_contents(hash_table, &new_hash_table);

	hash_deallocate(hash_table);
	*hash_table = new_hash_table;

	return;
}

void hash_copy_contents(hash_table** table_from, hash_table** table_to){
	if (table_from == NULL || table_to == NULL) { return; }

	for (int i = 0; i < (*table_from)->table_size; i++) {

		if ((*table_from)->root_arr[i] != NULL) {

			node* curr = (*table_from)->root_arr[i];
			while (curr != NULL) {

				hash_add_item(table_to, curr->entry_ptr->key, curr->entry_ptr->item_ptr);
				curr = curr->next_ptr;
			}
		}
	}

}




