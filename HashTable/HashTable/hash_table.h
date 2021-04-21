
#ifndef HASH_TABLE_H
#define HASH_TABLE_H
/*
* hash table struct which stores root array that stores linked lists
* which stores the linked lists, and also stores the tables size.
* 
*/
struct hash_table {
	struct node** root_arr;
	int table_size;
};

typedef struct hash_table hash_table;

//external methods 
hash_table* hash_table_init(int table_size);

void hash_add_item(hash_table** hash_table, char* key, const void* ptr);

void hash_print_table(hash_table** hash_table);

const void* hash_find_item(hash_table** hash_table, char* key);

const void* hash_deallocate(hash_table** hash_table);

void hash_remove_item(hash_table** hash_table, char* key);

#endif