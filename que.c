#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
 #include <assert.h>

 // if queue NULL return -1
 
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
	return qt;
}

int queue_destroy(queue_t queue)
{
	free(queue);
}

int queue_enqueue(queue_t queue, void *data)
{
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
	
	Node* head = queue->head; 

	
	data = &head->value;
	
	queue->head = head->next;
	
	queue->head->prev = NULL;
	
	queue->len--;
	return 0;
}

int queue_delete(queue_t queue, void *data)
{
		Node* cur = queue->head; 
		Node* head = queue->head; 
		Node* temp ; 
		
		if(!cur){
			//return error?
		}
		else{
				//check if at end/beg of list
			

			 while(cur != NULL){				 
				 if(cur->value == data){			// find where value == data 
					//printf("\n");
					//printf("we have a match\n");
					//printf("%d\n", *(int*)(cur->value));
					 break;
				 }				
				cur = cur->next;
			 }		
			 
			 cur->prev->next = cur->next;
			 

			 
			 cur->next->prev = cur->prev;
			 
			 
			 
		}
		
	return 0;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	Node* cur = queue->head; 
	Node* head = queue->head; 
	Node* temp ; 
	
	return 0;
}

int queue_length(queue_t queue)
{
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

int main()
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
	
	queue_delete(queue,&c);
	
	queue_print(queue);
	
	//assert(queue_destroy(NULL) == -1);
	
	return 0;
}