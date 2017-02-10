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

//https://en.wikipedia.org/wiki/Semaphore_(programming)


int sem_down(sem_t sem)   // acquire, P(), wait, decre,ent				-- thread 2 not returning to func
{
	printf("		block\n");
	
	/* TODO Phase 3 */
	struct uthread_tcb* cur = uthread_current(); 
	
/* 	if((sem->count)>=0){			// If the value of semaphore variable is not negative, decrements it by 1
		sem->count--;
		
		if ((sem->count)<0 ){//If the semaphore variable is now negative, the process executing 
											//wait is blocked (i.e., added to the semaphore's queue) until the value is greater or equal to 1
											
			uthread_block();								
		}
		printf("		count = %d\n",sem->count);
	}
 */
	
	
 	if((sem->count)==0){
		printf("		enqueue\n");
		queue_enqueue(sem->blockQ,cur);
		uthread_block();
		//sem->count--;
	}
	else if((sem->count)>0){
		sem->count--;
	}
	else if((sem->count)<0){
		printf("error");
	}
	 

	printf("		count = %d\n",sem->count);
	
	return 0;
}



int sem_up(sem_t sem)   // release, V(), signal, increment 
{
	printf("		un-block\n");
	
	/* TODO Phase 3 */
	struct uthread_tcb* cur = uthread_current(); 
	struct uthread_tcb* temp;
	
/* 	sem->count++; 	//Increments the value of semaphore variable by 1.
	
	
	if((sem->count)==0){		//if the pre-increment value was negative
	
										//transfers a blocked process from the semaphore's waiting queue to the ready queue.
										
		queue_dequeue(sem->blockQ,(void**) &temp);
		uthread_unblock(temp);									
	
	}
	
	
	count--;
	
	
	printf("		count = %d\n",sem->count); */
	
 	//printf("	count = %d \n",sem->count);

	printf("		dequeue\n");
	if(queue_length(sem->blockQ)>0){
		queue_dequeue(sem->blockQ,(void**) &temp);
		uthread_unblock(temp);	
	}
	else{
		sem->count++;
	}
		
	

	printf("		count = %d\n",sem->count);

	
	
	
	return 0;
}
