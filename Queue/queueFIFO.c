/*
**********************Author information*************************
*
* Author: Jan Luca Loettgen
* Created: 25/04/2021
* Date last edited: 26/04/2021
*
******************************Purpose*****************************
*
* Simple first in first out queue, which can store a pointer to 
* any datatype or to a function.
*
*******************************Summary*****************************
*
* To create the queue the maximum size of the queue must be specfied.
* Once the queue is created elements can be added and removed using
* queue_FIFO_add and queue_FIFO_pop. After finished using queue call
* queue_FIFO_destroy to deallocate all dynamic memory.
*/

#include <stdlib.h>
#include "queueFIFO.h"
#include <stdio.h>

queue* queue_FIFO_create(int size) {

	queue* q = malloc(sizeof(queue));

	if (q != NULL) {
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

int queue_FIFO_add(queue** q, const void* item) {

	if (*q != NULL && (*q)->num_stored < (*q)->size) {

		q_element* elem = malloc(sizeof(q_element));

		if (elem != NULL) {
			elem->value = item;
			elem->next_element = NULL;

			if ((*q)->head == NULL) {
				(*q)->head = elem;
				(*q)->num_stored++;
			}
			else if ((*q)->tail == NULL) {
				(*q)->tail = elem;
				(*q)->head->next_element = elem;
				(*q)->num_stored++;
			}
			else {
				(*q)->tail->next_element = elem;
				(*q)->tail = elem;
				(*q)->num_stored++;
			}
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

const void* queue_FIFO_pop(queue** q) {

	if ((*q) != NULL && (*q)->head != NULL) {

		q_element* destroy_elem = (*q)->head;
		void const* return_value = (*q)->head->value;

		if ((*q)->head->next_element == (*q)->tail) {
			(*q)->tail = NULL;
		}
		(*q)->head = (*q)->head->next_element;
		(*q)->num_stored--;

		free(destroy_elem);

		return return_value;
	}
	else {
		return NULL;
	}
}

int queue_FIFO_destroy(queue** q){

	if (*q == NULL){ return 0; } //handles case where queue is null.

	if ((*q)->head == NULL) { //queue exits but is empty.
		free(*q);
	}

	if ((*q)->tail == NULL){//queue has head but no tail - 1 person in queue. 
		free((*q)->head);
		free((*q));
		return 1;
	}

	q_element* curr = (*q)->head;

	while (curr != (*q)->tail){
		q_element* aux_elem = curr;
		curr = curr->next_element;
		free(aux_elem);
	}
	free(curr);
	free(*q);
	q = NULL;
	return 1;
}