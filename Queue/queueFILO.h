#ifndef QUEUE_H
#define QUEUE_H

struct q_element{
	const void* value;
	struct q_element* next_element; 
};
typedef struct q_element q_element;

struct queue{
	q_element* head;
	q_element* tail;
	int num_stored;
	int size;
};
typedef struct queue queue;

#endif

#ifndef QUEUE_FILO_H
#define QUEUE_FILO_H

queue* queue_FILO_create(int size);

int queue_FILO_add(queue** q, const void* item);

const void* queue_FILO_pop(queue** q);

int queue_FIFO_destroy(queue** q);

#endif