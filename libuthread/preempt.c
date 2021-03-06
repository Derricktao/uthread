#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define _UTHREAD_PRIVATE
#include "preempt.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100

void preempt_save(sigset_t *level)
{
	/* TODO Phase 4 */

	sigprocmask(0, NULL, level); // save mask to level
	preempt_disable(); // disable preemption
}

void preempt_restore(sigset_t *level)
{
	/* TODO Phase 4 */

	sigprocmask(SIG_SETMASK, level, NULL); // set mask to level
}

void preempt_enable(void)
{
	/* TODO Phase 4 */

	sigset_t mask; // signal mask
	sigemptyset(&mask); // set mask to empty
	sigaddset(&mask, SIGVTALRM); // add SIGVTALRM to mask
	sigprocmask(SIG_UNBLOCK, &mask, NULL); // unblock SIGVTALRM
}

void preempt_disable(void)
{
	/* TODO Phase 4 */

	sigset_t mask; // signal mask
	sigemptyset(&mask); // set mask to empty
	sigaddset(&mask, SIGVTALRM); // add SIGVTALRM to mask
	sigprocmask(SIG_BLOCK, &mask, NULL); // block SIGVTALRM
}

bool preempt_disabled(void)
{
	/* TODO Phase 4 */
	
	sigset_t mask; // signal mask
	sigprocmask(0, NULL, &mask); // copy current mask
	
	// check if SIGVTALRM is in mask,
	if (sigismember(&mask, SIGVTALRM)) return true;  // preemption is disabled
	else return false; // preemption is enabled
}

/*
 * timer_handler - Timer signal handler (aka interrupt handler)
 * @signo - Received signal number (can be ignored)
 */
static void timer_handler(int signo)
{
	/* TODO Phase 4 */

	if (!preempt_disabled()) // if preemption not disabled
		uthread_yield(); // yield to next thread
}

void preempt_start(void)
{
	struct sigaction sa;
	struct itimerval it;

	/*
	 * Install signal handler @timer_handler for dealing with alarm signals
	 */
	sa.sa_handler = timer_handler;
	sigemptyset(&sa.sa_mask);
	/* Make functions such as read() or write() to restart instead of
	 * failing when interrupted */
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGVTALRM, &sa, NULL)) {
		perror("sigaction");
		exit(1);
	}

	/*
	 * Configure timer to fire alarm signals at a certain frequency
	 */
	it.it_value.tv_sec = 0;
	it.it_value.tv_usec = 1000000 / HZ;
	it.it_interval.tv_sec = 0;
	it.it_interval.tv_usec = 1000000 / HZ;
	if (setitimer(ITIMER_VIRTUAL, &it, NULL)) {
		perror("setitimer");
		exit(1);
	}
}