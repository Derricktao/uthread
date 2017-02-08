#include <stdint.h>
#include <stdlib.h>


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


// Apart from delete and iterate operations, all operations should be O(1).

queue_t queue_create(void)
{
	queue_t qt;
	
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
			cur = tail;
			
			Node* new = malloc(sizeof(Node));
			 
			new->value = data;
			 
			new->prev = cur;
			new->next = NULL;
			 
			cur->next = new; 
			 
			queue->tail = new;
			
			
			
		}
		
		len++;
}

int queue_dequeue(queue_t queue, void **data)
{
	
	Node* head = queue->head; 

	
	data = &head->value;
	
	head = head->next;
	
	head->prev = NULL;
	
	len--;
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
			
			 while(cur != NULL){				 
				 if(cur->value == data){			// find where value == data 
					 break;
				 }				
				cur = cur->next;
			 }		
			 
			 temp = cur->prev 
			 
			 cur = cur->next;
			 
			 cur->prev = temp;
			 
			 
			 
		}
		
		
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	
}

int queue_length(queue_t queue)
{
	return len;
}


int main()
{
	
	
	return 0;
}