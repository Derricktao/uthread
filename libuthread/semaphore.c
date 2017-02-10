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
	size_t max;
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
	//printf("		block\n");
	
	/* TODO Phase 3 */
	struct uthread_tcb* cur = uthread_current(); 
	
/*    	if((sem->count)>=0){			// If the value of semaphore variable is not negative, decrements it by 1
		sem->count--;
		printf("		count\n");	
		if ((sem->count)<0 ){//If the semaphore variable is now negative, the process executing 
											//wait is blocked (i.e., added to the semaphore's queue) until the value is greater or equal to 1
			printf("		block\n");	
			queue_enqueue(sem->blockQ,cur);			
			uthread_block();								
		}
		//printf("		count = %d\n",sem->count);
	}  
  */
	 //--------------------------------------------------------------------------------------------------------------
	
	
/* 	     if((sem->count)==0){
			//printf("		enqueue\n");
			queue_enqueue(sem->blockQ,cur);
			uthread_block();
			//sem->count--;
		} */
		
     if((sem->count)==0){
		printf("		block, count = %d\n", sem->count);
		queue_enqueue(sem->blockQ,cur);
		uthread_block();
		//sem->count--; // you accidentally put this in here
	}
	else if((sem->count)>0){					// add to top?
		sem->count--;
		printf("		run, count = %d\n", sem->count);
	}
	else if((sem->count)<0){
		printf("error");
	}   
	  
	 //--------------------------------------------------------------------------------------------------------------
	 
/* 	 if((sem->count)>0){
		 sem->count--;
	 }
	 else{
		 uthread_block();	
	 }
	  */
	 

	//printf("		count = %d\n",sem->count);
	
	return 0;
}



int sem_up(sem_t sem)   // release, V(), signal, increment 
{
	//printf("		un-block\n");
	
	/* TODO Phase 3 */
	struct uthread_tcb* cur = uthread_current(); 
	struct uthread_tcb* temp;
	
/*     	sem->count++; 	//Increments the value of semaphore variable by 1.
	
	
	if((sem->count)==0){		//if the pre-increment value was negative
	
										//transfers a blocked process from the semaphore's waiting queue to the ready queue.
		printf("		un-block\n");								
		queue_dequeue(sem->blockQ,(void**) &temp);
		uthread_unblock(temp);									
	
	}    */
			 //--------------------------------------------------------------------------------------------------------------							
/* 	
	count--;
	
	sem->count++;
	printf("		count = %d\n",sem->count);  */
	
 	//printf("	count = %d \n",sem->count);

	//printf("		dequeue\n");
	
	
	
	 //--------------------------------------------------------------------------------------------------------------
	
   	if(sem->count == 0 && queue_length(sem->blockQ)>0){
		printf("		unblock\n");
		queue_dequeue(sem->blockQ,(void**) &temp);
		uthread_unblock(temp);	
		//sem->count++; 
	}
	else sem->count++;
	//else if (sem->count < sem->max) sem->count++;
   	
		
		 //--------------------------------------------------------------------------------------------------------------
	
/*    	if(queue_length(sem->blockQ)>0){
		queue_dequeue(sem->blockQ,(void**) &temp);
		uthread_unblock(temp);	
	}
	else{
		sem->count++;
	}
	 */

	//printf("		count = %d\n",sem->count);

	
	
	
	return 0;
}
