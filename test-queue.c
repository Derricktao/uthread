#include <stdlib.h>
#include <stdio.h>
#include <assert.h>	
#include <queue.h>

// compile with:
// $ gcc -Werror -g -o test-queue -Ilibuthread test-queue.c -Llibuthread -luthread

void pq(void *data)
{
	printf("%d\n", *(int*)data);
}

int main(int argc, char* argv[])
{
	queue_t queue = queue_create();

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	
	int *e;
	

//Enqueue
	queue_enqueue(queue,&a);
	queue_enqueue(queue,&b);
	queue_enqueue(queue,&c);
	queue_enqueue(queue,&d);
	
	/*queue_dequeue(queue,(void**)&e);
	printf("%o %o\n", e, &a);
	
	queue_dequeue(queue,(void**)&e);
	printf("%o %o\n", e, &b);	*/
	printf("abcd enqueued\n");
	printf("queue length now is %d\n",queue_length(queue));
	printf("the queue is: \n");
	queue_iterate(queue,pq);
	
//Queue dequeue
	queue_dequeue(queue,(void**)&e);
	printf("dequeued to e \n");
	printf("queue length now is %d\n",queue_length(queue));
	printf("the queue is: \n");
	queue_iterate(queue,pq);
	printf("e is %d\n",*e); 

//Queue Delete
	printf("\nTest Delete\ndelete b// queue_delete(queue, &b;\n");
	queue_delete(queue, &b);
	printf("the queue is: \n");
	queue_iterate(queue,pq);
	printf("queue length now is %d\n",queue_length(queue));	

//Test the queue_destory
	printf("\nTest Destroy\nDestroy the queue //queue_destroy(queue);\n");
	queue_destroy(queue);
	printf("queue length now is %d\n",queue_length(queue));


	assert(queue_destroy(NULL) == -1);
	assert(queue_enqueue(NULL, NULL) == -1);
	return 0;
}
