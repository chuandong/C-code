#include "queue.h"

queue_t *queue_init(int len)
{
	queue_t *queue;

	queue = malloc(sizeof(*queue));
	queue->data = malloc(sizeof(int) * len);
	queue->head = 0;
	queue->tail = 0;
	queue->tlen = len;

	return queue;
}

int queue_destroy(queue_t *queue)
{
	free(queue->data);
	free(queue);

	return 0;
}

int queue_enqueue(queue_t *queue, int value)
{
	if (queue_isfull(queue))
		return -1;
	
	queue->data[queue->tail] = value;
	queue->tail = (queue->tail + 1) % queue->tlen;

	return 0;
}

int queue_dequeue(queue_t *queue, int *value)
{
	if (queue_isempty(queue))
		return -1;
	
	*value = queue->data[queue->head];
	queue->head = (queue->head + 1) % queue->tlen;

	return 0;
}

int queue_isfull(queue_t *queue)
{
	return (queue->tail + 1) % queue->tlen == queue->head;
}

int queue_isempty(queue_t *queue)
{
	return queue->head == queue->tail;
}

#if QUEUE_DEBUG
void _queue_debug_(queue_t *queue)
{
	int i;

	printf("Head: %d\tTail: %d\tTlen: %d\n", 
			queue->head, queue->tail, queue->tlen);
	for (i = 0; i < queue->tlen; i++)
		printf("%3d", queue->data[i]);
	putchar('\n');
}
#endif

// int queue_getlen(queue_t *queue);
