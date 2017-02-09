#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define _UTHREAD_PRIVATE
#include "context.h"
#include "preempt.h"
#include "queue.h"
#include "uthread.h"

struct uthread_tcb {
	/* TODO Phase 2 */
	int status;
	uthread_ctx_t* context;
	void *stack;
};


queue_t threadQ;
struct uthread_tcb* runningThread = NULL;

void uthread_yield(void)
{
	/* TODO Phase 2 */
	//printf("%d", queue_length(threadQ));

	struct uthread_tcb *curr, *next;
	queue_enqueue(threadQ, runningThread); // requeue top
	curr = runningThread;
	
	queue_dequeue(threadQ, (void**) &next); // dequeue next
	//printf("%d %d", top, next); fflush(stdout);
	
	runningThread = next;
	uthread_ctx_switch(curr->context, next->context); // context switch top and next

}

int uthread_create(uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
	struct uthread_tcb* thread = malloc(sizeof(struct uthread_tcb)); // allocate new tcb
	thread->context = malloc(sizeof(uthread_ctx_t));
	thread->stack = uthread_ctx_alloc_stack(); // call stack allocator, from context.c/.h
	uthread_ctx_init(thread->context, thread->stack, func, arg); // init context from ^

	queue_enqueue(threadQ, thread); // add tcb to queue
}

void uthread_exit(void)
{
	/* TODO Phase 2 */
	struct uthread_tcb *curr, *next;
	curr = runningThread;
	
	queue_dequeue(threadQ, (void**) &next); // dequeue next
	//printf("%d %d", top, next); fflush(stdout);
	
	runningThread = next;
	uthread_ctx_switch(curr->context, next->context); // context switch top and next
}

void uthread_block(void)
{
	/* TODO Phase 2 */
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	/* TODO Phase 2 */
}

struct uthread_tcb *uthread_current(void)
{
	/* TODO Phase 2 */
	return runningThread;
}

void uthread_start(uthread_func_t start, void *arg)
{
	/* TODO Phase 2 */
	threadQ = queue_create(); // queue of tcb

	struct uthread_tcb* idle = malloc(sizeof(struct uthread_tcb)); // create idle thread
	idle->context = malloc(sizeof(uthread_ctx_t));
	idle->stack = uthread_ctx_alloc_stack();
	queue_enqueue(threadQ, idle); // add idle thread

	runningThread = idle;

	uthread_create(start, arg); // add first thread
	
	//printf("%d\n", queue_length(threadQ)); fflush(stdout);

	// infinite loop
	while(1) {
		if (queue_length(threadQ) > 1) // does not only have idle thread
			uthread_yield(); // yield to next thread
		else exit(0); // exit loop
	}
}
