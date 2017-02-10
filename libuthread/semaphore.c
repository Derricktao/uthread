#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define _UTHREAD_PRIVATE
#include "preempt.h"
#include "queue.h"
#include "semaphore.h"
#include "uthread.h"



typedef struct semaphore {
	/* TODO Phase 3 */
	size_t count;
	queue_t blockQ;
} *sem_t;

	

sem_t sem_create(size_t count)
{
	/* TODO Phase 3 */
	
	// if count is negative then failure 
	if(count<0){
		return NULL;
	}

	sem_t sem = malloc(sizeof(sem_t));
	
	sem->count = count;
	
	sem->blockQ = queue_create();
	
	return sem;
}

int sem_destroy(sem_t sem)
{
	/* TODO Phase 3 */
	if(!sem){
		return -1;
	}
	
	
	free(sem);
	
	return 0;
}

//count is the number of threads that can share it at the same time 


int sem_down(sem_t sem)   // acquire, P(), wait 				-- thread 2 not returning to func
{
	printf("	block\n");
	
	/* TODO Phase 3 */
	struct uthread_tcb* cur = uthread_current(); 
	
	
	
	if((sem->count)==0){
		printf("	enqueue\n");
		queue_enqueue(sem->blockQ,cur);
		uthread_block();
	}
	else if((sem->count)>0){
		sem->count--;
	}
	else if((sem->count)<0){
		printf("error");
	}
	

	
	
	return 0;
}



int sem_up(sem_t sem)   // release, V(), signal
{
	printf("	un-block\n");
	
	/* TODO Phase 3 */
	struct uthread_tcb* cur = uthread_current(); 
	struct uthread_tcb* temp;
	

	//printf("	count = %d \n",sem->count);
	if((sem->count)==0){
		printf("	dequeue");
		queue_dequeue(sem->blockQ,(void**) &temp);
		uthread_unblock(temp);		
	}
		

	

	
	
	
	return 0;
}
