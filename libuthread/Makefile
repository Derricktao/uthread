all: libuthread.a	

libuthread.a: context.o preempt.o queue.o semaphore.o uthread.o
	ar cr libuthread.a context.o preempt.o queue.o semaphore.o uthread.o

context.o:
	gcc -c context.c

preempt.o:
	gcc -c preempt.c

queue.o:
	gcc -c queue.c

semaphore.o:
	gcc -c semaphore.c

uthread.o:
	gcc -c uthread.c
