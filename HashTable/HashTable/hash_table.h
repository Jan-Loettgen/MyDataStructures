
#ifndef HASH_TABLE_H
#define HASH_TABLE_H
/*
* hash table struct which stores root array that stores linked lists
* which stores the linked lists, and also stores the tables size.
* 
*/
typedef long long (*hash_func)(char* key);

struct hash_table {
	struct node** root_arr;
	int table_size;
	hash_func hash_func;
};

typedef struct hash_table hash_table;
//external methods 
long long hash_func_poly(char* key);

hash_table* hash_table_init(int table_size, hash_func hash_func);

void hash_add_item(hash_table** hash_table, char* key, const void* ptr);

void hash_print_table(hash_table** hash_table);

const void* hash_find_item(hash_table** hash_table, char* key);

void hash_deallocate(hash_table** hash_table);

void hash_remove_item(hash_table** hash_table, char* key);

void hash_rehash(hash_table** hash_table, int new_table_size, hash_func hash_func);

#endif