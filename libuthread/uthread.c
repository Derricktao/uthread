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

queue_t threadQ;

struct uthread_tcb {
	/* TODO Phase 2 */
	int status;
	uthread_ctx_t context;
	void *stack;
};

void uthread_yield(void)
{
	/* TODO Phase 2 */
}

int uthread_create(uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
	uthread_tcb* thread = malloc(sizeof(uthread_tcb);
	thread->stack = uthread_ctx_alloc_stack();
	uthread_ctx_init(thread->context, thread->stack, func, arg);

	threadQ.enqueue(thread);
}

void uthread_exit(void)
{
	/* TODO Phase 2 */
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
}

void uthread_start(uthread_func_t start, void *arg)
{
	/* TODO Phase 2 */
	threadQ = queue_create(); // queue of tcb

	uthread_tcb* idle = malloc(sizeof(uthread_tcb); // create idle thread
	threadQ.enqueue(idle); // add idle thread

	uthread_create(start, arg); // add first thread

	// infinite loop
	while(1) {

	}
}
