/*
**********************Author information*************************
*
* Author: Jan Luca Loettgen
* Created: 25/04/2021
* Date last edited: 26/04/2021
*
******************************Purpose*****************************
*
* Simple first in last out queue, which can store a pointer to 
* any datatype or to a function.
*
*******************************Summary*****************************
*
* To create the queue the maximum size of the queue must be specfied.
* Once the queue is created elements can be added and removed using
* queue_FILO_add and queue_FILO_pop. After finished using queue call
* queue_FIFO_destroy to deallocate all dynamic memory.
*/

#include <stdlib.h>
#include <stdio.h>
#include "queueFILO.h"

queue* queue_FILO_create(int size){

	queue* q = malloc(sizeof(queue));
	
	if (q  != NULL)  {
        q->head = NULL;
        q->tail = NULL;
        q->size = size;
        q->num_stored = 0;
        return q;
	}
    else {
        return NULL;
    }
}

int queue_FILO_add(queue** q, const void* item) {

	if (*q != NULL) {

		q_element* elem = malloc(sizeof(struct q_element));

		if (elem != NULL && (*q)->num_stored < (*q)->size) {
			elem->value = item;
			elem->next_element = (*q)->tail;
			(*q)->tail = elem;
			(*q)->num_stored++;
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

const void* queue_FILO_pop(queue** q) {

	if ((*q) != NULL && (*q)->tail != NULL) {

		const void* return_item;
		q_element* destroy_elem;

		return_item = (*q)->tail->value;
		destroy_elem = (*q)->tail;

		(*q)->tail = (*q)->tail->next_element;
		(*q)->num_stored--;

		free(destroy_elem);

		return return_item;
	}
	else {
		return NULL;
	}
}

int queue_FILO_destroy(queue** q) {

	if (*q == NULL) { return 0; } //handles case where queue is null.

	if ((*q)->tail == NULL) { //queue exits but is empty.
		free(*q);
		return 1;
	}

	q_element* curr = (*q)->tail;

	while (curr != NULL) {
		q_element* aux_elem = curr;
		curr = curr->next_element;
		free(aux_elem);
	}
	free(*q);
	return 1;
}