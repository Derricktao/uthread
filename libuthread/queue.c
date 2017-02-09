#include <stdint.h>
#include <stdlib.h>

#include "queue.h"

typedef struct Node {
	struct Node* prev;
	struct Node* next;
	void *value; 

} Node;

struct queue {
	/* TODO Phase 1 */
	Node* head;
	Node* tail;
	int len;
};

queue_t queue_create(void)
{
	/* TODO Phase 1 */
	queue_t qt = malloc(sizeof(queue_t));
	
	qt->head = NULL;
	qt->tail = NULL;
	qt->len=0;
	return qt;
}

int queue_destroy(queue_t queue)
{
	/* TODO Phase 1 */
	if(!queue){
		return -1;
	}
	
	free(queue);
	return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	if(!queue){
		return -1;
	}
	
		Node* cur = queue->head; 
		Node* head = queue->head; 
		Node* temp = head; 
		
	 	if(!cur){

			cur = malloc(sizeof(Node));
			
			cur->value = data; 

			queue->tail=cur;
			queue->head=cur;
		}		
		else{
			cur = queue->tail;
			
			Node* new = malloc(sizeof(Node));
			 
			new->value = data;
			 
			new->prev = cur;
			new->next = NULL;
			 
			cur->next = new; 
			 
			queue->tail = new;
			
			
			
		}
		
		queue->len++;
	return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
	/* TODO Phase 1 */
	if(!queue || queue->len==0 ){
		return -1;
	}
	
	Node* head = queue->head; 
	Node* del = head;
	
	data = &(head->value);
	
	queue->head = head->next;
	
	queue->head->prev = NULL;
	
	queue->len--;
	
	free(del);
	return 0;
}

int queue_delete(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	if(!queue ){
		return -1;
	}
	
	Node* cur = queue->head; 
	Node* head = queue->head; 
	Node* del ; 
	
	int flag=0;
		

				//check if at end/beg of list
			

	 while(cur != NULL){				 
		 if(cur->value == data){			// find where value == data 
			//printf("\n");
			//printf("we have a match\n");
			//printf("%d\n", *(int*)(cur->value));
			flag=1;
			 break;
		 }				
		cur = cur->next;
	 }		
	 
	 
	 if(flag==0){		// if there is no match
		 return -1;
	 }
	 
	 
	if(cur == queue->head){		// value == data, at head
	
		del = queue->head;
	
		 queue->head = head->next;
		 queue->head->prev = NULL;
	}
	else if(cur == queue->tail){	// value == data, at tail
	
		del = queue->tail;
	
		queue->tail = queue->tail->prev;
		queue->tail->next = NULL;
	}
	else {									// value == data, in mid 
	
		del = cur; 
		
		cur->prev->next = cur->next;	 
		cur->next->prev = cur->prev;
	}
	 
	free(del);
	return 0;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	/* TODO Phase 1 */
	if(!queue ){
		return -1;
	}
	
	Node* cur = queue->head; 
	Node* head = queue->head; 
	Node* temp ; 
	
	
	
	//assert(queue_lenght(myqueue) == 1);
	
	//assert after each function call? , if delete then preseve the value of cur
	// to keep function from seg faulting 
	
	while(cur != NULL){				 
		func(cur->value);
		cur = cur->next;
	 }		
	
	
	return 0;
}

int queue_length(queue_t queue)
{
	/* TODO Phase 1 */
	if(!queue){
		return -1;
	}
	return queue->len;
}
