
#include <stdlib.h>
#include "queueFIFO.h"
#include <stdio.h>

queue* queue_create(int size){

	queue* queue = malloc(sizeof(queue));
	
	if (queue  != NULL)  {
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = size;
        queue->num_stored = 0;
        return queue;
	}
    else {
        return NULL;
    }
}

int queue_add(queue** queue, const void* item) {

	if (*queue != NULL && (*queue)->num_stored < (*queue)->size) {

		q_element* elem = malloc(sizeof(q_element));

		if (elem != NULL) {
			elem->value = item;
			elem->next_element = NULL;

			if ((*queue)->head == NULL){
				(*queue)->head = elem;
				(*queue)->num_stored++;
			}
			else if((*queue)->tail == NULL){
				(*queue)->tail = elem;
				(*queue)->head->next_element = elem;
				(*queue)->num_stored++;
			}	
			else {
				(*queue)->tail->next_element = elem;
				(*queue)->tail = elem;
				(*queue)->num_stored++;
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

const void* queue_pop(queue** queue){

	q_element* return_qlem;

	if ((*queue) != NULL && (*queue)->head !=NULL){
		
		return_qlem = (*queue)->head;

		if ((*queue)->head->next_element == (*queue)->tail){
			(*queue)->tail = NULL;
		}
		(*queue)->head = (*queue)->head->next_element;
		(*queue)->num_stored--;

		return return_qlem->value;
	}
	else {
		return NULL;
	}
}