
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\LinkedList\linked_list.h"

typedef long long (*hash_func)(char* key);

struct hash_table {
	struct node** root_arr;
	int table_size;
	int num_stored;
	hash_func hash_func;
	int automatic; //1 for yes, 0 for no.
	float load_factor;
	float growth_factor;

};

typedef struct hash_table hash_table;
//external methods 
long long hash_func_poly(char* key);

hash_table* hash_table_manu_init(int table_size, hash_func hash_func);

hash_table* hash_table_auto_init(int table_size, hash_func hash_func, float load_factor, float growth_factor);

void hash_add_item(hash_table** hash_table, char* key, const void* ptr);

void hash_print_table(hash_table** hash_table);

const void* hash_find_item(hash_table** hash_table, char* key);

void hash_deallocate(hash_table** hash_table);

void hash_remove_item(hash_table** hash_table, char* key);

void hash_rehash(hash_table** hash_table, float new_table_size, hash_func hash_func);

void hash_copy_contents(hash_table** table_from, hash_table** table_to);

#endif