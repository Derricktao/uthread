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


int sem_down(sem_t sem)   // acquire, P(), wait, decre,ent				-- thread 2 not returning to func
{
	/* TODO Phase 3 */
	if (!sem) return -1;

	struct uthread_tcb* cur = uthread_current(); 
	
	if((sem->count)==0){
		//printf("		block, count = %d\n", sem->count);
		queue_enqueue(sem->blockQ,cur);
		uthread_block();
		//sem->count--; // you accidentally put this in here
	}
	else if((sem->count)>0){					// add to top?
		sem->count--;
		//printf("		run, count = %d\n", sem->count);
	}
	else if((sem->count)<0){
		printf("error");
	}   
	  
	
	return 0;
}



int sem_up(sem_t sem)   // release, V(), signal, increment 
{
	/* TODO Phase 3 */
	if (!sem) return -1;

	struct uthread_tcb* cur = uthread_current(); 
	struct uthread_tcb* temp;

	
   	if(sem->count == 0 && queue_length(sem->blockQ)>0){
		//printf("		unblock\n");
		queue_dequeue(sem->blockQ,(void**) &temp);
		uthread_unblock(temp);	
		//sem->count++; 
	}
	else {
		sem->count++;
		//printf("		up, count = %d\n", sem->count);
	}

	return 0;
}
