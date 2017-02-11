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

	size_t count; // size of semaphore
	queue_t blockQ; // queue for blocked threads
} *sem_t;

sem_t sem_create(size_t count)
{
	/* TODO Phase 3 */
	
	if(count < 0) return NULL; // if invalid size

	sigset_t mask;
	preempt_save(&mask); // save and disable preemption

	sem_t sem = malloc(sizeof(sem_t)); // make space for new semaphore
	sem->count = count; // set count
	sem->blockQ = queue_create(); // make new queue

	preempt_restore(&mask); // restore signal mask
	
	return sem;
}

int sem_destroy(sem_t sem)
{
	/* TODO Phase 3 */

	if(!sem) return -1; // if NULL pointer, return -1
	
	sigset_t mask;
	preempt_save(&mask); // save and disable preemption

	free(sem); // free

	preempt_restore(&mask); // restore signal mask
	
	return 0;
}

int sem_down(sem_t sem)
{
	/* TODO Phase 3 */

	if (!sem) return -1; // if NULL pointer, return -1
	
	if(sem->count == 0)
	{
		queue_enqueue(sem->blockQ,uthread_current()); // add current thread to blocked thread queue
		uthread_block(); // block current thread
	}
	else if(sem->count > 0)
	{
		sem->count--; // decrement count
	}	  
	
	return 0;
}

int sem_up(sem_t sem)
{
	/* TODO Phase 3 */

	if (!sem) return -1; // if NULL pointer, return -1
	
   	if(sem->count == 0 && queue_length(sem->blockQ) > 0)
   	{
		struct uthread_tcb* temp; // temp holder
		queue_dequeue(sem->blockQ,(void**) &temp); // dequeue first blocked thread
		uthread_unblock(temp); // unblock thread
	}
	else
	{
		sem->count++; // increment count
	}

	return 0;
}