
/*
**********************Author information*************************
* 
* Author: Jan Luca Loettgen
* Created: 18/04/2021
* Date last edited: 20/04/2021
* 
******************************Purpose*****************************
*
* The functions in this file make up functions requried
* by a generic linked list. 
*
*******************************Summary*****************************
* 
* The generic linked list stores a pointer to the next node in the 
* linked list and a pointer to an entry. The entry is a key-value 
* pair,where the key is string, and the value is a pointer to the
* item. The item can be of any  datatype type. Access to the 
* items/values is via the keys. Linked lists makes use of 
* dynamically allocated memory, call "ll_destroy_list" to free
* memory. 
* 
*/


#include "linked_list.h"


entry* ll_entry_create(char* key, const void* item_ptr) {
	entry* ptr = malloc(sizeof(entry));

	if (ptr == NULL) { exit(9); }

	ptr->key = key;
	ptr->item_ptr = item_ptr;
	return ptr;
}

void ll_entry_destroy(entry* entry_ptr) {
	//currently if entry stores a pointer that is not being destroyed.
	free(entry_ptr); 
}

const void* ll_entry_search(entry* entry, char* key) {
	if (entry->key == key) {
		return entry->item_ptr;
	}
	else {
		return NULL;
	}
}

//node* ll_create_node(entry* entry_ptr) {
node* ll_create_node(char* key, const void* item_ptr) {

	entry* entry_ptr = ll_entry_create(key, item_ptr);

	node* ptr = malloc(sizeof(node));

	if (ptr == NULL) { exit(10); }

	ptr->entry_ptr = entry_ptr;
	ptr->next_ptr = NULL;

	return ptr;
}

void ll_destroy_node(node* node_ptr) {
	//just blows up a node without consideration of the effect on the linked list.
	//does however, ensure to destroy the entry stored at node before node itself.
	ll_entry_destroy(node_ptr->entry_ptr);
	free(node_ptr);
}

//void ll_append_node(node** root, node* node) {
void ll_append_node(node** root, char* key, const void* item_ptr){
	//appends nodde to end of linked list. Note time complexity O(n).
	node* node = ll_create_node(key, item_ptr);

	struct node* curr = *root;
	while (curr->next_ptr != NULL) {
		curr = curr->next_ptr;
	}
	curr->next_ptr = node;
}

//void ll_insert_node(node** root, node* node) {
void ll_insert_node(node** root, char* key, const void* item_ptr){
	//adds a new node at start of list. effectively creates a new root.
	//note time complexity O(1) hence better to add elements at start of list than end of list.
	node* node = ll_create_node(key, item_ptr);
	node->next_ptr = *root;
	*root = node;
}

void ll_destroy_list(node** root) {
	node* curr = *root;
	while (curr != NULL) {
		struct node* prev = curr;
		curr = curr->next_ptr;
		ll_destroy_node(prev);
	}
}

void ll_remove_element(node** root, char* key) {
	if (*root == NULL) {//handle the case that there is list.
		return;
	}

	//handles the case where the root is the element to remove.
	if ((*root)->entry_ptr->key == key) {
		node* node_to_remove = *root;
		*root = (*root)->next_ptr;
		ll_destroy_node(node_to_remove);
		return;
	}
	//searchs other nodes in list for key
	node* curr = *root;
	while (curr->next_ptr != NULL) {
		if (curr->next_ptr->entry_ptr->key == key) {
			node* node_to_remove = curr->next_ptr;
			curr->next_ptr = curr->next_ptr->next_ptr;
			ll_destroy_node(node_to_remove);
			return;
		}
		curr = curr->next_ptr;
	}

	return;
}

node* ll_search_list(node** root, char* key) {
	// ll_search_list returns node where desired item is stored.
	node* curr = *root;

	while (curr != NULL) {
		if (curr->entry_ptr->key == key) {
			return curr;
		}
		curr = curr->next_ptr;
	}
	return curr;
}

void ll_print_keys(node** root) {
	node* curr = *root;
	while (curr != NULL) {
		printf(" %s ->", curr->entry_ptr->key);
		curr = curr->next_ptr;
	}
	printf("%s", "\n");
}

void ll_update_node(node** root, char* key, const void* new_item_ptr) {
	node* node = ll_search_list(root, key);
	node->entry_ptr->item_ptr = new_item_ptr;

}