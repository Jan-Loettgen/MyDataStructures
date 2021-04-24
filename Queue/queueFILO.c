
#include <stdlib.h>
#include <stdio.h>
#include "queueFILO.h"

queue* queue_FILO_create(int size){

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

int queue_FILO_add(queue** queue, const void* item) {

	if (*queue != NULL && (*queue)->num_stored < (*queue)->size) {

		q_element* elem = malloc(sizeof(q_element));

		if (elem != NULL) {
			elem->value = item;

            elem->next_element = (*queue)->tail;
            (*queue)->tail = elem;
            (*queue)->num_stored++;
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

const void* queue_FILO_pop(queue** queue){

	if ((*queue) != NULL && (*queue)->tail !=NULL){

        q_element* return_qlem = (*queue)->tail;
        (*queue)->tail = (*queue)->tail->next_element;
		(*queue)->num_stored--;
		return return_qlem->value;
	}
	else {
		return NULL;
	}
}