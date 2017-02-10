#include <stdlib.h>
#include <stdio.h>

#include <queue.h>

// compile with:
// $ gcc -Werror -g -o test-queue -Ilibuthread test-queue.c -Llibuthread -luthread

int main(int argc, char* argv[])
{
	queue_t queue = queue_create();

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	
	int *e;
	
	printf("%o %o %o\n", &a, &b, &e);

	queue_enqueue(queue,&a);
	queue_enqueue(queue,&b);
	//queue_enqueue(queue,&c);
	//queue_enqueue(queue,&d);
	
	queue_dequeue(queue,(void**)&e);
	printf("%o %o\n", e, &a);
	
	queue_dequeue(queue,(void**)&e);
	printf("%o %o\n", e, &b);	
	
	//queue_delete(queue,&b);

	return 0;
}
