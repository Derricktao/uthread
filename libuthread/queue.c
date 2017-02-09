#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <setjmp.h>

// how to check for errors?
 
typedef struct Node {
	struct Node* prev;
	struct Node* next;
	void *value; 

} Node;

typedef struct queue {
	
	Node* head;
	Node* tail;
	int len;
} *queue_t;

typedef void (*queue_func_t)(void *data);

// Apart from delete and iterate operations, all operations should be O(1).

queue_t queue_create(void)
{
	queue_t qt = malloc(sizeof(queue_t));
	
	qt->head = NULL;
	qt->tail = NULL;
	qt->len=0;
	return qt;
}

int queue_destroy(queue_t queue)		// done
{
	if(!queue){
		return -1;
	}
	
	free(queue);
	return 0;
}

int queue_enqueue(queue_t queue, void *data)	//done
{
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

int queue_dequeue(queue_t queue, void **data)  // done, check if works with one element
{
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

int queue_delete(queue_t queue, void *data)			// done
{
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

int queue_iterate(queue_t queue, queue_func_t func)  // done until needs modification
{
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
	
	if(!queue){
		return -1;
	}
	return queue->len;
}

void queue_print(queue_t queue){
	Node* cur = queue->head; 
	
	printf("\n");
	 
	 while(cur != NULL){
		 
		printf("%d\n", *(int*)(cur->value));
		
		cur = cur->next;

	 }
}

/*int main()
{

	queue_t queue;
	
	queue = queue_create();
	
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	
	void **e;
	
	queue_enqueue(queue,&a);
	queue_enqueue(queue,&b);
	queue_enqueue(queue,&c);
	queue_enqueue(queue,&d);
	
	queue_print(queue);
	printf("\n");
	
	
	queue_dequeue(queue,e);
	
	
	queue_print(queue);
	
	queue_delete(queue,&b);
	
	queue_print(queue);
	
	//assert(queue_destroy(NULL) == -1);
	
	return 0;
}*/
