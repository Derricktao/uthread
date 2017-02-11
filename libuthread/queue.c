#include <stdint.h>
#include <stdlib.h>

#include "queue.h"

typedef struct Node {
	struct Node* next; // pointer to next node
	void *value; // pointer to data
} Node; // node struct for linked list

struct queue {
	/* TODO Phase 1 */

	Node* head; // pointer to top of queue
	Node* tail; // pointer to end of queue
	int len; // counter for size of queue
};

queue_t queue_create(void)
{
	queue_t qt = malloc(sizeof(queue_t)); // make space for queue
	qt->head = NULL; // initialize pointers to NULL
	qt->tail = NULL;
	qt->len = 0; // set length to 0

	return qt;
}

int queue_destroy(queue_t queue)
{
	if (!queue) return -1; // if NULL pointer, return -1
	
	free(queue); // free queue

	return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
	if (!queue) return -1; // if NULL pointer, return -1
	
	Node *new = malloc(sizeof(Node)); // make space for new node
	new->next = NULL; // set next pointer to NULL
	new->value = data; // set data

 	if(queue->len == 0) // if queue is empty
		queue->head = new; // set to head pointer
	else // if queue is not empty
		queue->tail->next = new; // set after last node
	
	queue->tail = new; // set to tail pointer
	queue->len++; // increment len
	return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
	if (!queue || !data || queue->len == 0) return -1; // if NULL pointers or is empty, return -1
	
	*data = queue->head->value;	// get data from head node
	queue->head = queue->head->next; // set head to 2nd element in queue
	queue->len--; // decrement len
	return 0;
}

int queue_delete(queue_t queue, void *data)
{
	if (!queue)	return -1; // if NULL pointer, return -1
	
	Node* cur = queue->head; // current node
	Node* prev = NULL; // previous node
	
	int flag = 0; // 0 - data not found , 1 - data found
		
	while(cur != NULL)
	{				 
		if(cur->value == data) // check if data is in list
		{
			flag = 1; // set flag and break
			break;				
		}

		prev = cur;
		cur = cur->next;
	}		
	 
	if(flag == 0) return -1; // if there is no match, return -1
	 
	if (cur == queue->head && cur == queue->tail) // if last item in queue
	{
		queue->head = NULL; // set head and tail to NULL
		queue->tail = NULL;
	}
	else if(cur == queue->head)	// value == data, at head
	{
		queue->head = cur->next; // set head to second element
	}
	else if(cur == queue->tail) // value == data, at tail
	{
		queue->tail = prev; // set tail to previous node
		queue->tail->next = NULL; // set next node of tail to NULL
	}
	else // value == data, in middle
	{
		prev->next = cur->next; // set next of previous node to current node's next
	}
	 
	free(cur); // free node
	queue->len--; // decrement len
	return 0;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	/* TODO Phase 1 */

	if(!queue) return -1; // if NULL pointer, return -1
	
	Node* cur = queue->head; // current node
		
	while(cur != NULL) // while not NULL
	{				 
		func(cur->value); // call function with data
		cur = cur->next; // set next node
	}		
	
	return 0;
}

int queue_length(queue_t queue)
{
	if (!queue) return -1; // if NULL pointer, return -1

	return queue->len; // return len
}