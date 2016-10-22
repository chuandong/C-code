#include "queue.h"
#include <stdio.h>

int main()
{	
	queue_t *queue;
	int value;

	queue = queue_init(10);

	puts("EnQeueue:");
	value = 1;
	while (0 == queue_enqueue(queue, value)) {
		printf("%3d", value);
		value++;
	}
	putchar('\n');

	puts("Debug:");
	_queue_debug_(queue);

	puts("DeQueue:");
	while (0 == queue_dequeue(queue, &value))
		printf("%3d", value);
	putchar('\n');
	
	puts("Debug:");
	_queue_debug_(queue);

	queue_destroy(queue);


	return 0;
}
