all: libuthread.a	

libuthread.a: context.o preempt.o queue.o semaphore.o uthread.o
	ar cr libuthread.a context.o preempt.o queue.o semaphore.o uthread.o

context.o:
	gcc -Werror -g -c context.c

preempt.o:
	gcc -Werror -g -c preempt.c

queue.o:
	gcc -Werror -g -c queue.c

semaphore.o:
	gcc -Werror -g -c semaphore.c

uthread.o:
	gcc -Werror -g -c uthread.c

clean:
	rm -f libuthread.a *.o
