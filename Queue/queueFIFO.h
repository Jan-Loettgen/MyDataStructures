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

#ifndef QUEUEFIFO_H
#define QUEUEFIFO_H

queue* queue_FIFO_create(int size);

int queue_FIFO_add(queue** q, const void* item);

const void* queue_FIFO_pop(queue** q);

int queue_FILO_destroy(queue** q);

#endif