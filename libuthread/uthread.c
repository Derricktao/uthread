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
	int status; // status of thread; NOT IMPLEMENTED YET
	uthread_ctx_t* context; // context, from context.c/.h
	void *stack; // stack, allocated from function in context.c/.h
};


queue_t threadQ; // queue for ready threads
struct uthread_tcb* runningThread = NULL; // tracker for currently running thread

void uthread_yield(void)
{
	/* TODO Phase 2 */
	//printf("%d", queue_length(threadQ));

	struct uthread_tcb *curr, *next; // holders for current thread and next thread
	queue_enqueue(threadQ, runningThread); // requeue running thread
	curr = runningThread; // temp hold running thread
	
	queue_dequeue(threadQ, (void**) &next); // dequeue next thread
	//printf("%d %d", top, next); fflush(stdout);
	
	runningThread = next; // update running thread
	uthread_ctx_switch(curr->context, next->context); // context switch current and next thread
}

int uthread_create(uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
	struct uthread_tcb* thread = malloc(sizeof(struct uthread_tcb)); // allocate new tcb
	thread->context = malloc(sizeof(uthread_ctx_t)); // init context space
	thread->stack = uthread_ctx_alloc_stack(); // call stack allocator, from context.c/.h
	uthread_ctx_init(thread->context, thread->stack, func, arg); // init context from ^

	queue_enqueue(threadQ, thread); // add tcb to queue
}

void uthread_exit(void)
{
	/* TODO Phase 2 */
	// called from context bootstrap in context.c/.h
	// basically same as yield, except without requeuing running thread
	struct uthread_tcb *curr, *next; // holders for current thread and next thread
	curr = runningThread; // temp hold running thread
	
	queue_dequeue(threadQ, (void**) &next); // dequeue next thread
	//printf("%d %d", top, next); fflush(stdout);
	
	runningThread = next; // update running thread
	uthread_ctx_switch(curr->context, next->context); // context switch current and next thread
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
	return runningThread; // return running thread
}

void uthread_start(uthread_func_t start, void *arg)
{
	/* TODO Phase 2 */
	threadQ = queue_create(); // queue of tcb

	struct uthread_tcb* idle = malloc(sizeof(struct uthread_tcb)); // create idle thread
	idle->context = malloc(sizeof(uthread_ctx_t)); // init context space
	idle->stack = uthread_ctx_alloc_stack(); // init stack space
	queue_enqueue(threadQ, idle); // add idle thread to queue

	runningThread = idle; // update runningThread

	uthread_create(start, arg); // add first thread to queue

	// infinite loop
	while(1) {
		if (queue_length(threadQ) > 1) // does not only have idle thread
			uthread_yield(); // yield to next thread
		else exit(0); // exit loop
	}
}
