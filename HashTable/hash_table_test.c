#define _CRTDBG_MAP_ALLOC //added because it adds the file and line where the memory leak was created.

//#include <stdio.h>
//#include <stdlib.h>


#include <crtdbg.h> //used to detect memory leaks
//#include "hash_table.h" //contains hash table methdos.
#include "main.h"

int main1() {
	
	char s1[] = "Sarah";
	char s2[] = "Jessie";
	char s3[] = "Olga";
	char s4[] = "Luca";
	char s5[] = "Jan";
	char s6[] = "Matty";
	char s7[] = "Charlie";
	char s8[] = "Alan";
	char s9[] = "Ted";
	char s10[] = "Barney";
	char s11[] = "Robin";
	char s12[] = "Marc";
	char s13[] = "Pedro";

	int value1 = 5;
	int value2 = 10;
	int value3 = 15;
	int value4 = 20;
	int value5 = 25;
	int value6 = 0;
	int value7 = 5;
	int value8 = 10;
	int value9 = 15;
	int value10 = 20;
	int value11 = 25;
	int value12 = 0;
	int value13 = 42;

	//hash_table* hash_table = hash_table_manu_init(5, hash_func_poly);

	hash_table* hash_table = hash_table_auto_init(7, hash_func_poly, 0.75, 0.5);

	hash_add_item(&hash_table, s1, &value1);
	hash_add_item(&hash_table, s2, &value2);
	hash_add_item(&hash_table, s3, &value3);
	hash_add_item(&hash_table, s4, &value4);
	hash_add_item(&hash_table, s5, &value5);

	hash_add_item(&hash_table, s6, &value6);
	hash_add_item(&hash_table, s7, &value7);
	hash_add_item(&hash_table, s8, &value8);
	hash_print_table(&hash_table);
	hash_add_item(&hash_table, s9, &value9);
	hash_add_item(&hash_table, s10, &value10);
	hash_add_item(&hash_table, s11, &value11);
	hash_add_item(&hash_table, s12, &value12);
	hash_add_item(&hash_table, s13, &value13);
	
	hash_print_table(&hash_table);

	printf("%d\n", hash_table->table_size);
	
	hash_deallocate(&hash_table);

	_CrtDumpMemoryLeaks();

	return 1;
}
