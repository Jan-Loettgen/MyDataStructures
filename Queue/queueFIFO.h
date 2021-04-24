#ifndef QUEUEFIFO_H
#define QUEUEFIFO_H

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

queue* queue_create(int size);

int queue_add(queue** queue, const void* item);

const void* queue_pop(queue** queue);

#endif